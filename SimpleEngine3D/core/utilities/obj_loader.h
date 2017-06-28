#pragma once
#include "../containers/dynamic_array.h"
#include "../math/math.h"
#include "model_loader.h"

namespace SE3D
{
	struct OBJindex
	{
		uint32 VertexIndex;
		uint32 TextCoordIndex;
		uint32 NormalIndex;
	};


	class OBJLoader : public ModelLoader
	{
	private:
		DynamicArray<Vector3D> m_Vertices;
		DynamicArray<Vector2D> m_TextCoords;
		DynamicArray<Vector3D> m_Normals;
		DynamicArray<OBJindex> m_Indices;
		uint32 m_VerticesOffset;
		uint32 m_TextCoordsOffset;
		uint32 m_NormalsOffset;
		bool m_HasNormals;
		bool m_HasTextureCoordinates;
		Vector3D m_FurthestPoint;
		Vector3D m_Center;

	public:
		OBJLoader(const char* path);
		~OBJLoader();
		inline Vector3D GetFurthestPoint() const { return m_FurthestPoint; }
		inline Vector3D GetMassCenter() const { return m_Center; }

	private:
		void LoadMeshFromFile(const char* path);
		void AddNewMesh(const char* line);
		void AddVertex(const char* line);
		void AddTextCoord(const char* line);
		void AddNormal(const char* line);
		void AddFace(const char* line);
		void CalculateTangents();
		void ConvertToInternalFormat() override;
	};
}
