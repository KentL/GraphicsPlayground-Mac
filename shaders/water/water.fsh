#version 150

uniform sampler2D ReflectionTex;
uniform sampler2D RefractionTex;
uniform sampler2D NormalMap;
uniform sampler2D NormalMap2;
uniform sampler2D NormalMap3;
uniform vec4 ViewDir;
uniform vec3 LightDir;
uniform vec4 MatSpecular;
uniform vec4 LightSpecular;
uniform vec4 MatDiffuse;
uniform vec4 LightDiffuse;
uniform float WaveHeight;
uniform bool UseNormal;
uniform vec3 CameraPos;

in vec3 v_normal;
in vec3 v_tangent;
in vec4 v_pos;

in vec2 refraction_uv;
in vec2 reflection_uv;
in vec2 normalmap_uv1;
in vec2 normalmap_uv2;
in vec2 normalmap_uv3;


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
    if(UseNormal){
        //Normal
        vec3 nMapColor1 = texture(NormalMap, normalmap_uv1).rgb;
        vec3 nMapColor2 = texture(NormalMap2, normalmap_uv2).rgb;
        vec3 nMapColor3 = texture(NormalMap3, normalmap_uv3).rgb;
        
        vec3 face_normal = normalize( v_normal );
        vec3 normalMapSample = nMapColor1*0.8+nMapColor2*0.3+nMapColor3*0.5;
        vec3 n = TangentToWorldSpace( normalMapSample, face_normal, v_tangent );
        
        vec3 lightDir = normalize(LightDir);
        vec3 R = reflect(-lightDir,n);
        vec3 viewDir = normalize(vec3(ViewDir.x,ViewDir.y,ViewDir.z));
        
        
        // Diffuse
        vec4 diffuse = MatDiffuse * LightDiffuse * max(0.0,dot(n, -lightDir));
        
        // Specular
        float specFactor = pow(max(dot(R, viewDir ), 0.0), MatSpecular.w);
        vec4 specular = specFactor * MatSpecular * LightSpecular;
        
        //perturbation
        vec2 perturbation1 = WaveHeight*(nMapColor1.xy-0.5);
        vec2 perturbation2 = WaveHeight*(nMapColor2.xy-0.5);
        vec2 perturbation3 = WaveHeight*(nMapColor3.xy-0.5);
        vec2 perturbation = perturbation1+perturbation2+perturbation3;
        
        //Fresnel
        vec3 eyeDir = normalize(v_pos.xyz - CameraPos);
        float fangle = 1+dot(eyeDir, n);
        fangle = pow(fangle ,5);
        float fresnelTerm = 1/fangle;
        fresnelTerm = clamp(fresnelTerm,0.0f,1.0f);
        
        vec4 color = texture(RefractionTex,refraction_uv+perturbation)*(1-fresnelTerm)+texture(ReflectionTex,reflection_uv+perturbation)*fresnelTerm;
        
        vec4 light = clamp(specular+diffuse,0.9,5);
        
        PixelColor = color * vec4(light.rgb, 1.0);
    }else{
        PixelColor = texture(RefractionTex,refraction_uv)*0.3+texture(ReflectionTex,reflection_uv)*0.7;
    }
    
}

