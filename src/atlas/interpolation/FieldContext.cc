/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#include "atlas/interpolation/FieldContext.h"

//include "eckit/linalg/Vector.h"
//include "atlas/atlas.h"
#include "atlas/functionspace/NodeColumns.h"
#include "atlas/grid/GridDistribution.h"
#include "atlas/grid/partitioners/Partitioner.h"
#include "atlas/grid/Structured.h"
//include "atlas/internals/AtlasTool.h"
#include "atlas/mesh/generators/Structured.h"
#include "atlas/mesh/Mesh.h"
#include "atlas/mesh/Nodes.h"
#include "atlas/output/Gmsh.h"
//include "atlas/runtime/Log.h"

#include "atlas/grid/partitioners/PartitionerFromPrePartitionedMesh.h"
//include "atlas/interpolation/Interpolation.h"


namespace atlas {
namespace interpolation {


void FieldContext::read(const std::string&) {

    // Create source functionspace and fields
    functionSpace_.reset(new functionspace::NodeColumns(mesh(), meshHaloSize_));
    field::FieldSet src_fields;
    src_fields.add( functionSpace_->createField<double>("funny_scalar_1" /*, nb_levels=10*/) );
    src_fields.add( functionSpace_->createField<double>("funny_scalar_2" /*, nb_levels=10*/) );

    // Helper constants
    const double
            deg2rad = M_PI / 180.,
            c_lat = 0. * M_PI,
            c_lon = 1. * M_PI,
            c_rad = 2. * M_PI / 9.;

    array::ArrayView< double, 2 > lonlat( mesh().nodes().lonlat() );
    array::ArrayView< double, 1 >
            src_scalar_1(src_fields[0]),
            src_scalar_2(src_fields[1]);
    for (size_t j = 0; j < mesh().nodes().size(); ++j) {
        const double lon = deg2rad * lonlat(j, 0);  // (lon)
        const double lat = deg2rad * lonlat(j, 1);  // (lat)
        const double
                c2 = cos(lat),
                s1 = sin((lon-c_lon)/2.),
                s2 = sin((lat-c_lat)/2.),
                dist = 2.0 * sqrt( c2*s1*c2*s1 + s2*s2 );
        src_scalar_1(j) = dist < c_rad? 0.5 * (1. + cos(M_PI*dist/c_rad)) : 0.;
        src_scalar_2(j) = -src_scalar_1(j);


        double x = lonlat(j, 0) + 25.676;
        double y = lonlat(j, 1) - 37.741;
        while (x >  180.) { x -= 360.; }
        while (x < -180.) { x += 360.; }

        src_scalar_1(j) = -tanh(y/10*cos(50/sqrt(x*x+y*y))-x/10*sin(50/sqrt(x*x+y*y)));

    }

}


void FieldContext::write(const std::string& fileName) {
    util::Config output_config;
    output_config.set("coordinates", std::string("xyz"));
    output::Gmsh out(fileName, output_config);
    out.write(*mesh_);
    if (fieldSet_) {
        for (size_t i = 0; i < fieldSet_->size(); ++i) {
            out.write(fieldSet_->operator[](i));
        }
    }
}


FieldContext::FieldContext(
        const std::string& gridname,
        const std::string& partitioner,
        const std::string& meshGenerator,
        bool meshGeneratorTriangulate,
        double meshGeneratorAngle ) :
    optionGridname_(gridname),
    optionPartitioner_(partitioner),
    optionMeshGenerator_(meshGenerator),
    meshHaloSize_(0) {

    meshGeneratorParams_.set("three_dimensional", false);
    meshGeneratorParams_.set("patch_pole",        true);
    meshGeneratorParams_.set("include_pole",      false);
    meshGeneratorParams_.set("triangulate", meshGeneratorTriangulate);
    meshGeneratorParams_.set("angle",       meshGeneratorAngle);
}


}  // interpolation
}  // atlas
