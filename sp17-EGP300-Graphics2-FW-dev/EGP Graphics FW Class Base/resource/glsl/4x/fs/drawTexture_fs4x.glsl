/*
	Draw Texture
	By Dan Buckstein
	Fragment shader that displays a sample from a texture.
	
	Modified by: ______________________________________________________________
*/

// version
#version 410


// ****
// varyings
in vertex
{
	vec2 textCoord;
} data;

// ****
// uniforms: 
// in GLSL 4.3+ you can hard-set texture slots: 
//		layout (binding = <texture index>) uniform <sampler type> <name>;
// ...otherwise they are declared just like other uniforms: 
//		uniform <sampler type> <name>;
uniform sampler2D tex_dm;

// ****
// target
layout(location = 0) out vec4 color;

// shader function
void main()
{
	color = texture(tex_dm, data.textCoord);
}