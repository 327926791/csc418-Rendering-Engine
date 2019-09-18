// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // from q6
  vec3 rand_v ;
float u, v, w, nk[2], nj[2], ni[2], noise ;
int ii, jj, kk ;

// get the bottom-left point of unit cubic
// the point of st is in the cubic
   ii = (st.x > 0) ? int(st.x) : int(st.x -1 ) ; 
   jj = (st.y > 0) ? int(st.y): int(st.y-1) ;
   kk = (st.z > 0) ? int(st.z) : int(st.z - 1);

// hermite interpolation
for (int i=ii; i<=ii+1; i++) {
    for (int j=jj; j<=jj+1; j++) {
        for (int k=kk; k<=kk+1; k++) {
           v = smooth_step(st.z-kk);
           // get random vection, then dot with vector(x-i,y-j,z-k)
           // then, mutiple with smooth values
           rand_v = random_direction(vec3(i,j,k)) ;
           //nk[k-kk] = smooth_step(st.x-i) * smooth_step(st.y-j) * smooth_step(st.z-k)* dot(rand_v,vec3(st.x-i, st.y-j, st.z-k)) ;
           nk[k-kk] = dot(rand_v,vec3(st.x-i, st.y-j, st.z-k)) ;
         }
         // interpolation
         u = smooth_step(st.y-jj) ;
         nj[j-jj] = mix(nk[0],nk[1],v) ;         
    }
    w = smooth_step(st.x-ii) ;
    ni[i-ii] = mix(nj[0], nj[1], u) ;
    
}
noise = mix(ni[0], ni[1], w) ;
noise=smooth_step(noise);

if (noise < -1)
   noise= -1 ;
if (noise > 1)
    noise = 1 ;

return noise/2 ;  
  /////////////////////////////////////////////////////////////////////////////
}

