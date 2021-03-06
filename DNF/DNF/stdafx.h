// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "imm32.lib")
#pragma comment (lib, "Version.lib")
#pragma comment (lib, "legacy_stdio_definitions.lib")

#include <Ws2tcpip.h>
#include <winsock2.h>
#include <mswsock.h>
#include <Mmsystem.h>
#include <Ws2spi.h>
#include <Mstcpip.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <algorithm>
#include <memory>
#include <process.h>
#define DIRECTINPUT_VERSION		0x0800
#include <dinput.h>
#include <intrin.h>

// Direct3D9 includes
#include <d3d9.h>
#include <d3dx9.h>

// Direct3D10 includes
#include <d3dcommon.h>
#include <dxgi.h>
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include <d3dx10.h>

#pragma warning(disable: 4996)

#include "./UI/DXUT.h"
#include "./UI/DXUTmisc.h"
#include "./UI/DXUTenum.h"
#include "./UI/DXUTcamera.h"
#include "./UI/DXUTgui.h"
#include "./UI/DXUTguiIME.h"
#include "./UI/DXUTres.h"
#include "./UI/DXUTsettingsdlg.h"
#include "./UI/ImeUi.h"

#ifdef _DEBUG
#include "vld.h"
#endif

#include "Defines.h"

using namespace std;

#include "Export_Function.h"