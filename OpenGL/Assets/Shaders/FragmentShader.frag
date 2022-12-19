#version 450 core

#define MAX_LIGHTS 10

// Shaders output.
out vec4 fragColor;

// Light structure.
struct Light 
{
	float innerCone, outerCone, range, linear, quadratic;
	vec3 ambient, diffuse, specular, position, direction;
};

// Shader inputs.
in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

// Texture maps related.
uniform sampler2D tex;

// Camera related.
uniform vec3 viewPos;

// Lights related.
uniform Light lights[MAX_LIGHTS];

vec4 computeLight(Light light)
{
	bool isDirectional = (light.direction != vec3(0.0, 0.0, 0.0));
	bool isSpotlight   = (light.innerCone != 0.0 && light.outerCone != 0.0 && isDirectional);

	float angle = 0.0, intensity = 1.0;

	// Compute the light vector (point light only).
	vec3 lightVec = light.position == vec3(0, 0, 0) ? vec3(0, 0, 0) : light.position - fragPos;

	// Diffuse calculation.
	vec3  normal   = normalize(normal);
	vec3  lightDir = normalize(isDirectional ? -light.direction : lightVec);
	float diff     = max(dot(normal, lightDir), 0.0);

	// Specular calculation.
	vec3  viewDir    = normalize(viewPos - fragPos);
	vec3  halfwayVec = normalize(viewDir + lightDir);
	float spec       = pow(max(dot(normal, halfwayVec), 0), 32.0);

	// Light intensity calculation (directional light intensity is 1.0 by default).
	if (isSpotlight)
	{
		angle 	  = dot(vec3(0, -1, 0), -lightDir);
		intensity = clamp((angle - light.outerCone) / (light.innerCone - light.outerCone), 0.0, 1.0);
	}
	else if (!isDirectional)
	{
		intensity = 1.0 / (1 + light.linear * light.range + light.quadratic * pow(light.range, 2.0));
	}

	vec4 ambient  = texture(tex, texCoord) * vec4(light.ambient, 1);
	vec4 diffuse  = texture(tex, texCoord) * diff * intensity;
	vec4 specular = texture(tex, texCoord) * spec * intensity;

	return ambient + diffuse + specular;
}

void main()
{
	// Sum all computed lights to the current pixel.
    vec4 result = vec4(0,0,0,0);
	for (int i = 0; i < MAX_LIGHTS; i++)
        result += computeLight(lights[i]);

	fragColor = result;
}