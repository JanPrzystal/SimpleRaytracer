#include "rt_util.h"

// std::vector<shared_ptr<Hittable>> gHittableObjects = {};

// void rt_addHitabble(shared_ptr<Hittable> object) {
//     gHittableObjects.push_back(object);
// }

// bool rt_testRayHit(const Ray& r, Interval interval, HitRecord& rec) {
//     HitRecord temp_rec;
//     bool hit_anything = false;
//     number closest_so_far = interval.tmax;

//     for (const auto& object : gHittableObjects) {
//         if (object->hit(r, Interval(interval.tmin, closest_so_far), temp_rec)) {
//             hit_anything = true;
//             closest_so_far = temp_rec.t;
//             rec = temp_rec;
//         }
//     }

//     return hit_anything;
// }