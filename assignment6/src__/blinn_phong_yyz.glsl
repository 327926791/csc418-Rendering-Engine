// Compute Blinn-Phong Shading given a material specification, a point on a
// surface and a light direction. Assume the light is white and has a low
// ambient intensity.
//
// Inputs:
//   ka  rgb ambient color
//   kd  rgb diffuse color
//   ks  rgb specular color
//   p  specular exponent (shininess)
//   n  unit surface normal direction
//   v  unit view direction
//   l  unit light direction
// Returns rgb color
vec3 blinn_phong(
  vec3 ka,
  vec3 kd,
  vec3 ks,
  float p,
  vec3 n,
  vec3 v,
  vec3 l)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
    //light
    vec3 I=vec3(1.1,1.1,1.1);
    vec3 Ia=vec3(0.1,0.1,0.1);
    
    //normalize
    n=normalize(n);
    l=normalize(l);
    v=normalize(v);
    
    //---ambient---
    vec3 ambient=ka*Ia;
    
    //--- diffuse ---
    float dotnl=dot(n,l);
    dotnl=dotnl<0? 0:dotnl;
    vec3 diffuse=kd*I*dotnl;
    
    //--- specular ---
    vec3 h=normalize(l+v);
    float nh=dot(n,h);
    nh=nh<0?0:nh;
    nh=pow(nh,p);
    vec3 specular=ks*I*nh;
    
    return ambient+diffuse+specular;
  /////////////////////////////////////////////////////////////////////////////
}


