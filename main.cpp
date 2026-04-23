#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

using namespace std;

color ray_color(const ray &r) { return color(0, 0, 0); }

int main() {

  auto aspect_ratio = 16.0 / 9.0;
  int image_w = 400;

  int image_h = int(image_w / aspect_ratio);
  image_h = (image_h) < 1 ? 1 : image_h;

  auto focal_length = 1.0;
  auto viewport_h = 2.0;
  auto viewport_w = viewport_h * (double(image_w) / image_h);
  auto camera_center = point3(0, 0, 0);

  auto viewport_u = vec3(viewport_w, 0, 0);
  auto viewport_v = vec3(0, -viewport_h, 0);

  auto pixel_data_u = viewport_u / image_w;
  auto pixel_data_v = viewport_v / image_h;

  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_data_u + pixel_data_v);

  cout << "P3\n" << image_w << ' ' << image_h << "\n255\n";

  for (int i = 0; i < image_h; i++) {
    clog << "\rScanlines remaining" << (image_h - i) << ' ' << flush;
    for (int j = 0; j < image_w; j++) {
      auto pixel_center = pixel00_loc + (j * pixel_data_u) + (i * pixel_data_v);
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);
      color pixel_color = ray_color(r);

      write_color(cout, pixel_color);
    }
  }

  clog << "\rDone \n";
}
