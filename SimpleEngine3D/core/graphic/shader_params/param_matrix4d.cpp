#include "param_matrix4d.h"
#include <GL/glew.h>

namespace SE3D
{
	ParamMatrix4D::ParamMatrix4D(Matrix4D value)
		: m_Value(value)
	{
		m_Type = MATRIX4D;
	}

	void ParamMatrix4D::Bind()
	{
		glUniformMatrix4fv(m_Location, 1, GL_TRUE, (GLfloat*)m_Value.GetPtr());
	}

	void ParamMatrix4D::SetValue(Matrix4D value)
	{
		m_Value = value;
	}
}
