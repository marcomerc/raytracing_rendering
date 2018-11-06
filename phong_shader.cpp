#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <algorithm>    // std::max

// extern bool debug_pixel;

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 colors= vec3(0,0,0);
   vec3 colora= vec3(0,0,0);
   vec3 colord= vec3(0,0,0);
   vec3 colorss = vec3(0,0,0);
     colora =  world.ambient_color*color_ambient*world.ambient_intensity;// ambent +
      for(int i = 0; i < world.lights.size(); ++i){ // caculating the lighting of each light
         // vec3 L =   (world.lights.at(i)->position - intersection_point).normalized()  ;
         vec3 L =   (world.lights.at(i)->position - intersection_point)  ;
         vec3 R = (2*dot(L.normalized(),normal) * normal) - L.normalized();
         Ray hitObject(intersection_point,(world.lights.at(i)->position - intersection_point) );
         Hit theHit = world.Closest_Intersection(hitObject);
         double lightDist = L.magnitude();

         vec3 V = (world.camera.position- intersection_point).normalized();
          if( (theHit.dist == -1 || lightDist < theHit.dist)  && world.enable_shadows == 1){
             colord+= color_diffuse* world.lights.at(i)->Emitted_Light( (world.lights.at(i)->position - intersection_point))
               * fmax(dot( normal,(world.lights.at(i)->position - intersection_point).normalized() ),0 );
               colorss+=color_specular * world.lights.at(i)->Emitted_Light( (world.lights.at(i)->position - intersection_point))* pow( fmax(dot(R,V),0) ,specular_power); // specular

             }else if(world.enable_shadows == 0 ){
               colord+= color_diffuse* world.lights.at(i)->Emitted_Light( (world.lights.at(i)->position - intersection_point))
                 * fmax(dot( normal,(world.lights.at(i)->position - intersection_point).normalized() ),0 );
                 colorss+=color_specular * world.lights.at(i)->Emitted_Light( (world.lights.at(i)->position - intersection_point))* pow( fmax(dot(R,V),0) ,specular_power); // specular

             }



      }
      colors = colord +colora + colorss ;
    TODO; //determine the color
    return colors;
}
