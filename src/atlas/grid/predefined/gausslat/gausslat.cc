/*
 * (C) Copyright 1996-2016 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Willem Deconinck
/// @date Jan 2015

#include "atlas/atlas_config.h"
#include "atlas/grid/predefined/gausslat/gausslat.h"

namespace atlas {
namespace grid {
namespace predefined {
namespace gausslat {

//------------------------------------------------------------------------------------------------------

void GaussianLatitudes::assign(double lats[], const size_t size) const
{
    ASSERT( size >= lats_.size() );
    for(size_t jlat=0; jlat < lats_.size(); ++jlat)
        lats[jlat] = lats_[jlat];
}

void GaussianLatitudes::assign(std::vector<double>& lats) const
{
    lats = lats_;
}

template<typename CONCRETE>
void load()
{
  eckit::ConcreteBuilderT0<GaussianLatitudes,CONCRETE> builder("tmp");
}

void regist()
{
  load<N16>();
  load<N24>();
  load<N32>();
  load<N48>();
  load<N64>();
  load<N80>();
  load<N96>();
  load<N128>();
  load<N160>();
  load<N200>();
  load<N256>();
  load<N320>();
  load<N400>();
  load<N512>();
  load<N576>();
  load<N640>();
  load<N800>();
  load<N1024>();
  load<N1280>();
  load<N1600>();
  load<N2000>();
  load<N4000>();
  load<N8000>();
}

//------------------------------------------------------------------------------------------------------

} // namespace gausslat
} // namespace predefined
} // namespace grid
} // namespace atlas

