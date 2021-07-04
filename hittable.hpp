//
//  hittable.hpp
//  RayTracing
//
//  Created by yamato eguchi on 7/1/21.
//

#ifndef hittable_hpp
#define hittable_hpp

#include "rtweekend.hpp"

class material;

// p = point where a ray has struck the object
// normal = the normal to the point where the ray struck the object
//
struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
public:
    
    // hit is a pure virtual function.
    // A pure virtual function cannot have a body and it must be overridden
    // by classes that are derived from hittable
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif /* hittable_hpp */
