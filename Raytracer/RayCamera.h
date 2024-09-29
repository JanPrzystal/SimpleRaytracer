#include "math3d.h"
#include "Hittable.h"
#include "Material.h"
#include <iostream>

class RayCamera : public Camera {
public:
    int image_height;       // Rendered image height
    int image_width = 256;  // Rendered image width
    void (*drawPixel)(int x, int y, int color);
    int* framebuffer;
    int samples_per_pixel = 10;
    int max_depth = 5;
    number reflectance = 1.0f;

    RayCamera(int image_width, int* framebuffer) : Camera() {
        init(image_width, framebuffer);
    }

    RayCamera(number aspectRatio, number nearPlane, number farPlane, number fov, int image_width, int* framebuffer) : Camera(aspectRatio, nearPlane, farPlane, fov) {
        init(image_width, framebuffer);
    }

    void render(const Hittable& object){
        // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            int buffer_offset = j*image_width;
            // std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                Point pixel_center = pixel00_loc + (pixel_delta_u * (number)i) + (pixel_delta_v * (number)j);//TODO optimize
                Vector3 ray_direction = pixel_center - position;
                // Ray r(position, ray_direction);

                Color pixel_color = Color(0,0,0,0);//ray_color(r, object);
                Vector3 temp_color = Vector3();
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    Ray r = get_ray(i, j, pixel_center);
                    // if(i==j)
                    //     printf("pixel_color before %d %d %d %d\n", pixel_color.r, pixel_color.g, pixel_color.b, pixel_color.a);
                    temp_color += ray_color(r, object, max_depth).toVector();
                }
                pixel_color = Color::fromVector(temp_color / samples_per_pixel);
                // printf("color done %d\n", i);
                if(drawPixel != nullptr){
                    // printf("pixel color: %X\n", pixel_color.toInt());
                    drawPixel(i, j, pixel_color.toInt_24());
                }else if(image != nullptr)
                    image[buffer_offset + i] = pixel_color.toInt_24();
                else
                    std::cout << "RayCamera: Error: nowhere to draw pixel" << '\n';
            }
        }

        std::clog << "\nDone.           \n";

    }

private:
    int* image;             // Rendered image
    Point pixel00_loc;      // Location of pixel 0, 0
    Vector3 pixel_delta_u;  // Offset to pixel to the right
    Vector3 pixel_delta_v;  // Offset to pixel below

    Interval default_interval;

    void init(int image_width, int* framebuffer){
        this->image_width = image_width;
        if(framebuffer != nullptr)
            this->image = framebuffer;
       
        printf("image_width: %d, aspect ratio: %f\n", image_width, aspectRatio);
        image_height = static_cast<int>(image_width / aspectRatio);
        image_height = (image_height < 1) ? 1 : image_height;

        number focal_length = 1.0;
        number viewport_height = 2.0;
        number viewport_width = viewport_height * (static_cast<number>(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        Vector3 viewport_u = Vector3(viewport_width, 0, 0);
        Vector3 viewport_v = Vector3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        Vector3 viewport_upper_left = position - Vector3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * (number)0.5;

        default_interval = Interval(nearPlane, farPlane);

        printf("pixel00_loc: %f %f %f\n", pixel00_loc.x, pixel00_loc.y, pixel00_loc.z);

        printf("pixel_delta_u: %f %f %f\n", pixel_delta_u.x, pixel_delta_u.y, pixel_delta_u.z);
        printf("pixel_delta_v: %f %f %f\n", pixel_delta_v.x, pixel_delta_v.y, pixel_delta_v.z);
    }

    Color ray_color(const Ray& ray, const Hittable& object, int depth) const {
        if(depth < 1){
            return Color(0,0,0,0);
        }
        
        HitRecord hit = HitRecord();

        if (object.hit(ray, default_interval, hit)) {
            Ray scattered;
            Color attenuation;
            if (hit.material->scatter(ray, hit, attenuation, scattered))
                return attenuation * ray_color(scattered, object, depth-1);
            return Color(0,0,0,0);

            Vector3 direction = hit.normal + Vector3::random_on_hemisphere(hit.normal);
            return ray_color(Ray(hit.p, direction), object, depth-1) * reflectance;
            // return Color::fromVector((hit.normal + Vector3(1,1,1)) * 0.5);
        }

        Vector3 unit_direction = Vector3(ray.direction().normalized());
        number a = (unit_direction.y + 1.0) * 0.5;
        // printf("ray dir x: %f\n", ray.direction().x);

        //TODO skip float color
        //create color in 0.0-1.0 range
        Vector3 color = (Vector3(1.0, 1.0, 1.0)*(1.0-a)) + (Vector3(0.5, 0.7, 1.0)*a);

        //convert to int rgba 
        Color real_color = Color::fromVector(color);
        return real_color;
    }

    Ray get_ray(int i, int j, Point pixel_center) const {
        // Get a randomly sampled camera ray for the pixel at location i,j.
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_direction = pixel_sample - position;

        return Ray(position, ray_direction);
    }

    Vector3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.
        //todo cast
        number px = -0.5 + random_number();
        number py = -0.5 + random_number();
        return (pixel_delta_u * px) + (pixel_delta_v * py);
    }
};