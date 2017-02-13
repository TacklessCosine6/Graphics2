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
uniform sampler2D tex_dm;
uniform sampler2D tex_sm;


// ****
// target
in vertex
{
	vec4 normal;
	vec4 lightVec;
	vec4 eyeVec;
	vec2 texCoord;
} data;

layout(location = 0) out vec4 color;

// shader function
void main()
{
	vec4 N = normalize(data.normal);
	vec4 L = normalize(data.lightVec);
	float kd = dot(N, L);

	float ks = dot(normalize(data.eyeVec), (kd + kd)*N - L);


	kd = max(0.0, kd);
	ks = max(0.0, ks);
	ks = pow(ks, 16);

	const vec4 AMB = vec4(0.0, 0.1, 0.2, 1.0);

	vec4 diffuse = texture(tex_dm, data.texCoord);
	vec4 spec = texture(tex_sm, data.texCoord);
	color = AMB + diffuse*kd + spec * ks;
}