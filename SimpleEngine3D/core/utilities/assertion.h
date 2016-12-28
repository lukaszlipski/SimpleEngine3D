#pragma once

#if _DEBUG
#define Assert(x) if(x) { } else { char* a = 0;	*a =0; }
#else
	#define Assert(x)
#endif
