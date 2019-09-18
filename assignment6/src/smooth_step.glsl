// Filter an input value to perform a smooth step. This function should be a
// cubic polynomial with smooth_step(0) = 0, smooth_step(1) = 1, and zero first
// derivatives at f=0 and f=1. 
//
// Inputs:
//   f  input value
// Returns filtered output value
float smooth_step( float f)
{
/////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
 // smooth_step = -2x^3 + 3x^2 ; 

 float ret ;

 ret = -2 * pow(f,3) + 3 * pow(f,2) ;

 return ret ;
  /////////////////////////////////////////////////////////////////////////////
}

vec3 smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  float x, y, z ;

  x = -2*pow(abs(f.x),3) + 3 * pow(f.x,2) ;
  y = -2*pow(abs(f.y),3) + 3 * pow(f.y,2) ;
  z = -2*pow(abs(f.z),3) + 3 * pow(f.z,2) ;

  return vec3(x,y,z) ;
  /////////////////////////////////////////////////////////////////////////////
}
