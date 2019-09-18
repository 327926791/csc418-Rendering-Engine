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
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
    //function: f(x)=6x^5 - 15x^4 + 10x^3
    float val=6*pow(f,5)-15*pow(f,4)+10*pow(f,3);
    return val;
  /////////////////////////////////////////////////////////////////////////////
}
vec3 improved_smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
    float x=f[0];
    float y=f[1];
    float z=f[2];
    float valx=6*pow(x,5)-15*pow(x,4)+10*pow(x,3);
    float valy=6*pow(y,5)-15*pow(y,4)+10*pow(y,3);
    float valz=6*pow(z,5)-15*pow(z,4)+10*pow(z,3);
    
    
    return vec3(valx,valy,valz);
  /////////////////////////////////////////////////////////////////////////////
}
