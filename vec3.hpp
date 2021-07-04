//
//  vec3.hpp
//  RayTracing
//
//  Created by yamato eguchi on 6/29/21.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <cmath>
#include <iostream>

class vec3 {
public:
    double e[3];
public:
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
    
    // Get value functions:
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    
    // Negation operator
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    
    // Const operator[]. Only used for reading
    double operator[](int i) const { return e[i]; }

    // Non-const operator[]. Used for writing
    double& operator[](int i) { return e[i]; }
    
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    
    vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    
    vec3& operator/=(const double t) {
        return *this *= 1/t;
    }
    
    // Calculates distance of 3D point (x, y, z)
    double length() const { return sqrt(length_squared()); }
    
    // Calculated squared distance of 3D point.
    // This is fast and useful way wnen wanting to compare relative
    // distances or when you wish to determine if a vector is of unit length
    double length_squared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    
    inline static vec3 random() {
        vec3 vec(random_double(), random_double(), random_double());
        return vec;
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }
    
//  If the random unit vector we generate is exactly opposite the normal vector, the two will sum to zero, which will result in a zero scatter direction vector. This leads to bad scenarios later on (infinities and NaNs), so we need to intercept the condition before we pass it on:
    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

};

// Type aliases for vec3
using point3 = vec3;
using color = vec3;


// UTILITY FUNCTIONS

inline std::ostream& operator<<(std::ostream& out, const vec3 & rhs) {
    out << "(" << rhs.e[0] << ", " << rhs.e[1] << ", " << rhs.e[2] << ")";
    return out;
}

inline vec3 operator+(const vec3& lhs, const vec3& rhs) {
    return (vec3{lhs.e[0] + rhs.e[0], lhs.e[1] + rhs.e[1], lhs.e[2] + rhs.e[2]});
}

inline vec3 operator-(const vec3& lhs, const vec3& rhs) {
    return (vec3{lhs.e[0] - rhs.e[0], lhs.e[1] - rhs.e[1], lhs.e[2] - rhs.e[2]});
}

inline vec3 operator*(double lhs, const vec3& rhs) {
    return (vec3{lhs * rhs.e[0], lhs * rhs.e[1], lhs * rhs.e[2]});
}

inline vec3 operator*(const vec3& lhs, double rhs) {
    return (rhs * lhs);
}

inline vec3 operator*(const vec3& lhs, const vec3& rhs) {
    return (vec3{lhs.e[0] * rhs.e[0], lhs.e[1] * rhs.e[1], lhs.e[2] * rhs.e[2]});
}

inline vec3 operator/(const vec3& lhs, double rhs) {
    return (1/rhs) * lhs;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

//The reflected ray direction in red is just 𝐯+2𝐛. In our design, 𝐧 is a unit vector, but 𝐯 may not be. The length of 𝐛 should be 𝐯⋅𝐧. Because 𝐯 points in, we will need a minus sign, yielding:
vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

#endif /* vec3_hpp */
