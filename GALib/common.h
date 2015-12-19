#pragma once


#include <Windows.h>
#include <list>
#include <vector>
#include <deque>
#include <unordered_map>
#include <array>
#include <assert.h>
#include <functional>
#include <memory>
#include <limits>
#include <tuple>
#include <string>
#include <type_traits>
#include <d3d11.h>
#include <wrl.h>
#include <mmsystem.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib,"winmm.lib")
#ifdef GA_LIB_SCREE_SHOT
#pragma comment(lib,"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86\d3dx11.lib")
#endif
template<class T>
using ComPtr = Microsoft::WRL::ComPtr < T >;

#include "Utility\DebugPrint.h"

#define SAFE_RELEASE(x) if(x) x->Release(); x = nullptr;
#ifdef _DEBUG
#define OSReport(...) DebugPrint(__VA_ARGS__)
#else
#define OSReport(...) 0
#endif