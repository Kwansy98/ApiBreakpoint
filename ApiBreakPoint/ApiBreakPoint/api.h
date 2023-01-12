//#pragma once
//#include <vector>
//#include <string>
//
//struct ApiBreakPointInfo
//{
//	std::string dllName;
//	std::string apiName;
//	std::string description;
//	bool bpSet;
//
//	ApiBreakPointInfo(std::string _dllName, std::string _apiName, std::string _description)
//		: dllName(_dllName), apiName(_apiName), description(_description), bpSet(false) {}
//};
//
//struct ApiGroup
//{
//	std::string groupName;
//	std::vector<ApiBreakPointInfo> apiList;
//};
//
///*
// * You can change display text language here if you want.
// * Dll name are not necessary so far cause we are using "bp" rather than SetBPX()
// * If the function name appears in multiple dlls, the behavior depends on the bp instruction
// */
//ApiGroup Groups[TAB_COUNT] =
//{
//	{
//		"常用断点",
//		{
//			ApiBreakPointInfo("expsrv.dll","rtcFileLen","VB自校验"),
//			ApiBreakPointInfo("Kernel32.dll","FindFirstFileA","查找文件"),
//			ApiBreakPointInfo("Kernel32.dll","ExitProcess","程序退出"),
//			ApiBreakPointInfo("Kernel32.dll","GetStartupInfoA","获取启动信息"),
//			ApiBreakPointInfo("Kernel32.dll","GetFileSize","获取文件大小"),
//			ApiBreakPointInfo("Kernel32.dll","VirtualProtect","Vmp脱壳"),
//			ApiBreakPointInfo("User32.dll","ExitWindowsEx","关机断点"),
//			ApiBreakPointInfo("Kernel32.dll","CreateFileA","自校验"),
//			ApiBreakPointInfo("Kernel32.dll","GetVersion","易语言脱壳"),
//			ApiBreakPointInfo("Ws2_32.dll","send","发送封包"),
//			ApiBreakPointInfo("Ws2_32.dll","WSASend","发送封包"),
//			ApiBreakPointInfo("Ws2_32.dll","recv","接收封包"),
//			ApiBreakPointInfo("ntdll.dll","RtlAdjustPrivilege","易语言快速关机"),
//			ApiBreakPointInfo("Shell32.dll","SHFormatDrive","格盘API"),
//			ApiBreakPointInfo("Kernel32.dll","RemoveDirectoryA","删除目录"),
//			ApiBreakPointInfo("Kernel32.dll","DeleteFileA","删除文件"),
//		}
//	},
//	{
//		"对话框",
//		{
//			ApiBreakPointInfo("","MessageBoxA","弹对话框"),
//			ApiBreakPointInfo("","MessageBoxW",""),
//			ApiBreakPointInfo("","MessageBoxExA",""),
//			ApiBreakPointInfo("","MessageBoxExW",""),
//		}
//	},
//	{
//		"文件处理",
//		{
//			ApiBreakPointInfo("Kernel32.dll","CreateFileA","创建或打开文件"),
//			ApiBreakPointInfo("Kernel32.dll","CreateFileW",""),
//		}
//	},
//	{
//		"Memory",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Reg",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Time",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Process",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Network",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Memory",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Disk",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Malware",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"AntiDebug",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"VB",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"VC/MFC",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"E-Lang",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//};