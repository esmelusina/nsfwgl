#pragma once


#include "Window.h"
#include "Assets.h"
#include "render.h"
#include "Application.h"


#include <iostream>
#include <cstring>

// http://stackoverflow.com/questions/8487986/file-macro-shows-full-path
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#ifdef _DEBUG
#define TODO()	  do{std::cerr << __FILENAME__ << "(" << __LINE__ << ") '" << __FUNCTION__ << "' IS NOT IMPLEMENTED!" << std::endl;}while(0)
#define TODO_D(A) do{std::cerr << __FILENAME__ << "(" << __LINE__ << ") '" << __FUNCTION__ << "' IS NOT IMPLEMENTED!" << std::endl << "  -> " << A << std::endl << std::endl;}while(0)

#ifdef NO_TODO_DETAIL
#define TODO_D(A) TODO()
#endif

#elif
#define TODO()	  do{}while(0)
#define TODO_D(A) do{}while(0)
#endif