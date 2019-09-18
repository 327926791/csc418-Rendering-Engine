// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
    //==== Blinn Phong Setup =====
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
    //n=vec3(1,1,1);
    
    //--- Directional Light ---
    vec3 l;
    float angle=animation_seconds*M_PI*0.25;
    l=vec3(cos(angle),0.5,sin(angle));
    l=normalize(l);
    
    //view unit vector
    vec3 v;
    v= -1*normalize(vec3(view_pos_fs_in[0],view_pos_fs_in[1],view_pos_fs_in[2]));
    
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
    
    
    //=== Noise ===
    float noise=improved_perlin_noise(sphere_fs_in+vec3(animation_seconds,animation_seconds*2,animation_seconds*0.5));
    
    if(is_moon)
    {
        
    }
    else
    {
        kd=mix(kd, vec3(1), noise);
        ka=mix(ka, vec3(1), noise);
        ks=mix(ks, vec3(1), noise);
    }
    
    color=blinn_phong(ka,kd,ks,p,n,v,l);
  /////////////////////////////////////////////////////////////////////////////
}
