// Inputs:
//   theta  amount y which to rotate (in radians)
// Return a 4x4 matrix that rotates a given 3D point/vector about the y-axis by
// the given amount.
mat4 rotate_about_y(float theta)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec4 c1,c2,c3,c4 ;
  c1 = vec4(cos(theta), 0, -sin(theta), 0) ;
  c2 = vec4(0,1,0,0) ;
  c3 = vec4(sin(theta),0, cos(theta), 0);
  c4 = vec4(0, 0, 0, 1) ;

  mat4 a = mat4(c1,c2,c3,c4);
  return a ;
  /////////////////////////////////////////////////////////////////////////////
}

