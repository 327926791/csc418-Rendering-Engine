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
// permutation array store integer from 0 to 255
vec2 a,b,c ;
float total ;

a = random2(seed) ;
b = random2(seed) ;
c = random2(seed) ;

  total = pow(2*a.x-1,2)+pow(2*b.x-1,2)+pow(2*c.x-1,2) ;
      if ( total > 1) {
          a.x = (2*a.x-1) / sqrt(total) ;
          b.x = (2*b.x-1) / sqrt(total) ;
          c.x = (2*c.x-1) / sqrt(total) ;
      }

	return   normalize(vec3(a.x, b.x, c.x)) ;


  /////////////////////////////////////////////////////////////////////////////
}
