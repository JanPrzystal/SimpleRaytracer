#ifndef RAY_H
#define RAY_H

#include "../Math3D/math3d.h"

class Ray {
  public:
    Ray() {}

    Ray(const Vector3& origin, const Vector3& direction) : orig(origin), dir(direction) {}

    Vector3 origin() const  { return orig; }
    Vector3 direction() const { return dir; }

    Vector3 at(number t) const {
        return (Vector3)orig + (Vector3)dir*t;
    }

  private:
    Vector3 orig;
    Vector3 dir;
};

#endif
