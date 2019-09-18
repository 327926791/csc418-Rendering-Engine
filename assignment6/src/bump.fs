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
vec3 calcuate_bump_normal(bool is_moon, vec3 s) {
	vec3 bump_pos1, bump_pos2, bump_pos3 ;
	vec3 T, B ;

	tangent(s, T, B) ;
	bump_pos1 = bump_position(is_moon, s+0.0001*T) ;
	bump_pos2 = bump_position(is_moon, s) ;
	bump_pos3 = bump_position(is_moon, s+0.0001*B) ;

	return cross(bump_pos1-bump_pos2, bump_pos3-bump_pos2) ;
}

void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

    mat4 s, t, r ,mod; 
    vec4 pos_cs_in ;
    vec3 bump_normal;

	//calcuate normal on bump surface
	bump_normal = calcuate_bump_normal(is_moon, normal_fs_in) ;

    mod = model(is_moon, animation_seconds/4) ;
    s = uniform_scale(0.3) ;
    t = translate(vec3(2,0,0));
	 
    if (is_moon) {
        pos_cs_in = view*mod*t*s*vec4(sphere_fs_in, 1.0) ;
    }
    else
        pos_cs_in = view*vec4(sphere_fs_in,1.0);


    float p;
	vec3 kd, ka, ks;
    vec3 l, v ;

    p = 1000.0 ;
 
    float theta = 0.5 * animation_seconds * M_PI;

    mat3 rr = mat3(cos(theta), 0, -sin(theta), 0 ,1 , 0, 
	      sin(theta), 0, cos(theta)) ;
			  
    l = normalize(vec3(cos(theta/2),0.5,sin(theta/2))); 
    v = -1 * normalize(vec3(pos_cs_in)) ;
  
    if (is_moon) {
        kd =vec3(0.5, 0.5, 0.5) ;
        ka = kd ;
        ks = kd ;
     // kd = mix(kd, vec3(1), noise) ;
	 //color =mix(blinn_phong(ka, kd, ks, p, rr*normal_fs_in, v, l),blinn_phong(ka, kd, ks, p, rr*bump_normal, v, l), 0.5) ;
        color =blinn_phong(ka, kd, ks, p, rr*bump_normal, v, l) ;
    }
    else {
       kd = vec3(0.2, 0.4, 0.9) ;
       ka = kd ;
       ks = kd ;
       //kd = mix(kd, vec3(1), noise) ;
	  // color = mix(blinn_phong(ka, kd, ks, p, normal_fs_in, v, l), blinn_phong(ka, kd, ks, p, bump_normal, v, l),0.5) ;
       color = blinn_phong(ka, kd, ks, p, bump_normal, v, l) ;
    }
  /////////////////////////////////////////////////////////////////////////////
}


