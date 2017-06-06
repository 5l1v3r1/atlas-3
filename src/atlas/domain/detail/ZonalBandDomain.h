#pragma once

#include <iostream>
#include <array>
#include "atlas/domain/detail/RectangularDomain.h"

namespace atlas {
namespace domain {

class ZonalBandDomain: public RectangularDomain {

protected:

    static constexpr char units_[] = "degrees";

public:

     // constructor
    ZonalBandDomain( const eckit::Parametrisation& );
    ZonalBandDomain( const Interval& );

    static std::string static_type() {return "zonal_band";}
    virtual std::string type() const override { return static_type(); }

    /// Checks if the point is contained in the domain
    virtual bool contains(double x, double y) const override;

    virtual bool global() const override { return global_; }
    virtual bool empty() const override { return (ymin() == ymax()); }

    virtual Spec spec() const override;

    virtual void print(std::ostream&) const override;

    virtual std::string units() const override { return units_; }

private:

    bool global_;
    double ymin_tol_;
    double ymax_tol_;
};

}  // namespace domain
}  // namespace atlas
