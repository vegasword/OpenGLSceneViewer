#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

// Shader outputs.
out vec3 fragPos;
out vec2 texCoord;
out vec3 normal;

uniform mat4 mvp;
uniform mat4 model;


void main()
{
	// Compute current position.
	fragPos = vec3(model * vec4(aPos, 1.0f));
	texCoord = aTex;
	normal   = normalize(model * vec4(aNormal, 0.0)).xyz;

	// Outputs the positions/coordinates of all vertices.
	gl_Position = mvp * vec4(aPos, 1.0);

}