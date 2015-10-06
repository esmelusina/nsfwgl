#pragma once


#include "Window.h"
#include "Assets.h"
#include "Render.h"
#include "Object.h"



#include <iostream>

#ifdef _DEBUG
#define TODO()	  do{std::cerr << __FILE__ << ": " << __LINE__ << ": " << __FUNCSIG__ << " IS NOT IMPLEMENTED!" << std::endl; }while(0)
#define TODO_D(A) do{std::cerr << __FILE__ << ": " << __LINE__ << ": " << __FUNCSIG__ << " IS NOT IMPLEMENTED!" << std::endl << A << std::endl << std::endl;}while(0)

#ifdef NO_TODO_DETAIL
#define TODO_D(A) TODO()
#endif

#elif
#define TODO() do{}while(0)
#define TODO_D(A) do{}while(0)
#endif