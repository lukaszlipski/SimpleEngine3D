#include "mesh.h"
#include "../utilities/model_loader.h"
#include "../utilities/memory.h"

namespace SE3D
{
	Mesh::Mesh(const INTERNAL_MESH_FORMAT& mesh)
		: m_Name(mesh.m_Name), m_Size(mesh.m_Indices.Size())
	{
		DynamicArray<VERTEX> m_VertexArray;

		for (uint32 i = 0; i < mesh.m_Vertices.Size(); i++)
		{
			VERTEX vert;
			vert.m_Position = mesh.m_Vertices[i];
			vert.m_Normal = mesh.m_Normals[i];
			vert.m_UV = mesh.m_TextCoords[i];
			m_VertexArray.Push(vert);
		}

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_VertexArray.Size() * sizeof(VERTEX), &m_VertexArray[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), reinterpret_cast<void*>(OffsetOf(VERTEX, m_Normal)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX), reinterpret_cast<void*>(OffsetOf(VERTEX, m_UV)));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.m_Indices.Size() * sizeof(uint32), &mesh.m_Indices[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

	Mesh::Mesh()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);
		
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_IBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Mesh::Draw() const
	{
		m_Material.Bind();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_Size, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		m_Material.Unbind();
	}
}
