/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#include "Interpolation.h"

#include <map>
#include "eckit/thread/AutoLock.h"
#include "eckit/thread/Once.h"
#include "eckit/thread/Mutex.h"
#include "eckit/exception/Exceptions.h"


namespace atlas {
namespace interpolation {


namespace {


typedef std::map<std::string, InterpolationFactory*> InterpolationFactoryMap_t;
static InterpolationFactoryMap_t *m = 0;
static eckit::Mutex *local_mutex = 0;
static pthread_once_t once = PTHREAD_ONCE_INIT;


static void init() {
    local_mutex = new eckit::Mutex();
    m = new InterpolationFactoryMap_t();
}


}  // (anonymous namespace)


InterpolationFactory::InterpolationFactory(const std::string& name):
    name_(name) {
    pthread_once(&once, init);
    eckit::AutoLock<eckit::Mutex> lock(local_mutex);

    if (m->find(name) != m->end()) {
        throw eckit::SeriousBug("InterpolationFactory duplicate '" + name + "'");
    }

    ASSERT(m->find(name) == m->end());
    (*m)[name] = this;
}


InterpolationFactory::~InterpolationFactory() {
    eckit::AutoLock<eckit::Mutex> lock(local_mutex);
    m->erase(name_);
}


Interpolation* InterpolationFactory::build(const std::string& name, const Interpolation::Config& config) {
    pthread_once(&once, init);
    eckit::AutoLock<eckit::Mutex> lock(local_mutex);

    InterpolationFactoryMap_t::const_iterator j = m->find(name);
    if (j == m->end()) {
        eckit::Log::error() << "InterpolationFactory '" << name << "' not found." << std::endl;
        eckit::Log::error() << "InterpolationFactories are:" << std::endl;
        for (j = m->begin() ; j != m->end() ; ++j) {
            eckit::Log::error() << '\t' << (*j).first << std::endl;
        }
        throw eckit::SeriousBug("InterpolationFactory '" + name + "' not found.");
    }

    return (*j).second->make(config);
}


void Interpolation::normalise(Interpolation::Triplets& triplets) {
    // sum all calculated weights for normalisation
    double sum = 0.0;

    for (size_t j = 0; j < triplets.size(); ++j) {
        sum += triplets[j].value();
    }

    // now normalise all weights according to the total
    const double invSum = 1.0 / sum;
    for (size_t j = 0; j < triplets.size(); ++j) {
        triplets[j].value() *= invSum;
    }
}


}  // interpolation
}  // atlas

