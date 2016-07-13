
#include <stdio.h>
#include <vector>
#include <map>

#include "../softbreeze.h"
#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../object/mesh.h"
#include "../file/obj_file_loader.h"


softbreeze_namespace_beg

namespace ObjFileLoader
{
	enum ObjInedxType
	{
		ObjInedxType_non,
		ObjInedxType_v,
		ObjInedxType_vn,
		ObjInedxType_vt,
		ObjInedxType_vnt,
	};

	//----------------------------------------------------------


	struct ObjFile_Index
	{
		ObjFile_Index()
		{
			indexType = ObjInedxType_non;
			vertex = 0;
			normal = 0;
			textureCoord = 0;
		}

		ObjInedxType	indexType;

		int					vertex;
		int					normal;
		int					textureCoord;
	};

	struct ObjFile_Content
	{
		std::vector<Vector3>			vertices;
		std::vector<Vector3>			normals;
		std::vector<Vector2>			textureCoords;
		
		std::vector<ObjFile_Index>		indices;
	};


	//-------------------------------------------------------------

	void Parse(const ObjFile_Content& objInfo,Mesh* mesh)
	{
		std::map<Vertex,unsigned int> vertexMap;
		std::vector<Vertex> vertexVector;
		std::vector<unsigned int>	indicesVector;

		int idx=0;
		std::vector<ObjFile_Index>::const_iterator itIndex		= objInfo.indices.begin();
		std::vector<ObjFile_Index>::const_iterator itIndexEnd	= objInfo.indices.end();
		for(;itIndex!=itIndexEnd;itIndex++)	{
			Vertex vertex;
			vertex.xyz			= objInfo.vertices[itIndex->vertex-1];
			vertex.normal		= objInfo.normals[itIndex->normal-1];
			vertex.textureCoord	= objInfo.textureCoords[itIndex->textureCoord-1];

			std::map<Vertex,unsigned int>::iterator itVertexFinded = vertexMap.find(vertex);
			if(itVertexFinded != vertexMap.end()) {
				indicesVector.push_back(itVertexFinded->second);
			} else { 
				vertexMap.insert( std::pair<Vertex,unsigned int>(vertex,idx));
				vertexVector.push_back(vertex);
				indicesVector.push_back(idx);
				idx++;
			}
		}

		mesh->vertices = vertexVector;
		mesh->indices = indicesVector;
	}


	void ReadIndexData(const char* qualifier,const char* data,ObjFile_Content& objInfo)
	{
		const int maxIndicesPerFace = 3;
		ObjFile_Index objIndices[maxIndicesPerFace]; //most

		char* buffer[maxIndicesPerFace];
		for(int i=0; i<maxIndicesPerFace ;i++)
		{
			buffer[i] = new char[1024];
		}

		int bufferIdx = 0;
		int bufferDataPointer = 0;
		for(int i=0;;i++)
		{
			if(data[i]!=' ' && data[i]!='\0') {
				buffer[bufferIdx][bufferDataPointer] = data[i];
				bufferDataPointer++;
			} else {
				buffer[bufferIdx][bufferDataPointer] = '\0';
				bufferIdx++;
				bufferDataPointer = 0;
				if(data[i]=='\0') {
					break;
				}
				if(bufferIdx>=maxIndicesPerFace){
					break;
				}
			}
		}
		

		int i=0;
		if(strstr(buffer[i], "//")) //  格式v//n
		{
			for(; i<maxIndicesPerFace ; i++) {
				if (2 == sscanf_s(buffer[i], "%d//%d", &objIndices[i].vertex, &objIndices[i].normal ) ) {
					objIndices[i].indexType = ObjInedxType_vn;
				}
			}

		} else if (3 == sscanf_s(buffer[i], "%d/%d/%d", &objIndices[i].vertex, &objIndices[i].textureCoord, &objIndices[i].normal))	{ //  格式v/t/n
			i++;
			for(;  i<maxIndicesPerFace ; i++) {
				if (3 == sscanf_s(buffer[i], "%d/%d/%d", &objIndices[i].vertex, &objIndices[i].textureCoord, &objIndices[i].normal) ) {
					objIndices[i].indexType = ObjInedxType_vnt;
				}
			}

		} else if (2 == sscanf_s(buffer[i], "%d/%d", &objIndices[i].vertex, &objIndices[i].textureCoord ) )	{//  格式v/t
			i++;
			for(; i<maxIndicesPerFace ; i++) {
				if (2 == sscanf_s(buffer[i], "%d/%d", &objIndices[i].vertex, &objIndices[i].textureCoord ) ) {
					objIndices[i].indexType = ObjInedxType_vt;
				}
			}

		} else { // 格式 v
			for(; i<maxIndicesPerFace ; i++) {
				if (1 == sscanf_s(buffer[i], "%d", &objIndices[i].vertex) ) {
					objIndices[i].indexType = ObjInedxType_v;
				}
			}

		}

		for(int j=0; j<i; j++) {
			if( j< 3) {
				objInfo.indices.push_back(objIndices[j]);
			}else {
				objInfo.indices.push_back(objIndices[j-2]);
				objInfo.indices.push_back(objIndices[j-1]);
				objInfo.indices.push_back(objIndices[j]);
			}
		}


		for(int i=0; i<maxIndicesPerFace ;i++)
		{
			delete buffer[i];
		}
	}

	void ReadSignalData(const char* qualifier,const char* data,ObjFile_Content& objInfo)
	{
		if(0==strcmp(qualifier , "v") ) {
			Vector3 vertexPos;
			sscanf_s(data, "%f %f %f", &vertexPos.x, &vertexPos.y, &vertexPos.z);
			objInfo.vertices.push_back(vertexPos);

		} else if (0==strcmp(qualifier , "vn")){
			Vector3 vertexNormal;
			sscanf_s(data, "%f %f %f", &vertexNormal.x, &vertexNormal.y, &vertexNormal.z);
			objInfo.normals.push_back(vertexNormal);

		} else if (0==strcmp(qualifier , "vt")){
			Vector2 textureCoord;
			sscanf_s(data, "%f %f ", &textureCoord.x, &textureCoord.y );
			objInfo.textureCoords.push_back(textureCoord);

		} else if (0==strcmp(qualifier , "f")) {
			ReadIndexData(qualifier,data,objInfo);
		} 
	}

	bool Load(const char* filePath,Mesh* mesh)
	{
		FILE* pFile = NULL;
		errno_t error = fopen_s(&pFile, filePath,"r");
		if(!pFile && error!=0) {
			return false;
		}

		char* qualifier = new char[16]; //the largest qualifier is"shadow_obj",16 byte is enough
		char* buffer = new char[1024]; 

		ObjFile_Content tempObjContent;

		char qualifierReadIdx = 0;
		while(!feof(pFile)) 
		{
			char readData=fgetc(pFile); 
			if(readData == ' ')
			{
				qualifier[qualifierReadIdx]  = '\0';
				//if (0==strcmp(qualifier , "#")) {
				//	continue;
				//}

				int  bufferIdx = 0;
				while(readData != '\n')
				{
					readData=fgetc(pFile);
					buffer[bufferIdx] = readData;
					bufferIdx++;
				}
				buffer[bufferIdx] = '\0';

				ReadSignalData(qualifier,buffer,tempObjContent);
				qualifierReadIdx = 0;
			}
			else
			{
				if(readData != '\n') {
					qualifier[qualifierReadIdx] = readData;
					qualifierReadIdx++;
				}
				else
				{
					qualifierReadIdx = 0;
				}
			}

		}

		Parse(tempObjContent, mesh);

		delete qualifier;
		delete buffer;
		return true;
	}


}


softbreeze_namespace_end



