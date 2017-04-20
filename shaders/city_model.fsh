#version 150

// Scene info
uniform mat4 WorldViewProj;
uniform vec3 ViewDir;

// Light Info
uniform vec4 LightAmbient;
uniform vec4 LightSpecular;
uniform vec4 LightDiffuse;
uniform vec3 LightDir;

// Material info
uniform vec4 MatAmbient;
uniform vec4 MatSpecular;
uniform vec4 MatDiffuse;

// Texture(s)
uniform sampler2D tex;

// Varyings
in vec3 v_normal;
in vec2 v_uv1;

out vec4 PixelColor;

void main()
{
	vec3 n = normalize( v_normal );

	// Ambient
	vec4 ambient = MatAmbient * LightAmbient;

	// Diffuse
	vec4 diffuse = MatDiffuse * LightDiffuse * max(0.0,dot(n, -LightDir));

	// Specular
	vec3 R = reflect(LightDir,n);
	float specFactor = pow(max(dot(R, -ViewDir), 0.0), MatSpecular.w);
	vec4 specular = specFactor * MatSpecular * LightSpecular;
    
	vec4 light = clamp(ambient + diffuse + specular, 0, 1);

    PixelColor = texture(tex, v_uv1) * vec4( light.rgb, 1.0);
}
