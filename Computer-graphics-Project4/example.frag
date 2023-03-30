#version 450

layout(binding = 0) uniform sampler2D TextureMap;
layout(binding = 1) uniform sampler2D TextureMap_nor;
layout(binding = 2) uniform sampler2D TextureMap_spe;
layout(binding = 3) uniform sampler2D TextureMap_exp;
uniform float explode;
in vec3 frag_normal;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;
in vec3 frag_viewpoint;
in vec3 frag_pos;
in mat4 lightmodelfrag;
in vec3 frag_light_pos;
in float frag_but1;
in float frag_but2;
in float frag_but3;
out vec4 outColor;
vec3 newnor;
vec4 light_pos=vec4(0,0,3,1);
void main(){
	//if(explode>0.01)
	//light_pos=vec4(light_pos)*lightmodelfrag;
	vec3 light_dir= normalize( frag_light_pos-frag_pos );
	if(frag_but2==0.0)newnor=frag_normal;
	else if(frag_but2==1.0)
	{
		vec3 map_normal = texture(TextureMap_nor, texcoord).rgb;
		map_normal[0] = (map_normal[0] * 2.0 - 1.0);  // this normal is in tangent space// Transform normal vector to range [-1,1]    
		map_normal[1] = (map_normal[1] * 2.0 - 1.0);	
		map_normal[2] = (map_normal[2] * 2 - 1);
		newnor=map_normal.x*tangent+map_normal.y*bitangent+map_normal.z*frag_normal;	
		newnor=normalize(newnor);
	}

	vec3 diffuse_color;
	if(frag_but1<0.5) diffuse_color=vec3(0.35 ,0.3 ,0.15);
	else if(frag_but1>0.5)diffuse_color = texture(TextureMap, texcoord).rgb;// Get diffuse color
	diffuse_color = diffuse_color  * max(0, dot(newnor, vec3(light_dir) ));

    vec4 ambient = 0.3 * vec4(vec3(0.7 ,0.7 ,0.7 )*vec3(diffuse_color),1.0);// Ambient

    vec3 map_spec = texture(TextureMap_spe, texcoord).rgb;
	vec3 view_direction = normalize( vec3(0, 0, -1) - frag_pos);
	vec3 half_vector = normalize(light_dir + view_direction); 	// Calculate the speculat component.
	//map_spec=normalize(map_spec)*specular*-(map_spec.x-1);
	half_vector = normalize(-reflect(light_dir, newnor));
	vec3 specular;
	if(frag_but3<0.5)
	{
		if(frag_but2>0.5) specular = 0.5 *vec3(1,1,1) * pow(max(0, dot(newnor, half_vector)), 15);
		else if(frag_but2<0.5) specular = 0.01 *vec3(1,1,1) * pow(max(0, dot(newnor, half_vector)), 0.2);		
	}
	else if(frag_but3>0.5)
	{	
		if(frag_but2>0.5) specular = 0.5* map_spec*vec3(1,1,1) * pow(max(0, dot(newnor, half_vector)), 15);
		else if(frag_but2<0.5) specular = 0.01* map_spec*vec3(1,1,1) * pow(max(0, dot(newnor, half_vector)), 0.2);
	}


	vec4 result = ambient +  vec4(diffuse_color,1.0f)+ vec4(specular,1.0f) ;
	outColor = vec4(result);
	//outColor = vec4(map_spec,1);
	//outColor = vec4(frag_normal,1);
	//outColor = vec4(newnor,1.0f);
	//outColor = texture2D(TextureMap_spe, texcoord);
}