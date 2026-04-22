#include "color.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

using namespace std;

int main() {
  int image_w = 256;
  int image_h = 256;

  cout << "P3\n" << image_w << ' ' << image_h << "\n255\n";

  for (int i = 0; i < image_h; i++) {
    clog << "\rScanlines remaining" << (image_h - i) << ' ' << flush;
    for (int j = 0; j < image_w; j++) {
      auto pixel_color =
          color(double(j) / (image_w - 1), double(i) / (image_h - 1), 0);
      write_color(cout, pixel_color);
    }
  }

  clog << "\rDone       \n";
}
