// TL255

#include "atlas/grids/rgg/rgg.h"

namespace atlas {
namespace grids {
namespace rgg {

eckit::ConcreteBuilderT1<Grid,N128> builder_N128 (N128::grid_type_str());
eckit::ConcreteBuilderT1<Grid,N128> builder_TL255("rgg.TL255");

void N128::construct()
{
  int N=128;
  int lon[] = {
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
    100,
    108,
    120,
    120,
    125,
    128,
    144,
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
    216,
    225,
    240,
    240,
    240,
    250,
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
    360,
    375,
    375,
    375,
    375,
    384,
    384,
    400,
    400,
    400,
    400,
    405,
    432,
    432,
    432,
    432,
    432,
    432,
    432,
    450,
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
    480,
    480,
    480,
    486,
    486,
    486,
    500,
    500,
    500,
    500,
    500,
    500,
    500,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512,
    512
  };
  std::vector<double> lats(N);
  gaussian_latitudes_npole_equator(N,lats.data());
  setup_lat_hemisphere(N,lats.data(),lon,DEG);
}

} // namespace rgg
} // namespace grids
} // namespace atlas