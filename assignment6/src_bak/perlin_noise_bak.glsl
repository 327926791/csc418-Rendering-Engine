// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
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
           v = abs(st.z - k) ;
           
           // get random vection, then dot with vector(x-i,y-j,z-k)
           // then, mutiple with smooth values
           rand_v = random_direction(vec3(i,j,k)) ;
           nk[k-kk] = smooth_step(st.x-i) * smooth_step(st.y-j) * smooth_step(st.z-k)* dot(rand_v,vec3(st.x-i, st.y-j, st.z-k)) ;
         }
         // interpolation
         u = abs(st.y - j) ;
         nj[j-jj] = (1.0 -v)*nk[0] + v * nk[1] ;         
    }
    w = abs(st.z - i) ;
    ni[i-ii] = (1.0-u)*nj[0] + u * nj[1] ;
}
noise = (1-w) * ni[0] + w * ni[1] ;

return noise ;  /////////////////////////////////////////////////////////////////////////////
}

