#ifndef PLANE_H
#define PLANE_H

#include "Hittable.h"

class Plane : public Hittable {
public:
    Plane(Vector3 _center, Vector3 _normal, shared_ptr<Material> _material) : Hittable(_material), center(_center), normal(_normal) {}

    bool hit(const Ray& ray, Interval interval, HitRecord& hit) const override {
        number denom = normal * ray.direction();
        if(denom >= 0){
            return false;
        }else{
            number t = (((Vector3)center - ray.origin()) * normal)/denom;
            if(interval.surrounds(t)){
                hit.t = t;
                hit.p = ray.at(hit.t);
                hit.normal = normal;
                hit.set_face_normal(ray, normal);
                hit.material = material;
                return true;
            }
        }
        return false;
    }

private:
    Vector3 center;
    Vector3 normal;
};

#endif