#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
out vec3 geom_pos;
out vec2 geom_texcoord;
out vec3 geom_nor;
out vec3 geom_light_pos;
out mat4 lightmodel;
out vec3 geom_viewpoint;
out float geom_but1;
out float geom_but2;
out float geom_but3;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat4 ligthModelView;
uniform float button1;
uniform float button2;
uniform float button3;
void main() {
	gl_Position = Projection * ModelView * vec4(pos, 1.0);
	//vec4 light_temp=Projection*ligthModelView*vec4(0,0,3,1);
	geom_light_pos=(Projection*ligthModelView*vec4(0,0,3,1)).xyz/(Projection*ligthModelView*vec4(0,0,3,1)).w;       //vec3(light_temp[0],light_temp[1],light_temp[2]);
	geom_viewpoint=(Projection *vec4(0,0,3,1)).xyz/(Projection*ligthModelView*vec4(0,0,3,1)).w;
	geom_texcoord = texcoord;
	geom_nor=(Projection * ModelView*vec4(normal,0)).xyz;
	geom_pos=(Projection * ModelView*vec4(pos,1)).xyz/(Projection * ModelView*vec4(pos,1)).w;
	lightmodel=ligthModelView;
	geom_but1=button1;
	geom_but2=button2;
	geom_but3=button3;
}