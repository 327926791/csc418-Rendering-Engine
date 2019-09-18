// Inputs:
//   s  amount to scale in all directions
// Return a 4x4 matrix that scales and input 3D position/vector by s in all 3
// directions.
mat4 uniform_scale(float s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec4 c1, c2, c3, c4 ;
  c1=vec4(s,0,0,0) ;
  c2=vec4(0,s, 0, 0) ;
  c3=vec4(0,0, s, 0);
  c4=vec4(0,0,0,1) ;
  
  mat4 ss = mat4(c1,c2,c3,c4) ;
  
  
  return ss;
  /////////////////////////////////////////////////////////////////////////////
}

