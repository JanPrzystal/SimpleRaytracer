#include "window.h"
#include "math3d.h"
#include "raytracer/raytracer.h"
#include <iostream>

typedef unsigned char byte;

const int image_width = 640;
const int image_height = 480;
const number aspect_ratio = image_width / image_height;

RayCamera *camera = nullptr;
// int framebuffer[image_width * image_height];
Scene *scene = nullptr;

int drawImage(){

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // const Vector3 sphere = Vector3(rand()%4-2,rand()%4-2,-(rand()%6+1));

    camera->render(*scene);

    window_update(0,0,0,0);
    return 0;
}

int main(){
    camera = new RayCamera((number)image_width/(number)image_height, 0.1, 1000.0, 60.0, image_width, nullptr);
    camera->drawPixel = window_setPixel;

    scene = new Scene();
    auto sphere1 = std::make_shared<Sphere>(Vector3(0.0f,0.0f,-1.0f), 0.5);
    auto plane1 = std::make_shared<Plane>(Vector3(0.0f,-1.0f,-1.0f), Vector3(0.0f,1.0f,0.0f));
    scene->add(sphere1);
    scene->add(plane1);

    int rc = window_init(image_width, image_height, "Raytracer", drawImage);
    while(1);
    window_deinit();

    delete camera;
    delete scene;
    return 0;
}