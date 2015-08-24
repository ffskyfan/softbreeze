

#ifndef MESH_H
#define MESH_H



class starVector3;
class starVector2;

struct starVertex
{
	starVertex()
	{
		for(int i=0;i<3;i++){
			color[i] = 63;
		}
		color[3] = 0; 
	}

	bool operator<(const starVertex& a) const 
	{
		if(xyz .x != a.xyz.x) {
			return xyz .x < a.xyz.x;
		} else if (xyz .y != a.xyz.y) {
			return xyz .y > a.xyz.y;
		} else if (xyz .z != a.xyz.z) {
			return xyz.z > a.xyz.z;
		} else if (normal.x != a.normal.x) {
			return normal.x > a.normal.x;
		} else if (normal.y != a.normal.y) {
			return normal.y > a.normal.y;
		}else if (normal.z != a.normal.z) {
			return normal.z > a.normal.z;
		} else if (textureCoord.x != a.textureCoord.x) {
			return textureCoord.x > a.textureCoord.x;
		} else if (textureCoord.y != a.textureCoord.y) {
			return textureCoord.y > a.textureCoord.y;
		} else if (color[0] != a.color[0]) {
			return color[0] > a.color[0];
		} else if (color[1] != a.color[1]) {
			return color[1] > a.color[1];
		} else if (color[2] != a.color[2]) {
			return color[2] > a.color[2];
		} else {
			return color[3] > a.color[3];
		}
	}

	starVector3 	xyz;
	starVector3		normal;
	starVector2		textureCoord;
	unsigned char 	color[4];
};

struct starMesh
{
	starMesh()
	{
		vertexNum = 0;
		indexNum  = 0;

		vertices  = 0;
		indices	  = 0;				
	}

	~starMesh()
	{
		if(vertices != 0) {
			delete vertices;
		}

		if(indices != 0) {
			delete indices;
		}
	}

	int vertexNum;
	int indexNum;

	starVertex*		vertices;
	unsigned int*	indices;				
};






#endif

