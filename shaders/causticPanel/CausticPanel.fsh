#version 150

uniform sampler2D normalTex1;
uniform sampler2D normalTex2;

in vec3 v_normal;
in vec3 v_tangent;
in vec2 normal_uv1;
in vec2 normal_uv2;



out vec4 PixelColor;

vec3 TangentToWorldSpace(vec3 normalMapSample, vec3 normal_world, vec3 tangent_world)
{
    vec3 nT = 2.0 * normalMapSample - 1.0;

    vec3 N = normal_world;
    vec3 T = normalize( tangent_world - dot(tangent_world, N) * N);
    vec3 B = cross(N, T);

    mat3 TBN = mat3(T,B,N);

    vec3 bumpNormal = normalize(TBN * nT);

    return bumpNormal;
}

void main()
{
    vec3 nMapColor1 = texture(normalTex1, normal_uv1).rgb;
    vec3 nMapColor2 = texture(normalTex2, normal_uv2).rgb;

    vec3 face_normal = normalize( v_normal );
    vec3 normalMapSample = nMapColor1*0.8+nMapColor2*0.3;
    vec3 n = TangentToWorldSpace( normalMapSample, face_normal, v_tangent);


    PixelColor = vec4(n.yyy,0.5);
}


