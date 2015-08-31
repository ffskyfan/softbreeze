

#ifndef SOFTBREEZE_VERTEX_H
#define SOFTBREEZE_VERTEX_H

softbreeze_namespace_beg


class Vector3;
class Vector2;

struct Vertex
{
	Vertex()
	{
		for(int i=0;i<3;i++){
			color[i] = 63;
		}
		color[3] = 0; 
	}

	bool operator<(const Vertex& a) const 
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

	Vector3 	xyz;
	Vector3		normal;
	Vector2		textureCoord;
	unsigned char 	color[4];
};



softbreeze_namespace_end



#endif

