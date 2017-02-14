/*
	Draw Color
	By Dan Buckstein
	Fragment shader that displays color received from previous piipeline stage.
	
	Modified by: ______________________________________________________________
*/

// version (same idea)
#version 410


// ****
// varyings: data received from previous stage in the pipeline
// same formats as vertex shader, with restrictions: 
//	-> for structure format, full structure layout must be identical
//		-> replace 'out' with 'in':		in <structure name> { ...
//	-> for one-by-one format, variable type and name must be identical


// uniforms: same idea for all shader types
// (none in this example)


// ****
// target: fragment shader result to be stored in framebuffer
// same format as attribute, but with 'out' instead of 'in': 
//		layout (location = <target index>) out <type> <name>;
in vertex
{
	vec4 color;
} data;


layout(location = 0) out vec4 color;

// shader entry point: function executes once per-fragment
void main()
{
	color = data.color;
}