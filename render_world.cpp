#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include "vec.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
//finding he closest object
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    TODO;
    double min_dist = std::numeric_limits<double>::max();
    Hit theHit;
    theHit.dist = -1;
    for(int i = 0; i < objects.size(); i++){
      Hit possibleHit =  objects.at(i)->Intersection(ray,0);
      if(possibleHit.dist != -1 &&  possibleHit.dist > pow(10,-4)){
         if( min_dist > possibleHit.dist  ){
           theHit= possibleHit;
           min_dist = possibleHit.dist;

         }
      }

    }
    return theHit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    TODO; // set up the initial view ray here
    Ray ray(camera.position, (camera.World_Position(pixel_index)  - camera.position).normalized());
    vec3 color=Cast_Ray(ray,0);
    camera.Set_Pixel(pixel_index,Pixel_Color(color)); // not sure
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++){
            Render_Pixel(ivec2(i,j));
        }




}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    vec3 LightColor;

    if(recursion_depth  == recursion_depth_limit) {
      return vec3(0,0,0);
    }
    Hit closestIntersection = this->Closest_Intersection(ray);
    if(closestIntersection.dist != -1 ){
      color=closestIntersection.object->material_shader->Shade_Surface(ray,ray.Point(closestIntersection.dist),
            closestIntersection.object->Normal( ray.Point(closestIntersection.dist),closestIntersection.part),recursion_depth);
    }else{
      const vec3 f;

      color = background_shader->Shade_Surface(ray,ray.Point(closestIntersection.dist),f,recursion_depth);
    }
    TODO; // determine the color here




    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
