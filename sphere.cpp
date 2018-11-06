#include "sphere.h"
#include "ray.h"
#include <algorithm>    // std::max

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
//     TODO;
     vec3 v = ray.endpoint -  center ; // o -c
     vec3 u =  ray.direction;  // l
    Hit result;
    result.dist = -1;
    double inside =  sqrt(pow(dot(v,u),2) -  (v.magnitude_squared() - pow(radius,2)));
    double vu = - dot(u,v);
    double t1 = vu + inside;
    double t2 = vu - inside;
    if(inside < 0 ){
      result.dist = -1;
    }else if( t1 > pow(10,-4) || t2 > pow(10,-4) ){
      if ( t1 > t2) {
          result.object = this;
          result.dist = t2;
          result.part = 0;

      }else{
         result.object = this;
         result.dist = t1;
         result.part = 0;

      }
    }

    return result;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{

    vec3 normal = (point - center).normalized();
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
