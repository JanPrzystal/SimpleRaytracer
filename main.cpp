#include "window.h"
#include "math3d/math3d.h"
#include "raytracer/Ray.h"
#include <iostream>

typedef unsigned char byte;

const int image_width = 256;
const int image_height = 256;
const NUMBER aspect_ratio = image_width / image_height;

bool hit_sphere(const Vector3& center, NUMBER radius, const Ray& r) {
    Vector3 oc = r.origin() - (Vector3)center;
    auto a = r.direction() * r.direction();
    auto b = 2.0 * (oc * r.direction());
    auto c = oc * oc - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

Vector3 ray_color(const Ray& r) {
    if (hit_sphere(Vector3(0,0,-1), 0.5, r))
    return Vector3(1, 0, 0);

    Vector3 unit_direction = Vector3(r.direction());
    NUMBER a = 0.5*(unit_direction.y + 1.0);
    return Vector3(1.0, 1.0, 1.0)*(NUMBER)(1.0-a) + Vector3(0.5, 0.7, 1.0)*a;
}

int drawImage(){
    // Camera, MOVE OUTSIDE RENDERING

    NUMBER focal_length = 1.0;
    NUMBER viewport_height = 2.0;
    NUMBER viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    Vector3 camera_center = Vector3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3 viewport_u = Vector3(viewport_width, 0, 0);
    Vector3 viewport_v = Vector3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vector3 pixel_delta_u = viewport_u / image_width;
    Vector3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    Vector3 viewport_upper_left = camera_center - Vector3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * (NUMBER)0.5;


  // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        // std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (pixel_delta_u*(NUMBER)i) + (pixel_delta_v*(NUMBER)j);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            Vector3 pixel_color = ray_color(r);

            int color = ((byte)0xFF) * pixel_color.z;//b
            color += (int)((byte)0xFF * pixel_color.y) << 8;//g
            color += (int)((byte)0xFF * pixel_color.x) << 16;//r
            window_setPixel(i, j, color);
        }
    }
    window_update(0,0,0,0);
    return 0;
}

int main(){
    int rc = window_init(image_width, image_height, "Raytracer", drawImage);
    while(1);
    window_deinit();
    return 0;
}