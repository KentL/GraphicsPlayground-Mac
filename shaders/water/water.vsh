#version 150
uniform mat4 WorldViewProj;
uniform mat4 ReflectionWorldViewProj;
uniform mat4 World;
uniform mat3 WorldIT;
uniform float Time;
uniform float QuadWidth;
uniform float QuadHeight;

in vec4 a_position;
in vec3 a_normal;
in vec2 a_uv1;
in vec3 a_tangent;


out vec2 normalmap_uv1;
out vec2 normalmap_uv2;
out vec2 normalmap_uv3;


out vec3 v_normal;
out vec3 v_tangent;
out vec4 v_pos;
out vec4 reflectionVertexPos;
out vec4 refractionVertexPos;

void main()
{
	gl_Position = WorldViewProj * a_position;
    v_pos = World*a_position;
    reflectionVertexPos =ReflectionWorldViewProj*a_position;
    refractionVertexPos =gl_Position;
    v_normal = WorldIT * a_normal;
    
    vec4 t = World * vec4(a_tangent.xyz,1.0);
    v_tangent = t.xyz;
    
   
    normalmap_uv1.x = a_uv1.x*QuadWidth/100.0f+Time;
    normalmap_uv1.y = a_uv1.y*QuadHeight/100.0f+Time;
    
    normalmap_uv2.x = a_uv1.x*QuadWidth/100.0f-Time/2;
    normalmap_uv2.y = a_uv1.y*QuadHeight/100.0f-Time/2;
    
    normalmap_uv3.x = a_uv1.x*QuadWidth/100.0f+Time/3;
    normalmap_uv3.y = a_uv1.y*QuadHeight/100.0f-Time/3;

}
