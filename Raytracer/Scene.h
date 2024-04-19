#ifndef SCENE_H
#define SCENE_H

#include "Hittable.h"
;
// #include <memory>
// #include <vector>

using std::shared_ptr;
using std::make_shared;

class Scene : public Hittable {
  public:
    std::vector<shared_ptr<Hittable>> objects;

    Scene() : Hittable(nullptr) {}
    Scene(shared_ptr<Hittable> object) : Scene() { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& ray, Interval interval, HitRecord& hit) const override {
        HitRecord tmp_hit;
        bool hit_anything = false;
        number closest_so_far = interval.max;

        for (const auto& object : objects) {
            if (object->hit(ray, Interval(interval.min, closest_so_far), tmp_hit)) {
                hit_anything = true;
                closest_so_far = tmp_hit.t;
                hit = tmp_hit;
            }
        }

        return hit_anything;
    }
};

#endif