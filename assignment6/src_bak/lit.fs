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
  vec3 kd, ka , ks, l, kd_moon,v ;
  float p ;

  kd = vec3(0.1, 0.1, 1.0) ;
  kd_moon = vec3(0.5,0.5,0.5) ;
  ka =  kd * 1.5 ;
  ks = vec3(1.0, 1.0, 1.0) ;
  p = 32.0 ;
 
  float theta = -0.5 * animation_seconds * M_PI;

  mat3 rr = mat3(cos(theta), 0, sin(theta),
              0 ,1 , 0, 
	     -sin(theta), 0, cos(theta)) ;
			  
  l = normalize(vec3(cos(theta),0.5,sin(theta))); 
  v = normalize(vec3(-view_pos_fs_in)) ;
  
  if (is_moon) {
      color = blinn_phong(ka, kd_moon, ks, p, normalize(rr*normal_fs_in), v, l) ;
   }
  else {
     color = blinn_phong(ka, kd, ks, p, normal_fs_in, v, l) ;
  }

  /////////////////////////////////////////////////////////////////////////////
}
