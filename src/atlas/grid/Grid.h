/*
 * (C) Copyright 1996-2014 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Peter Bispham
/// @author Tiago Quintino
/// @date Oct 2013

#ifndef atlas_grid_Grid_H
#define atlas_grid_Grid_H

#include <cstddef>
#include <vector>
#include <cmath>

#include "eckit/exception/Exceptions.h"
#include "eckit/memory/Owned.h"
#include "eckit/memory/SharedPtr.h"
#include "eckit/value/Params.h"

#include "eckit/geometry/Point2.h"

//------------------------------------------------------------------------------------------------------

namespace atlas {

class Mesh;

namespace grid {

class GridSpec;

//------------------------------------------------------------------------------------------------------

/// Interface to a grid of points in a 2d cartesian space
/// For example a LatLon grid or a Reduced Graussian grid
///
///      DECODE                       ATLAS                      ENCODE
///      NetCDFBuilder ---->|-------|         |----------|------>NetCDFWrite
///                         | Grid  |<------> | GridSpec |
///      GribBuilder ------>|-------|         |----------|------>GribWrite

class Grid : public eckit::Owned {

public: // types

    typedef eckit::geometry::LLPoint2           Point;     ///< point type

    typedef eckit::geometry::BoundBox2<Point>   BoundBox;

    typedef eckit::SharedPtr<Grid> Ptr;

//    class Iterator {
//    public:
//        virtual ~GridIterator() {}
//        virtual bool next( double& lat, double& lon ) = 0;
//    };
//    virtual Iterator* makeIterator() const = 0;

    class Coords {
    public:

        Coords( std::vector<double>& v ) : coords_(v) { ASSERT( v.size() && v.size()%2 == 0 ); }
        size_t size() const { return coords_.size() / 2; }
        double& lat( size_t i ) { return coords_[i];   }
        double& lon( size_t i ) { return coords_[i+1]; }

    private:

        std::vector<double>& coords_;
    };

    Mesh& mesh();
    const Mesh& mesh() const;

public: // methods

    Grid();

    virtual ~Grid();

    virtual std::string hash() const = 0;

    virtual BoundBox boundingBox() const = 0;

    virtual size_t nPoints() const = 0;

    virtual void coordinates( Grid::Coords& ) const = 0;

    virtual std::string gridType() const = 0;

    /// The GridSpec also includes the gridType, new allocated
    virtual GridSpec* spec() const = 0;

    virtual void constructFrom(const GridSpec& ) = 0;

    virtual void constructFrom( const eckit::Params& ) { NOTIMP; }

    virtual bool compare(const Grid&) const = 0;

    /// @deprecated will be removed soon as it exposes the inner storage of the coordinates
    virtual const std::vector<Point>& coordinates() const = 0;

private: // members

    mutable eckit::SharedPtr< Mesh > mesh_;

};

//------------------------------------------------------------------------------------------------------

} // namespace grid
} // namespace atlas

#endif
