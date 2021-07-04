//
//  ray.hpp
//  RayTracing
//
//  Created by yamato eguchi on 6/30/21.
//

#ifndef ray_hpp
#define ray_hpp

#include "vec3.hpp"

class ray {
public:
    point3 orig;
    vec3 dir;
    
public:
    // Default constructor
    ray() {}
    // Constructor
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
    
    // Get value functions
    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }
    
    // at function
    // returns P(t)
    // Remember:
    //    P(t) = A + tb
    point3 at(double t) const {
        return orig + t*dir;
    }
};


#endif /* ray_hpp */
