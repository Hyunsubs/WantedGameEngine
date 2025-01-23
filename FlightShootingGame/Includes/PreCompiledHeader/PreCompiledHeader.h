#pragma once

// 자주 쓰는 헤더
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "Container/List.h"
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"

// FMOD 라이브러리 추가
#include <FMOD/fmod.h>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_codec.h>

#pragma comment(lib, "fmod64_vc.lib")

// opencv 라이브러리 추가
#ifndef _DEBUG
#include <opencv2/opencv.hpp>
#endif