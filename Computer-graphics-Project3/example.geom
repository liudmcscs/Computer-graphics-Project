#version 450

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
in vec3 geom_nor[3];
in vec2 geom_texcoord[3];
in vec3 geom_pos[3];
in vec3 geom_viewpoint[3];
in mat4 lightmodel[3];
in vec3 geom_light_pos[3];
in float geom_but1[3];
in float geom_but2[3];
in float geom_but3[3];
out mat4 lightmodelfrag;
out vec2 texcoord;
out vec3 frag_normal;
out vec3 tangent;
out vec3 bitangent;
out vec3 frag_pos;
out vec3 frag_viewpoint;
out vec3 frag_light_pos;
out float frag_but1;
out float frag_but2;
out float frag_but3;
vec3 edge1 ; 
vec3 edge2 ; 
vec2 deltaUV1 ;
vec2 deltaUV2 ;
float f;
void main()
{
	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		texcoord = geom_texcoord[i];
		frag_normal=geom_nor[i];
		frag_pos=geom_pos[i];
		lightmodelfrag=lightmodel[i];
		frag_viewpoint=geom_viewpoint[i];
		frag_light_pos=geom_light_pos[i];
		frag_but1=geom_but1[i];
		frag_but2=geom_but2[i];
		frag_but3=geom_but3[i];

		edge1 = geom_pos[0] - geom_pos[1];
		edge2 = geom_pos[2] - geom_pos[1];
		deltaUV1 = geom_texcoord[0] - geom_texcoord[1];
		deltaUV2 = geom_texcoord[2] - geom_texcoord[1];
		//
		//edge1 = geom_pos[i+0] - geom_pos[(i+1)%3];
		//edge2 = geom_pos[(i+2)%3] - geom_pos[(i+1)%3/*i+0*/];
		//deltaUV1 = geom_texcoord[i+0] - geom_texcoord[(i+1)%3];
		//deltaUV2 = geom_texcoord[(i+2)%3] - geom_texcoord[(i+1)%3/*i+0*/];
		f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
		tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		//tangent = normalize(tangent);

		bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		//bitangent = normalize(bitangent);  


		EmitVertex();
	}
	EndPrimitive();
}