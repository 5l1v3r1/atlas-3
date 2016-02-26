// TL319

#include "atlas/grid/predefined/rgg/rgg.h"

namespace atlas {
namespace grid {
namespace predefined {
namespace rgg {

eckit::ConcreteBuilderT1<Grid,N160> deprecated_builder_N160 (N160::grid_type_str());
eckit::ConcreteBuilderT1<Grid,N160> builder_N160 ("N160");

void N160::construct()
{
  int N=160;
  long lon[] = {
     18,
     25,
     36,
     40,
     45,
     50,
     60,
     64,
     72,
     72,
     80,
     90,
     90,
     96,
    108,
    120,
    120,
    125,
    128,
    135,
    144,
    150,
    160,
    160,
    180,
    180,
    180,
    192,
    192,
    200,
    216,
    216,
    225,
    225,
    240,
    240,
    243,
    250,
    256,
    270,
    270,
    288,
    288,
    288,
    300,
    300,
    320,
    320,
    320,
    320,
    324,
    360,
    360,
    360,
    360,
    360,
    360,
    375,
    375,
    375,
    384,
    384,
    400,
    400,
    400,
    405,
    432,
    432,
    432,
    432,
    432,
    450,
    450,
    450,
    450,
    480,
    480,
    480,
    480,
    480,
    480,
    480,
    500,
    500,
    500,
    500,
    500,
    512,
    512,
    540,
    540,
    540,
    540,
    540,
    540,
    540,
    540,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    576,
    600,
    600,
    600,
    600,
    600,
    600,
    600,
    600,
    600,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640,
    640
  };
  std::vector<double> lats(N);
  gaussian_latitudes_npole_equator(N,lats.data());
  setup_lat_hemisphere(N,lats.data(),lon,internals::DEG);
}

} // namespace rgg
} // namespace predefined
} // namespace grid
} // namespace atlas
