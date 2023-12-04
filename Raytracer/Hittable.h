#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Interval.h"
// #include "math/Vector3.h"

class HitRecord {
  public:
    Vector3 p;
    Vector3 normal;
    number t;
    bool front_face;

    void set_face_normal(const Ray& ray, const Vector3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        normal = Vector3(outward_normal); 

        front_face = ray.direction() * normal < 0;
        
        if(!front_face)
            normal = normal * -1.0;//todo add - to Vector3
    }
};

class Hittable {
  public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, Interval interval, HitRecord& hit) const = 0;
};

#endif