// By Dan Buckstein
// Modified by: _______________________________________________________________
#include "egpfw/egpfw/egpfwOBJLoader.h"


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BUFFER_OFFSET_BYTE(p,n) ((char *)(p) + n)


// helper structures
union float2
{
	struct { float f0, f1; };
	float f[2];
};
union float3
{
	struct { float f0, f1, f2; };
	float f[3];
};
union float4
{
	struct { float f0, f1, f2, f3; };
	float f[4];
};
union int4
{
	struct { int i0, i1, i2, i3; };
	int i[4];
};
union face
{
	struct { unsigned int v0, v1, v2, vt0, vt1, vt2, vn0, vn1, vn2; };
	struct { unsigned int v[3], vt[3], vn[3]; };
};

struct uniqueTriFace;
struct uniqueVertex;
struct uniqueTexcoord;
struct uniqueNormal;

#ifndef __cplusplus
typedef union float2			float2;
typedef union float3			float3;
typedef union float4			float4;
typedef union int4				int4;
typedef union face				face;
typedef struct uniqueTriFace	uniqueTriFace;
typedef struct uniqueVertex		uniqueVertex;
typedef struct uniqueTexcoord	uniqueTexcoord;
typedef struct uniqueNormal		uniqueNormal;
#endif	// __cplusplus


//-----------------------------------------------------------------------------


// ****
// load triangulated OBJ file
egpTriOBJDescriptor egpfwLoadTriangleOBJ(const char *objPath, const egpMeshNormalMode normalMode, const double globalScale)
{
	egpTriOBJDescriptor obj = { 0 };

	FILE *file = fopen(objPath, "r");

	if (file == NULL)
		printf("\nCould not open file %s!\n", objPath);


	fseek(file, 0L, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	float* theData = (float*)malloc(fileSize);

	obj.attribOffset[ATTRIB_POSITION] = 0;

	int count = 0;
	int currAttrIndex = 0;
	char* str = (char*)malloc(sizeof(char) * 100);
	fgets(str, 100, file);
	if (str == NULL)
		printf("Cound not read from OBJ file!\n");

	while (!(str[0] == 'v' && str[1] == ' '))
	{
		fgets(str, 100, file);
		if (str == NULL)
			printf("Could not read from OBJ file");

		printf("\n%s", str);
	}

	if (str == NULL)
		printf("No OBJ verteces could be found in %s!\n", objPath);


	char* num = (char*)malloc(sizeof(char) * 10);

	int currStrIndex;
	int currNumIndex = 0;

	while (str[0] == 'v' && str[1] == ' ')
	{
		currStrIndex = 2;

		for (int i = 0; i < 3; i++)
		{
			while (str[currStrIndex] != ' ')
				num[currNumIndex++] = str[currStrIndex++];

			float temp = strtof(num, NULL);
			theData[currAttrIndex] = temp;

			for (int j = 0; j < 10; j++)
				num[j] = 0;

			currNumIndex = 0;
			currStrIndex++;
			count++;
			currAttrIndex++;
		}


		fgets(str, 100, file);
		if (str == NULL)
			printf("Could not read from OBJ file");
	}

	count = 0;
	obj.attribOffset[ATTRIB_TEXCOORD] = currAttrIndex;

	while (str[0] == 'v' && str[1] == 't' && str[2] == ' ')
	{
		currStrIndex = 3;
		for (int i = 0; i < 2; i++)
		{
			while (str[currStrIndex] != ' ')
				num[currNumIndex++] = str[currStrIndex++];

			float temp = strtof(num, NULL);
			printf("%f\n", temp);
			theData[currAttrIndex] = temp;

			for (int j = 0; j < 10; j++)
				num[j] = 0;

			currNumIndex = 0;
			currStrIndex++;
			count++;
			currAttrIndex++;
		}

		fgets(str, 100, file);
		if (str == NULL)
			printf("Could not read from OBJ file");

		printf("\n%s", str);
	}

	count = 0;
	obj.attribOffset[ATTRIB_NORMAL] = currAttrIndex;

	while (str[0] == 'v' && str[1] == 'n' && str[2] == ' ')
	{
		currStrIndex = 3;

		for (int i = 0; i < 3; i++)
		{
			while (str[currStrIndex] != ' ')
				num[currNumIndex++] = str[currStrIndex++];

			float temp = strtof(num, NULL);
			theData[currAttrIndex] = temp;

			for (int j = 0; j < 10; j++)
				num[j] = 0;

			currNumIndex = 0;
			currStrIndex++;
			count++;
			currAttrIndex++;
		}


		fgets(str, 100, file);
		if (str == NULL)
			printf("Could not read from OBJ file");
	}

	while (!(str[0] == 'f' && str[1] == ' '))
	{
		fgets(str, 100, file);
		if (str == NULL)
			printf("Could not read from OBJ file");

		printf("\n%s", str);
	}



	for (int j = 0; j < count + obj.attribOffset[ATTRIB_NORMAL]; j++)
	{
		printf("%f\n", theData[j]);
	}



	fclose(file);
	free(str);
	free(num);

	obj.data = theData;
	return obj;
}


// ****
// convert OBJ to VAO & VBO
int egpfwCreateVAOFromOBJ(const egpTriOBJDescriptor *obj, egpVertexArrayObjectDescriptor *vao_out, egpVertexBufferObjectDescriptor *vbo_out)
{
	egpAttributeDescriptor attribs[] = {
		(ATTRIB_POSITION, ATTRIB_VEC3, egpfwGetOBJAttributeData(obj, ATTRIB_POSITION)),
		(ATTRIB_COLOR, ATTRIB_VEC3, egpfwGetOBJAttributeData(obj, ATTRIB_COLOR)),
		(ATTRIB_NORMAL, ATTRIB_VEC3, egpfwGetOBJAttributeData(obj, ATTRIB_NORMAL)),
		(ATTRIB_TEXCOORD, ATTRIB_VEC2, egpfwGetOBJAttributeData(obj, ATTRIB_TEXCOORD)),
	};

	//junk ? creating a vao requires
	egpIndexBufferObjectDescriptor* ibo;

	 *vao_out = egpfwCreateVAOInterleaved(PRIM_TRIANGLES, attribs, 4, egpfwGetOBJNumVertices(obj), vbo_out , ibo);

	egpfwReleaseOBJ(obj);
	return 0;
}


// ****
// free obj data
int egpfwReleaseOBJ(egpTriOBJDescriptor *obj)
{
	//... Here

	free(obj);

	return 0;
}


// ****
// save/load binary
int egpfwSaveBinaryOBJ(const egpTriOBJDescriptor *obj, const char *binPath)
{
	
	return 0;
}

egpTriOBJDescriptor egpfwLoadBinaryOBJ(const char *binPath)
{
	egpTriOBJDescriptor obj = { 0 };
	return obj;
}


// these functions are complete!
// get attribute data from OBJ
const void *egpfwGetOBJAttributeData(const egpTriOBJDescriptor *obj, const egpAttributeName attrib)
{
	if (obj && obj->data && obj->attribOffset[attrib])
		return BUFFER_OFFSET_BYTE(obj->data, obj->attribOffset[attrib]);
	return 0;
}

unsigned int egpfwGetOBJNumVertices(const egpTriOBJDescriptor *obj)
{
	if (obj && obj->data)
		return *((unsigned int *)obj->data);
	return 0;
}
