#include "file.h"

namespace SE3D {

	void File::Delete(FILE file)
	{
		if (file.Content != nullptr)
			delete file.Content;
	}

}