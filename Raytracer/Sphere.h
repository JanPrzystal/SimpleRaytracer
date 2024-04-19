#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable {
  public:
    Sphere(Vector3 _center, number _radius, shared_ptr<Material> _material) : Hittable(_material), center(_center), radius(_radius) {}

    bool hit(const Ray& ray, Interval interval, HitRecord& hit) const override {
        Vector3 oc = ray.origin() - (Vector3)center;
        //quadratic formula
        number a = ray.direction() * ray.direction();
        number half_b = oc * ray.direction();
        number c = oc * oc - radius*radius;
        number discriminant = half_b*half_b - a*c;
        if (discriminant < 0) {
            return false;
        } 

        number sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        number root = (-half_b - sqrtd) / a;
        if (!interval.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!interval.surrounds(root))
                return false;
        }

        hit.t = root;
        hit.p = ray.at(hit.t);
        hit.normal = (hit.p - (Vector3)center) / radius;
        Vector3 outward_normal = (hit.p - (Vector3)center) / radius;
        hit.set_face_normal(ray, outward_normal);
        hit.material = material;

        return true;
    }

  private:
    Vector3 center;
    number radius;
};

#endif