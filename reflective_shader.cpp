#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"
#include "light.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 reflective = (ray.direction- (2*(dot(normal,ray.direction))*normal)).normalized()  ;
    if (debug_pixel) {
      // std::cout << "normal of reflective  "  <<  reflective << '\n';
      // std::cout << "intersection " <<  intersection_point << '\n';

}
    Ray reflectiveRay(intersection_point,reflective);


    if (debug_pixel) {
      if(recursion_depth == 3){
        std::cout << "test" << '\n';
      }
      // std::cout << "recursion_depth "  <<  recursion_depth<< '\n';
    //   std::cout << "intersection " <<  intersection_point << '\n';
    //   std::cout << "normal " <<  normal << '\n';
    //
    //   std::cout << "reflectily " << reflectivity << '\n';
    // std::cout<< "the final color in reflective thing " << c << '\n';
    // std::cout <<  "the reflective color  " <<  world.Cast_Ray(reflectiveRay, recursion_depth+1) << '\n';

    }

      // std::cout <<  "the reflective in the shader reflective " << recursion_depth << '\n';

      vec3 c = shader->Shade_Surface(ray,intersection_point,normal,recursion_depth);
      if (debug_pixel) {
        std::cout << "between the color and reursion " <<  recursion_depth << '\n';
        /* code */
      }
      vec3 r =  world.Cast_Ray(reflectiveRay, recursion_depth+1);


      if (debug_pixel) {

        /* code */
      }

  if(reflectivity !=  0 && reflectivity != 1 ){
    color = c + reflectivity * ( r - c  ) ;
  }else if(reflectivity  == 0){
      color = c;

  }else if(reflectivity  == 1){
        color = r ;
  }


    // std::cout <<  "the reflective final color" << color << '\n';
//
if (debug_pixel) {
  // std::cout << "recursion_depth "  <<  recursion_depth<< '\n';
  // std::cout <<  "the reflective color  " <<  r << '\n';
//   std::cout << "intersection " <<  intersection_point << '\n';
//   std::cout << "normal " <<  normal << '\n';
//
  // std::cout << "reflectily " << reflectivity << '\n';
// std::cout<< "the final color of the thing " << color << '\n';
// std::cout <<  "the objects color " << shader->Shade_Surface(ray,intersection_point,normal,recursion_depth) << '\n';
// std::cout <<  "the reflective color  " <<  world.Cast_Ray(reflectiveRay, recursion_depth+1) << '\n';

}


     // colors = colord +colora + colorss;

    TODO; // determine the color
    return color;
}
