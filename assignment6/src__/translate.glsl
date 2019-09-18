// Inputs:
//   t  3D vector by which to translate
// Return a 4x4 matrix that translates and 3D point by the given 3D vector
mat4 translate(vec3 t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec4 c1,c2,c3,c4 ;
  c1 = vec4(1,0,0,0) ;
  c2 = vec4(0,1,0,0);
  c3 = vec4(0,0,1,0);
  c4 = vec4(t.x, t.y, t.z, 1) ;
  mat4 a =mat4(c1,c2,c3,c4);
 
  return a;
  /////////////////////////////////////////////////////////////////////////////
}

