// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
    
    //color param
    vec3 ka,kd,ks;
    //phong exponential param
    int p=1000;
    //shading vectors:
    //normal vector
    vec3 n;
    if(is_moon)
    {
        float angle=-0.25*animation_seconds*2*M_PI;
        mat3 rot=mat3(cos(angle),0,sin(angle),
                      0,1,0,
                      -sin(angle),0,cos(angle)) ;
        
        //rotate normal vector
        n=rot*normal_fs_in;
    }
    else
    {
        n=normal_fs_in;
    }
    
    
    //--- Directional Light ---
    vec3 l;
    float angle=animation_seconds*M_PI*0.25;
    l=vec3(cos(angle),0.5,sin(angle));
    l=normalize(l);
    
    //view unit vector
    vec3 v;
    v= -1*normalize(vec3(view_pos_fs_in[0],view_pos_fs_in[1],view_pos_fs_in[2]));
    //v=vec3(0,0,1);
    
    if(is_moon)
    {
        //color params
        ka=vec3(0.61,0.61,0.61);
        kd=vec3(0.61,0.61,0.61);
        ks=vec3(0.61,0.61,0.61);
    }
    else
    {
        //color params
        ka=vec3(0,0.45,0.9);
        kd=vec3(0,0.45,0.9);
        ks=vec3(0,0.45,0.9);
    }
    
    color=blinn_phong(ka,kd,ks,p,n,v,l);
    
    
    
  /////////////////////////////////////////////////////////////////////////////
}
