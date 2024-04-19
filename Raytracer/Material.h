#pragma once

#include "Hittable.h"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const HitRecord& hit, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
  public:
    Lambertian(const Color& a) : albedo(a) {}

    bool scatter(const Ray& ray, const HitRecord& hit, Color& attenuation, Ray& scattered)
    const override {
        Vector3 scatter_direction = hit.normal + Vector3::random_normalized_vector();
        
        if (scatter_direction.near_zero())
            scatter_direction = hit.normal;
        
        scattered = Ray(hit.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

  private:
    Color albedo;
};

class Metal : public Material {
  public:
    Metal(const Color& a) : albedo(a) {}

    bool scatter(const Ray& ray, const HitRecord& hit, Color& attenuation, Ray& scattered)
    const override {
        Vector3 reflected = Vector3::reflect(ray.direction().normalized(), hit.normal);
        scattered = Ray(hit.p, reflected);
        attenuation = albedo;
        return true;
    }

  private:
    Color albedo;
};
