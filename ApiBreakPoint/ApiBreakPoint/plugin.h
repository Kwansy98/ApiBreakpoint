#pragma once

#include "pluginmain.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <commctrl.h>

#pragma comment(lib,"Comctl32.lib")

using namespace Script::Module;
using namespace Script::Symbol;
using namespace Script::Debug;
using namespace Script::Register;

#define MENU_MAINWINDOW_POPUP 1

//functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
void pluginStop();
void pluginSetup();


#define MAINWINDOW_WIDTH 840
#define MAINWINDOW_HEIGHT 600

const UINT IDC_TABCTRL = __COUNTER__ + 1500;



#define TAB_COUNT 15
#define CHECK_COUNT (25*3)

struct ApiBreakPointInfo
{
	std::string dllName;
	std::string apiName;
	std::string description;
	bool bWantToSetBp; // means weather user want bp set or not. true doesn't means bp really set, perhaps int3 erased or dll not loaded yet

	ApiBreakPointInfo(std::string _dllName, std::string _apiName, std::string _description)
		: dllName(_dllName), apiName(_apiName), description(_description), bWantToSetBp(false) {}
};

struct ApiGroup
{
	std::string groupName;
	std::vector<ApiBreakPointInfo> apiList;
};

// check box control ID
const UINT IDC_CHECKS[CHECK_COUNT] =
{
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
};




