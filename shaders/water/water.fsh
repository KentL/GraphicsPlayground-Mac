#version 150

uniform sampler2D ReflectionTex;
uniform sampler2D RefractionTex;
uniform sampler2D NormalMap;
uniform vec4 ViewDir;
uniform vec3 LightDir;
uniform vec4 MatSpecular;
uniform vec4 LightSpecular;
uniform vec4 MatDiffuse;
uniform vec4 LightDiffuse;

in vec3 v_normal;
in vec3 v_tangent;

in vec2 refraction_uv;
in vec2 reflection_uv;
in vec2 normalmap_uv;

out vec4 PixelColor;

vec3 TangentToWorldSpace(vec3 normalMapSample, vec3 normal_world, vec3 tangent_world)
{
    vec3 nT = 2.0 * normalMapSample - 1.0;
    
    vec3 N = normal_world;
    vec3 T = normalize( tangent_world - dot(tangent_world, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = mat3(T,B,N);
    
    vec3 bumpNormal = TBN * nT;
    return bumpNormal;
}

void main()
{
    vec3 face_normal = normalize( v_normal );
    vec3 normalMapSample = texture(NormalMap, normalmap_uv).rgb;
    vec3 n = TangentToWorldSpace( normalMapSample, face_normal, v_tangent );
    
    vec3 lightDir = normalize(LightDir);
    vec3 R = reflect(-lightDir,n);
    vec3 viewDir = normalize(vec3(ViewDir.x,ViewDir.y,ViewDir.z));
    
    // Diffuse
    vec4 diffuse = MatDiffuse * LightDiffuse * max(0.0,dot(n, -lightDir));
    
    // Specular
    float specFactor = pow(max(dot(R, viewDir ), 0.0), MatSpecular.w);
    vec4 specular = specFactor * MatSpecular * LightSpecular;
    
    vec4 color = texture(RefractionTex,refraction_uv)*0.3+texture(ReflectionTex,reflection_uv)*0.7;
    
    vec4 light = clamp(specular+diffuse,0.8,20);
    //vec4 light = specular+diffuse;
    PixelColor = color * vec4(light.rgb, 1.0);
   // PixelColor = texture(NormalMap,normalmap_uv);
}


