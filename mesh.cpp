#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    TODO;
    double dist = 0;
    Hit result;
    result.dist = -1;
    double min_dist=0;
    bool usedYet  = true;
    int trian = 0;
    for(int i = 0; i < triangles.size();i++){
        if(Intersect_Triangle(ray,i,dist)){
            if(usedYet){
              usedYet = false;
              min_dist = dist;
              result.part = i;
            }else if( min_dist > dist){
              min_dist =  dist;
              result.part = i;
        }
        trian++;

      }
  }
    result.object = this;
    result.dist = min_dist;
    return result;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const // the nornal of the p
{
    assert(part>=0);
    TODO;

    vec3  vectorA = vertices.at(triangles.at(part)[1])  - vertices.at(triangles.at(part)[0]) ;
    vec3  vectorB = vertices.at(triangles.at(part)[2])  - vertices.at(triangles.at(part)[0]) ;
    vec3  normal   = cross(vectorA,vectorB).normalized();

    vec3  vectorAa =vertices.at(triangles.at(part)[1])  - vertices.at(triangles.at(part)[0]) ;
    vec3  vectorBa =vertices.at(triangles.at(part)[2])  - vertices.at(triangles.at(part)[0]) ;
    vec3 Na=cross(vectorAa,vectorBa).normalized();

    vec3  vectorAb =vertices.at(triangles.at(part)[2])  - vertices.at(triangles.at(part)[1]) ;
    vec3  vectorBb =vertices.at(triangles.at(part)[0])  - vertices.at(triangles.at(part)[1]) ;
    vec3 Nb=cross(vectorAb,vectorBb).normalized();

    vec3  vectorAc =vertices.at(triangles.at(part)[0])  - vertices.at(triangles.at(part)[2]) ;
    vec3  vectorBc =vertices.at(triangles.at(part)[1])  - vertices.at(triangles.at(part)[2]) ;
    vec3 Nc=cross(vectorAc,vectorBc).normalized();

    vec3  aa =vertices.at(triangles.at(part)[1])  - vertices.at(triangles.at(part)[0]) ;
    vec3  ba =vertices.at(triangles.at(part)[2])  - vertices.at(triangles.at(part)[0]) ;
    vec3  ab =vertices.at(triangles.at(part)[2])  - vertices.at(triangles.at(part)[1]) ;
    vec3  ac =vertices.at(triangles.at(part)[0])  - vertices.at(triangles.at(part)[2]) ;


    double beta  = dot(cross(ab, point-vertices.at(triangles.at(part)[1])), normal ) / dot(cross(aa,ba), normal);
    double delta = dot(cross(ac, point-vertices.at(triangles.at(part)[2])), normal )/ dot(cross(aa,ba), normal);
    double gama  = dot(cross(aa, point-vertices.at(triangles.at(part)[0])), normal) / dot(cross(aa,ba), normal);
    vec3 Nq =  (beta*normal + delta*Nb + gama*Nc).normalized();

    return Nq;
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    TODO;

        vec3  vectorA = vertices.at(triangles.at(tri)[1])  - vertices.at(triangles.at(tri)[0]) ;
        vec3  vectorB = vertices.at(triangles.at(tri)[2])  - vertices.at(triangles.at(tri)[0]) ;
        vec3  normal   = cross(vectorA,vectorB).normalized();
        double d=dot(normal,vertices.at(triangles.at(tri)[0]));
        dist =  (d - (dot(normal,ray.endpoint)))/dot(normal,ray.direction);
        vec3 point = ray.Point(dist);
        vec3 Q = ray.Point(dist);

        vec3  vectorAa =vertices.at(triangles.at(tri)[1])  - vertices.at(triangles.at(tri)[0]) ;
        vec3  vectorBa =vertices.at(triangles.at(tri)[2])  - vertices.at(triangles.at(tri)[0]) ;
        vec3  vectorAb =vertices.at(triangles.at(tri)[2])  - vertices.at(triangles.at(tri)[1]) ;
        vec3  vectorAc =vertices.at(triangles.at(tri)[0])  - vertices.at(triangles.at(tri)[2]) ;
     Hit result;
     result.dist = -1;
     ivec3 triangle =triangles.at(tri);
     if(
          dot(cross(vertices.at(triangle[1])  - vertices.at(triangle[0]), Q -  vertices.at(triangle[0]) ),normal)   >= 0  &&
          dot(cross(vertices.at(triangle[2])  - vertices.at(triangle[1]), Q -  vertices.at(triangle[1]) ),normal)   >= 0  &&
          dot(cross(vertices.at(triangle[0])  - vertices.at(triangle[2]), Q -  vertices.at(triangle[2]) ),normal)   >= 0  )
     {
       dist =  (d - (dot(normal,ray.endpoint)))/dot(normal,ray.direction);
       double beta  = dot(cross(vectorAb, point-vertices.at(triangles.at(tri)[1])), normal ) / dot(cross(vectorAa,vectorBa), normal);
       double delta = dot(cross(vectorAc, point-vertices.at(triangles.at(tri)[2])), normal )/ dot(cross(vectorAa,vectorBa), normal);
       double gama  = dot(cross(vectorAa, point-vertices.at(triangles.at(tri)[0])), normal) / dot(cross(vectorAa,vectorBa), normal);
       if(dist > small_t && beta >weight_tolerance && delta > weight_tolerance && gama > weight_tolerance ){
         return true;
       }
       dist = -1;
     }
    return false;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
