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
    //function f(x)= (-2) x^3 + (3) x^2
    float y=-2*pow(f,3)+3*pow(f,2);
    
    
    
    return y;
  /////////////////////////////////////////////////////////////////////////////
}

vec3 smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
    vec3 y;
    float y1=-2*pow(f[0],3)+3*pow(f[0],2);
    float y2=-2*pow(f[1],3)+3*pow(f[1],2);
    float y3=-2*pow(f[2],3)+3*pow(f[2],2);
    y=vec3(y1,y2,y3);
    return y;
  /////////////////////////////////////////////////////////////////////////////
}
