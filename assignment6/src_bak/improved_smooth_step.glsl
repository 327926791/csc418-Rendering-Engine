// Filter an input value to perform an even smoother step. This function should
// be a quintic polynomial with improved_smooth_step(0) = 0,
// improved_smooth_step(1) = 1, and zero first _and_ second derivatives at f=0
// and f=1. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   f  input value
// Returns filtered output value
float improved_smooth_step( float f)
{
// f = 6x^5 - 15x^4 + 10 x^3  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  float ret ;

  ret = 6 * pow(f,5) - 15 * pow(f,4) + 10 * pow(f,3) ;
  return ret;
  /////////////////////////////////////////////////////////////////////////////
}
vec3 improved_smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec3 ret ;

  ret.x = 6 * pow(f.x,5) - 15 * pow(f.x,4) + 10 * pow(f.x,3) ;
  ret.y = 6 * pow(f.y,5) - 15 * pow(f.y,4) + 10 * pow(f.y,3) ;
  ret.z = 6 * pow(f.z,5) - 15 * pow(f.z,4) + 10 * pow(f.z,3) ;

  return ret;
  /////////////////////////////////////////////////////////////////////////////
}
