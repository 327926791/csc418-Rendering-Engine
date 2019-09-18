// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
    vec3 vec=vec3(1,0,0);
    
    vec2 ran1,ran2,ran3;
    ran1=random2(seed);
    ran2=random2(seed);
    ran3=random2(seed);


    vec=vec3(2*dot(ran1,ran1)-1,2*dot(ran2,ran2)-1, 2*dot(ran3,ran3)-1);
    
    //normalize
    vec=normalize(vec);
    return vec;
  /////////////////////////////////////////////////////////////////////////////
}
