// This header provides a workarounds for including CImg in our files.

#ifndef LTS_UTIL_CIMG_WORKAROUND_H
#define LTS_UTIL_CIMG_WORKAROUND_H

#include "CImg.h"

// CImg includes the X11 header X.h which has a macro called "Success"
// and this clashes with the Eigen library.
// See: https://stackoverflow.com/questions/22400905/eigen-and-cimg-compatibility-issues
#ifdef Success
	#undef Success
#endif


#endif //LTS_UTIL_STRING_H
