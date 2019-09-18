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
  vec3 I = vec3(1.1, 1.1, 1.1);
  vec3 h ;
  
  h = normalize(l + v );

  vec3 intensity = ka * vec3(0.1,0.1,0.1) + kd * I * max(0.0, dot(n,l)) + ks * I * pow(max(0.0, dot(n,h)),p) ;
  return intensity ;
  /////////////////////////////////////////////////////////////////////////////
}


