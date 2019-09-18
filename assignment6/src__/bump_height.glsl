// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
    float adjust=0;
    
    //--- read perlin noise output ---
    float noise=improved_perlin_noise(s);
    
    adjust=noise;
    
    //--- Check domain ---
    if(adjust<-0.1)
    {
        adjust=0.1;
    }
    if(adjust>0.1)
    {
        adjust=0.1;
    }
    
    return adjust;
  /////////////////////////////////////////////////////////////////////////////
}
