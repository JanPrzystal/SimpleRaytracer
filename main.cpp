#include "window.h"
#include "math3d.h"
#include "Raytracer/raytracer.h"
#include <iostream>
#include <chrono>

typedef unsigned char byte;

u16 image_width = 480;
u16 image_height = 360;
number aspect_ratio;

RayCamera *camera = nullptr;
// int framebuffer[image_width * image_height];
Scene *scene = nullptr;

int drawImage(){

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // const Vector3 sphere = Vector3(rand()%4-2,rand()%4-2,-(rand()%6+1));
    uint64_t  beforeTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    camera->render(*scene);

    window_update(0,0,0,0);

    uint64_t  afterTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    uint64_t dTime = afterTime - beforeTime;
    std::cout << "Frame time: " << std::to_string(dTime) << "ms\n";

    return 0;
}

int main(){
    int rc = window_init(&image_width, &image_height, "Raytracer", drawImage);
    aspect_ratio = image_width / image_height;
    
    camera = new RayCamera((number)image_width/(number)image_height, 0.01, 100.0, 80.0, image_width, nullptr);
    camera->drawPixel = window_setPixel;

    auto greenMat = std::make_shared<Lambertian>(Lambertian(Color(0x0f, 0xbb, 0x0f, 0xff)));
    auto redMat = std::make_shared<Lambertian>(Lambertian(Color(0xff, 0x0f, 0x0f, 0xff)));
    auto blueMat = std::make_shared<Lambertian>(Lambertian(Color(0x00, 0x00, 0xff, 0xff)));
    auto whiteMat = std::make_shared<Lambertian>(Lambertian(Color(0xf0, 0xf0, 0xf0, 0xff)));
    auto metalMat = std::make_shared<Metal>(Metal(Color(0xdd, 0xdd, 0xdd, 0xff)));

    scene = new Scene();
    auto sphere1 = std::make_shared<Sphere>(Vector3(0.0f,0.1f,-1.4f), 0.6, metalMat);
    auto sphere2 = std::make_shared<Sphere>(Vector3(-0.58f,-0.2f,-0.75f), 0.3, redMat);
    auto sphere3 = std::make_shared<Sphere>(Vector3(1.02f,0.0f,-1.0f), 0.5, blueMat);
    auto plane1 = std::make_shared<Plane>(Vector3(0.0f, -0.5f, 0.0f), Vector3(0.0f,1.0f,0.0f), greenMat);
    auto planeB = std::make_shared<Plane>(Vector3(0.0f, -0.5f, -2.0f), Vector3(0.0f,0.0f,1.0f), whiteMat);
    auto planeL = std::make_shared<Plane>(Vector3(-30.0f, -0.5f, 0.0f), Vector3(1.0f,0.2f,-0.3f), whiteMat);
    auto planeR = std::make_shared<Plane>(Vector3(30.0f, -0.5f, 0.0f), Vector3(-1.0f,0.2f,-0.3f), whiteMat);
    scene->add(sphere1);
    scene->add(sphere2);
    scene->add(sphere3);
    scene->add(plane1);
    // scene->add(planeB);
    // scene->add(planeL);
    // scene->add(planeR);

    drawImage();
    //while(1);
    window_deinit();

    delete camera;
    delete scene;
    return 0;
}
