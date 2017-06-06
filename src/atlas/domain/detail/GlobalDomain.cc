#include "atlas/domain/detail/GlobalDomain.h"

namespace atlas {
namespace domain {

namespace {
  constexpr std::array<double,2> yrange() { 
    return { -90., 90. };
  }
}

GlobalDomain::GlobalDomain() :
  ZonalBandDomain( yrange() ) {
}

GlobalDomain::GlobalDomain(const eckit::Parametrisation& p) : 
  GlobalDomain() {
}

GlobalDomain::Spec GlobalDomain::spec() const {
  Spec domain_spec;
  domain_spec.set("type",type());
  return domain_spec;
}

void GlobalDomain::print(std::ostream& os) const {
  os << "GlobalDomain";
}

register_BuilderT1(Domain,GlobalDomain,GlobalDomain::static_type());

}  // namespace domain
}  // namespace atlas

