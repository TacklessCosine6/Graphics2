/*
	Phong (FS)
	By Dan Buckstein
	Fragment shader that computes Phong shading.
	
	Modified by: ______________________________________________________________
*/

// version
#version 410


// ****
// varyings
layout(location = 0) in vec4 pos;
layout(location = 2) in vec4 normals;
layout(location = 8) in vec4 texCoord;


// ****
// uniforms
uniform mat4 mvp;
uniform vec4 lightPos;
uniform vec4 eyePos;

// ****
// target
out vertex
{
	vec4 normal;
	vec4 lightVec;
	vec4 eyeVec;
	vec2 texCoord;
} data;

// shader function
void main()
{
	gl_Position = mvp * pos;
	data.normal = vec4(normals.xyz, 0.0f);
	data.lightVec = lightPos - pos;
	data.eyeVec = eyePos - pos;
	data.texCoord = texCoord.xy;
	// ****
	// this example: phong shading algorithm

	// ****
	// output: phong

	// ****
	// extra: apply textures as well
}