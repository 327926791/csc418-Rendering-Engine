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
    float noise=0;
    
    //--- Generate 8 corners ---
    float x1,x2,y1,y2,z1,z2;
    x1=float(int(st[0]));
    y1=float(int(st[1]));
    z1=float(int(st[2]));
    x2=x1<0? (x1-1): (x1+1);
    y2=y1<0? (y1-1): (y1+1);
    z2=z1<0? (z1-1): (z1+1);
    
    //--- pesudo gradient vectors ---
    vec3 g1,g2,g3,g4,g5,g6,g7,g8;
    g1=random_direction(vec3(x1,y1,z1));
    g2=random_direction(vec3(x1,y1,z2));
    g3=random_direction(vec3(x1,y2,z1));
    g4=random_direction(vec3(x1,y2,z2));
    g5=random_direction(vec3(x2,y1,z1));
    g6=random_direction(vec3(x2,y1,z2));
    g7=random_direction(vec3(x2,y2,z1));
    g8=random_direction(vec3(x2,y2,z2));
    
    //--- 8 direction vectors(corner to point) ---
    vec3 d1,d2,d3,d4,d5,d6,d7,d8;
    d1=st-vec3(x1,y1,z1);
    d2=st-vec3(x1,y1,z2);
    d3=st-vec3(x1,y2,z1);
    d4=st-vec3(x1,y2,z2);
    d5=st-vec3(x2,y1,z1);
    d6=st-vec3(x2,y1,z2);
    d7=st-vec3(x2,y2,z1);
    d8=st-vec3(x2,y2,z2);
    
    //--- dot b/w direction and random vector ---
    float i1,i2,i3,i4,i5,i6,i7,i8;
    i1=dot(g1,d1);
    i2=dot(g2,d2);
    i3=dot(g3,d3);
    i4=dot(g4,d4);
    i5=dot(g5,d5);
    i6=dot(g6,d6);
    i7=dot(g7,d7);
    i8=dot(g8,d8);
    
    //--- interpolate ---
    float u,v,w;
    u=st[0]-float(x1);
    v=st[1]-float(y1);
    w=st[2]-float(z1);
    u=improved_smooth_step(u);
    v=improved_smooth_step(v);
    w=improved_smooth_step(w);
    //x direction(u)
    float lx1,lx2,lx3,lx4;
    lx1=mix(i1,i5,u);
    lx2=mix(i2,i6,u);
    lx3=mix(i3,i7,u);
    lx4=mix(i4,i8,u);
    //y direction(v)
    float ly1,ly2;
    ly1=mix(lx1,lx3,v);
    ly2=mix(lx2,lx4,v);
    //z direction(w)
    float lz;
    lz=mix(ly1,ly2,w);
    
    //--- Smooth step ---
    noise=improved_smooth_step(lz);
    if(noise<-1)
    {
        noise=-1;
    }
    if(noise>1)
    {
        noise=1;
    }
    
    return noise;
  /////////////////////////////////////////////////////////////////////////////
}

