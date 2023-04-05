#include <iostream>

#include "script/color.h"
#include "script/ray.h"
#include "script/vec3.h"

bool hit_sphere(const point3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - 4*a*c;
    
    return discriminant > 0;
}

color ray_color(const ray& r)
{
    if(hit_sphere(point3(2, 0, -5), 1, r))
        return color(1, 0, 0);
    
    vec3 unit_direction = unit_vector(r.direction());
    const float t = 0.5f*(unit_direction.y() + 1.0f);
    return (1.0f - t) * color(1.0f) + t * color(0.5f, 0.7f, 1.0f);      // lerp ---- blendedValue = (1−t).startValue + t.endValue
}

color ray_color(const ray& r, color col)
{
    vec3 unit_direction = unit_vector(r.direction());

    const float t = 0.5f*(unit_direction.y() + 1.0f);
    return (1.0f - t) * color(1.0f) + t * col;      // lerp ---- blendedValue = (1−t).startValue + t.endValue
}

int main() {

    // Image
    const auto aspect_ratio = 16.0f / 9.0f;
    const auto image_width = 400.0f;
    const auto image_height = image_width/aspect_ratio;

    // Camera
    auto viewport_height = 2.0f;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0f;

    auto origin = point3(0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n"<< image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr<< " \rScanLines remaining: "<< j << ' '<< std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = i / (image_width-1);
            auto v = j / (image_height-1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr<<" \n Done. \n";
}