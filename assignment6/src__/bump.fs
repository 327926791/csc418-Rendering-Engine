// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
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
    
    //--- get adjust height among normal (as vector)
    vec3 currPosition=sphere_fs_in;
    vec3 adjustHeight=bump_position(is_moon,sphere_fs_in);
    vec4 adjustPos=vec4(sphere_fs_in+adjustHeight,1);
    
    
    //--- Model ---
    //--- Model Transformation ---
    if(is_moon)
    {
        //get transformation matrices
        mat4 scale=uniform_scale(0.3);
        mat4 mol=model(is_moon,-animation_seconds/4);
        mat4 tran=translate(vec3(2,0,0));
        
        //scale
        adjustPos=scale*adjustPos;
        //transform
        adjustPos=tran*adjustPos;
        //module
        adjustPos=mol*adjustPos;
    }
    
    
    
    //--- Directional Light ---
    vec3 l;
    float angle=animation_seconds*M_PI*0.25;
    l=vec3(cos(angle),0.5,sin(angle));
    l=normalize(l);
    
    //view unit vector
    vec3 v;
    v= -1*normalize(adjustPos.xyz);
    
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
