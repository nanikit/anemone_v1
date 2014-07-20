﻿// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define OEMRESOURCE
#include "targetver.h"

// wstring → string 변환 경고 끄기
#pragma warning(disable: 4244)

// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <ios>
#include <tchar.h>
#include <vector>
#include <regex>

#include "Library.h"

#include "TransEngine.h"
#include "TextRenderer.h"
#include "TextProcess.h"
#include "Hotkey.h"
#include "Config.h"
#include "FileWatch.h"
#include "Remocon.h"

#include "Resource.h"

// GDIPlus
#include <GdiPlus.h>
#pragma comment(lib,"GdiPlus.lib")
using namespace Gdiplus;

// STL
#include <string>

extern HINSTANCE hInst;

// hWnd 모음
struct _hWnds
{
	HWND Main;
	HWND Setting;
	HWND Remocon;
	HWND View;
	HWND Clip;
};
extern _hWnds hWnds;
extern HANDLE AneHeap;
extern bool IsActive;

// 클래스 모음
struct _Class
{
	CTextRenderer *TextRenderer;
	CTransEngine *TransEngine;
	CTextProcess *TextProcess;
	CHotkey *Hotkey;
	CConfig *Config;
	CFileWatch *FileWatch;
	CRemocon *Remocon;
};
extern _Class Cl;

struct render_attr
{
	FontFamily *Font;
	int Size_A;
	int Size_B;
	int Size_C;
	int Size_S;
};

struct _key_map
{
	bool Ctrl = false;
	bool Alt = false;
	bool Shift = false;
	DWORD Code;
	DWORD func;
};

extern std::vector<_key_map> key_map;

static render_attr *rdName;
static render_attr *rdOriginal;
static render_attr *rdTrans;

INT IsWritableMemory(LPVOID pMemoryAddr);
INT IsReadableMemory(LPVOID pMemoryAddr);