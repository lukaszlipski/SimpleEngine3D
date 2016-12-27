#pragma once
#include "../containers/dynamic_array.h"
#include "../math/math.h"

namespace SE3D {

	struct OBJindex {
		uint32 VertexIndex;
		uint32 TextCoordIndex;
		uint32 NormalIndex;
	};

	class OBJLoader {

	private:
		bool m_HasNormals;
		bool m_HasTextureCoordinates;
		DynamicArray<Vector3D> m_Vertices;
		DynamicArray<Vector2D> m_TextCoords;
		DynamicArray<Vector3D> m_Normals;
		DynamicArray<OBJindex> m_Indices;
	public:

		OBJLoader(const char* path);

	};

}