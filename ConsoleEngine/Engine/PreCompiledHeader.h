#pragma once

// 자주 쓰는 헤더
#include <Windows.h>
#include <iostream>


// Debug
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define new new
#endif

template<typename T>
void SafeDelete(T* pointer)
{
	if (pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}