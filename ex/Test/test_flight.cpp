#include "Math/FastMath.h"
#include "harness_flight.hpp"

int main(int argc, char** argv) 
{
  ::InitSineTable();

  // default arguments
  bearing_noise=0;
  target_noise=0.1;
  turn_speed=5.0;
  output_skip = 5;

  if (!parse_args(argc,argv)) {
    return 0;
  }

  int n_wind = 3;

  plan_tests(5*n_wind);

  for (int i=0; i<n_wind; i++) {
    for (int j=0; j<5; j++) {
      ok (test_flight(j,i), test_name("flight",j),0);
    }
  }
  return exit_status();
}
