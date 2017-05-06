#version 150
uniform mat4 WorldViewProj;
uniform mat4 ReflectionWorldViewProj;
uniform mat4 World;
uniform mat3 WorldIT;

uniform float time;

in vec4 a_position;
in vec3 a_normal;
in vec2 a_uv1;
in vec3 a_tangent;

out vec2 reflection_uv;
out vec2 refraction_uv;
out vec2 normalmap_uv1;
out vec2 normalmap_uv2;
out vec2 normalmap_uv3;


out vec3 v_normal;
out vec3 v_tangent;

void main()
{
	gl_Position = WorldViewProj * a_position;
    vec4 reflectionVertexPos =ReflectionWorldViewProj*a_position;
    vec4 refractionVertexPos =WorldViewProj*a_position;
    vec3 n = WorldIT * a_normal;
    
    v_normal = n;
    
    vec4 t = World * vec4(a_tangent.xyz,1.0);
    v_tangent = t.xyz;
    
    refraction_uv.x = refractionVertexPos.x/refractionVertexPos.w/2.0+0.5;
    refraction_uv.y = refractionVertexPos.y/refractionVertexPos.w/2.0+0.5;
    reflection_uv.x = reflectionVertexPos.x/reflectionVertexPos.w/2.0+0.5;
    reflection_uv.y = reflectionVertexPos.y/reflectionVertexPos.w/2.0+0.5;
    
    normalmap_uv1.x = a_uv1.x+time;
    normalmap_uv1.y = a_uv1.y+time;
    
    normalmap_uv2.x = a_uv1.x-time/2;
    normalmap_uv2.y = a_uv1.y-time/2;
    
    normalmap_uv3.x = a_uv1.x+time/4;
    normalmap_uv3.y = a_uv1.y-time/4;
    
    
    
////
//    refraction_uv1.x = clamp(refractionVertexPos.x/refractionVertexPos.w/2.0+0.5,0.0001,0.9999);
//    refraction_uv1.y = clamp(refractionVertexPos.y/refractionVertexPos.w/2.0+0.5,0.0001,0.9999);
//    reflection_uv1.x = clamp(reflectionVertexPos.x/reflectionVertexPos.w/2.0+0.5,0.0001,0.9999);
//    reflection_uv1.y = clamp(reflectionVertexPos.y/reflectionVertexPos.w/2.0+0.5,0.0001,0.9999);

}
