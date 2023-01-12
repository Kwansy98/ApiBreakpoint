#include "plugin.h"

#ifdef _UNICODE
#error "USE ASCII CODE PAGE"
#endif

using namespace Script::Module;
using namespace Script::Symbol;
using namespace Script::Debug;
using namespace Script::Register;

// make sure only one window exists
bool bIsMainWindowShow = false;


/*
 * Add API Breakpoint here.
 * You can change display text language here if you want.
 * Dll name are not necessary so far cause we are using "bp" rather than SetBPX()
 * If the function name appears in multiple dlls, the behavior depends on the bp instruction
 */
ApiGroup Groups[TAB_COUNT] =
{
	{
		"常用断点",
		{
			ApiBreakPointInfo("Kernel32.dll","FindFirstFileA","查找文件"),
			ApiBreakPointInfo("Kernel32.dll","ExitProcess","程序退出"),
			ApiBreakPointInfo("Kernel32.dll","GetStartupInfoA","获取启动信息"),
			ApiBreakPointInfo("Kernel32.dll","GetFileSize","获取文件大小"),
			ApiBreakPointInfo("Kernel32.dll","VirtualProtect","Vmp脱壳"),
			ApiBreakPointInfo("User32.dll","ExitWindowsEx","关机断点"),
			ApiBreakPointInfo("Kernel32.dll","CreateFileA","自校验"),
			ApiBreakPointInfo("Kernel32.dll","GetVersion","易语言脱壳"),
			ApiBreakPointInfo("Ws2_32.dll","send","发送封包"),
			ApiBreakPointInfo("Ws2_32.dll","WSASend","发送封包"),
			ApiBreakPointInfo("Ws2_32.dll","recv","接收封包"),
			ApiBreakPointInfo("ntdll.dll","RtlAdjustPrivilege","易语言快速关机"),
			ApiBreakPointInfo("Shell32.dll","SHFormatDrive","格盘API"),
			ApiBreakPointInfo("Kernel32.dll","RemoveDirectoryA","删除目录"),
			ApiBreakPointInfo("Kernel32.dll","DeleteFileA","删除文件"),
			ApiBreakPointInfo("","GetLastError","返回错误码"),
		}
	},
	{
		"对话框",
		{
			ApiBreakPointInfo("","MessageBoxA","弹对话框"),
			ApiBreakPointInfo("","MessageBoxW",""),
			ApiBreakPointInfo("","MessageBoxExA",""),
			ApiBreakPointInfo("","MessageBoxExW",""),
			ApiBreakPointInfo("","MessageBoxIndirectA",""),
			ApiBreakPointInfo("","MessageBoxIndirectW",""),
			ApiBreakPointInfo("","GetWindowTextA","取控件文本"),
			ApiBreakPointInfo("","GetWindowTextW",""),
			ApiBreakPointInfo("","SetWindowTextA","设置控件文本"),
			ApiBreakPointInfo("","SetWindowTextW",""),
			ApiBreakPointInfo("","GetDlgItemTextA","取控件文本"),
			ApiBreakPointInfo("","GetDlgItemTextW",""),
			ApiBreakPointInfo("","SetDlgItemTextA","设置控件文本"),
			ApiBreakPointInfo("","SetDlgItemTextW",""),
			ApiBreakPointInfo("","GetDlgItemInt","取控件中整数"),
			ApiBreakPointInfo("","SetDlgItemInt","设置控件中整数"),
			ApiBreakPointInfo("","SendMessageA","发消息"),
			ApiBreakPointInfo("","SendMessageW","发消息"),
			ApiBreakPointInfo("","SendDlgItemMessage","发消息"),
			ApiBreakPointInfo("","IsDialogMessageA",""),
			ApiBreakPointInfo("","IsDialogMessageW",""),
			ApiBreakPointInfo("","DispatchMessageA","消息派发"),
			ApiBreakPointInfo("","DispatchMessageW",""),
			ApiBreakPointInfo("","CallWindowProcA","调用窗口过程"),
			ApiBreakPointInfo("","CallWindowProcW",""),
			ApiBreakPointInfo("","DefWindowProcA","默认消息处理"),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","MessageBeep","系统警告声"),
			ApiBreakPointInfo("","DrawTextA","文本描绘到矩形中"),
			ApiBreakPointInfo("","DrawTextW",""),
			ApiBreakPointInfo("","DrawTextExA",""),
			ApiBreakPointInfo("","DrawTextExW",""),
			ApiBreakPointInfo("","FindWindowA","获取窗口句柄"),
			ApiBreakPointInfo("","FindWindowW",""),
			ApiBreakPointInfo("","GetClipboardData","获取剪贴板数据"),
			ApiBreakPointInfo("","CoInitialize","初始化COM库"),
			ApiBreakPointInfo("","CoCreateInstance","创建COM对象"),
			ApiBreakPointInfo("","LoadIconA","载入图标资源"),
			ApiBreakPointInfo("","LoadIconW",""),
			ApiBreakPointInfo("","SetWindowLongA","设置窗口属性"),
			ApiBreakPointInfo("","SetWindowLongW",""),
			ApiBreakPointInfo("","SetWindowLongPtrA",""),
			ApiBreakPointInfo("","SetWindowLongPtrW",""),
			ApiBreakPointInfo("","ShowWindow","显示窗口"),
			ApiBreakPointInfo("","UpdateWindow","更新窗口"),
			ApiBreakPointInfo("","CreateWindowExA","创建窗口"),
			ApiBreakPointInfo("","CreateWindowExW",""),
			ApiBreakPointInfo("","CreateWindowA",""),
			ApiBreakPointInfo("","CreateWindowW",""),
			ApiBreakPointInfo("","DestroyWindow","销毁窗口"),
			ApiBreakPointInfo("","DialogBoxA","模态对话框"),
			ApiBreakPointInfo("","DialogBoxW",""),
			ApiBreakPointInfo("","DialogBoxParamA",""),
			ApiBreakPointInfo("","DialogBoxParamW",""),
			ApiBreakPointInfo("","DialogBoxIndirectA",""),
			ApiBreakPointInfo("","DialogBoxIndirectW",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamA",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamW",""),
			ApiBreakPointInfo("","EndDialog","清除模态对话框"),
			ApiBreakPointInfo("","TranslateMessage","消息队列"),
			ApiBreakPointInfo("","GetMessageA","取消息队列"),
			ApiBreakPointInfo("","GetMessageW",""),
			ApiBreakPointInfo("","PeekMessageA","查消息队列"),
			ApiBreakPointInfo("","PeekMessageW",""),
			ApiBreakPointInfo("","SetMenu","建菜单"),
			ApiBreakPointInfo("","DestroyMenu","删除菜单"),
			ApiBreakPointInfo("","DeleteMenu","删除菜单项"),
			ApiBreakPointInfo("","EnableMenuItem","菜单有无变灰"),
			ApiBreakPointInfo("","EnableWindow","禁止键盘鼠标输入"),
		}
	},
	{
		"文件处理",
		{
			ApiBreakPointInfo("","CreateFileA","创建或打开文件"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","OpenFile","打开文件"),
			ApiBreakPointInfo("","ReadFile","读文件"),
			ApiBreakPointInfo("","WriteFile","写文件"),
			ApiBreakPointInfo("","GetFileSize","取文件大小"),
			ApiBreakPointInfo("","FindFirstFileA","查找文件"),
			ApiBreakPointInfo("","FindFirstFileW",""),
			ApiBreakPointInfo("","GetModuleFileNameA","查模块路径"),
			ApiBreakPointInfo("","GetModuleFileNameW",""),
			ApiBreakPointInfo("","OpenFileMappingA","打开文件映射对象"),
			ApiBreakPointInfo("","OpenFileMappingW",""),
			ApiBreakPointInfo("","LoadLibraryA","加载DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","GetModuleHandleA","查找模块"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetModuleHandleExA",""),
			ApiBreakPointInfo("","GetModuleHandleExW",""),			
			ApiBreakPointInfo("","CreateFileMappingA","创建文件对象"),
			ApiBreakPointInfo("","CreateFileMappingW",""),
			ApiBreakPointInfo("","CopyFileA","复制文件"),
			ApiBreakPointInfo("","CopyFileW",""),
			ApiBreakPointInfo("","CopyFileExA",""),
			ApiBreakPointInfo("","CopyFileExW",""),
			ApiBreakPointInfo("","SetFilePointer","设置文件读写位置"),
			ApiBreakPointInfo("","MoveFileA","移动文件"),
			ApiBreakPointInfo("","MoveFileW",""),
			ApiBreakPointInfo("","MoveFileExA",""),
			ApiBreakPointInfo("","MoveFileExW",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW","删除文件"),
			ApiBreakPointInfo("","LoadCursorFromFileA","创建文件光标"),
			ApiBreakPointInfo("","LoadCursorFromFileW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA","INI重启验证常用"),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","GetPrivateProfileIntA",""),
			ApiBreakPointInfo("","GetPrivateProfileIntW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA","取字符串"),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","WritePrivateProfileStringA","设置字符串"),
			ApiBreakPointInfo("","WritePrivateProfileStringW",""),
		}
	},
	{
		"注册表",
		{
			ApiBreakPointInfo("","RegOpenKeyA","打开注册表项"),
			ApiBreakPointInfo("","RegOpenKeyW",""),
			ApiBreakPointInfo("","RegOpenKeyExA","重启验证常用"),
			ApiBreakPointInfo("","RegOpenKeyExW",""),
			ApiBreakPointInfo("","RegCreateKeyExA",""),
			ApiBreakPointInfo("","RegCreateKeyExW",""),
			ApiBreakPointInfo("","RegQueryValueA","取注册表键值"),
			ApiBreakPointInfo("","RegQueryValueW",""),
			ApiBreakPointInfo("","RegQueryValueExA",""),
			ApiBreakPointInfo("","RegQueryValueExW",""),
			ApiBreakPointInfo("","RegCreateKeyA","创建新项"),
			ApiBreakPointInfo("","RegCreateKeyW",""),
			ApiBreakPointInfo("","RegCloseKey","关闭注册表"),
			ApiBreakPointInfo("","RegDeleteKeyA","删除键值"),
			ApiBreakPointInfo("","RegDeleteKeyW",""),
			ApiBreakPointInfo("","RegEnumKeyExA","枚举子项"),
			ApiBreakPointInfo("","RegEnumKeyExW",""),
			ApiBreakPointInfo("","RegSetValueA","设置默认值"),
			ApiBreakPointInfo("","RegSetValueW",""),
			ApiBreakPointInfo("","RegSetValueExA","设置指定项的值"),
			ApiBreakPointInfo("","RegSetValueExW",""),
		}
	},
	{
		"时间处理",
		{
			ApiBreakPointInfo("","SetSystemTime","设置系统时间"),
			ApiBreakPointInfo("","TimerProc","回调函数"),//what is this
			ApiBreakPointInfo("","SetLocalTime","设置本地时间"),
			ApiBreakPointInfo("","GetLocalTime","获取本地时间"),
			ApiBreakPointInfo("","GetSystemTime","获取系统时间"),
			ApiBreakPointInfo("","GetCurrentTime","获取系统时间"),
			ApiBreakPointInfo("","GetFileTime","获取文件时间"),
			ApiBreakPointInfo("","GetTickCount","系统启动后所经过的毫秒数"),
			ApiBreakPointInfo("","CompareFileTime","比较文件时间"),
			ApiBreakPointInfo("","SetTimer","创建定时器"),
			ApiBreakPointInfo("","KillTimer","移除定时器"),
			ApiBreakPointInfo("","timeSetEvent","多媒体定时器"),
		}
	},
	{
		"进程函数",
		{
			ApiBreakPointInfo("","CreateThread","创建线程"),
			ApiBreakPointInfo("","CreateRemoteThread","创建远程线程"),
			ApiBreakPointInfo("","GetModuleHandleA","查模块基址"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","OpenMutexA","打开互斥体"),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","WriteProcessMemory","写内存"),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory","读内存"),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
			ApiBreakPointInfo("","CreateProcessA","创建进程"),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","OpenProcess","打开进程"),
			ApiBreakPointInfo("","ExitProcess","结束进程"),
			ApiBreakPointInfo("","ExitThread","结束当前线程"),
			ApiBreakPointInfo("","TerminateProcess","终止进程"),
			ApiBreakPointInfo("","TerminateThread","终止线程"),
			ApiBreakPointInfo("","CreateToolhelp32Snapshot","进程快照"),
			ApiBreakPointInfo("","Process32First","取进程句柄"),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","Module32Next","取模块句柄"),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Heap32ListFirst","取堆句柄"),
			ApiBreakPointInfo("","Heap32ListNext","取堆句柄"),
			ApiBreakPointInfo("","GetProcessHeap","取堆句柄"),
			ApiBreakPointInfo("","Heap32First","取进程堆相关信息"),
			ApiBreakPointInfo("","Heap32Next","取进程堆相关信息"),
			ApiBreakPointInfo("","PostQuitMessage","终止线程"),
			ApiBreakPointInfo("","IsDebuggerPresent","检测调试器"),
			ApiBreakPointInfo("","OpenProcessToken","获取进程访问令牌句柄"),
			ApiBreakPointInfo("","OpenThreadToken",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
		}
	},
	{
		"网络",
		{
			ApiBreakPointInfo("","send",""),
			ApiBreakPointInfo("","sendto",""),
			ApiBreakPointInfo("","WSASend",""),
			ApiBreakPointInfo("","WSASendTo",""),
			ApiBreakPointInfo("","recv",""),
			ApiBreakPointInfo("","inet_addr",""),
			ApiBreakPointInfo("","connect",""),
			ApiBreakPointInfo("","UrlDownloadToFileA",""),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
		}
	},
	{
		"内存",
		{
			ApiBreakPointInfo("","FindWindow","取窗口句柄"),
			ApiBreakPointInfo("","GetWindowThreadProcessId","获取窗口进程ID"),
			ApiBreakPointInfo("","OpenProcess","打开进程"),
			ApiBreakPointInfo("","VirtualAllocEx","申请内存"),
			ApiBreakPointInfo("","WriteProcessMemory","写内存"),
			ApiBreakPointInfo("","ReadProcessMemory","读内存"),
			ApiBreakPointInfo("","CreateRemoteThread","创建远程线程"),
			ApiBreakPointInfo("","CreateMutexA","创建互斥体"),
			ApiBreakPointInfo("","CreateMutexW",""),
			ApiBreakPointInfo("","GetModuleHandleA","查模块基址"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetProcAddress","查函数地址"),
			ApiBreakPointInfo("","VirtualAlloc","申请内存"),
			ApiBreakPointInfo("","HeapAlloc",""),
			ApiBreakPointInfo("","VirtualFree","释放内存"),
			ApiBreakPointInfo("","HeapFree",""),
			ApiBreakPointInfo("","LoadLibraryA","载入DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","GetVersion","获取系统版本"),
			ApiBreakPointInfo("","ZwAllocateVirtualMemory",""),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
		}
	},
	{
		"磁盘",
		{
			ApiBreakPointInfo("","GetDiskFreeSpaceA","获取磁盘信息"),
			ApiBreakPointInfo("","GetDiskFreeSpaceExA",""),
			ApiBreakPointInfo("","GetDiskFreeSpaceExW",""),
			ApiBreakPointInfo("","GetDriveTypeA","判断磁盘驱动器类型"),
			ApiBreakPointInfo("","GetDriveTypeW",""),
			ApiBreakPointInfo("","GetLogicalDrives","取驱动器字母"),
			ApiBreakPointInfo("","GetLogicalDriveStringsA","取驱动器路径"),
			ApiBreakPointInfo("","GetLogicalDriveStringsW",""),
		}
	},
	{
		"样本分析",
		{
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","CreateThread",""),
			ApiBreakPointInfo("","CreateProcessA",""),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","WriteProcessMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory",""),
			ApiBreakPointInfo("","OpenMutexA",""),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","CreateToolhelp32SnapShot",""),
			ApiBreakPointInfo("","Heap32ListFirst",""),
			ApiBreakPointInfo("","Heap32ListNext",""),
			ApiBreakPointInfo("","Heap32First",""),
			ApiBreakPointInfo("","Heap32Next",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32Next",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Process32First",""),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","PostQuitMessage",""),
			ApiBreakPointInfo("","Toolhelp32ReadProcessMemory",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
			ApiBreakPointInfo("","SetTimer",""),
			ApiBreakPointInfo("","GetTempPathA",""),
			ApiBreakPointInfo("","GetTempPathW",""),
			ApiBreakPointInfo("","ReadFile",""),
			ApiBreakPointInfo("","WriteFile",""),
			ApiBreakPointInfo("","ShellExecuteA",""),
			ApiBreakPointInfo("","ShellExecuteW",""),
			ApiBreakPointInfo("","WinExec",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW",""),
			ApiBreakPointInfo("","UrlDownloadToFileA",""),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
			ApiBreakPointInfo("","GetDesktopWindow",""),
		}
	},
	{
		"VB",
		{
			ApiBreakPointInfo("","FindResourceA","VB校验"),
			ApiBreakPointInfo("","CreateFileA","VB校验"),
			ApiBreakPointInfo("","GetVolumeInformation","磁盘卷"),
			ApiBreakPointInfo("","MultiByteToWideChar","A转U字符串"),
			ApiBreakPointInfo("","WideCharToMultiByte","U转A字符串"),
			ApiBreakPointInfo("","GetFileSize","获取文件大小"),
			ApiBreakPointInfo("","VarCyFromStr","字符串转整型"),
			ApiBreakPointInfo("","arBstrFromI2","整型转字符串"),
			ApiBreakPointInfo("","rtcFileLen","VB自校验"),
			ApiBreakPointInfo("","rtcFileLenth",""),
			ApiBreakPointInfo("","rtcMsgBox","显示对话框"),
			ApiBreakPointInfo("","rtcInputBox","输入框"),
			ApiBreakPointInfo("","GetMemStr",""),
			ApiBreakPointInfo("","rtcR8ValFromBstr",""),
			ApiBreakPointInfo("","rtcGetPresendDate",""),
			ApiBreakPointInfo("","rtcBeep",""),
			ApiBreakPointInfo("","rtcTrimBstr","字符串去除空格"),
			ApiBreakPointInfo("","rtcMidCharVar","字符串中取字符"),
			ApiBreakPointInfo("","rtcLeftCharVar","字符串左边取字符"),
			ApiBreakPointInfo("","rtcRightCharVar","字符串右边取字符"),
			ApiBreakPointInfo("","StrConv","转换字符串"),
			ApiBreakPointInfo("","rtcT8ValFromBstr","字符串转浮点数"),
			ApiBreakPointInfo("","__vbaI2Str","字符转1字节数值"),
			ApiBreakPointInfo("","__vbaI4Str","字符转4字节数值"),
			ApiBreakPointInfo("","__vbar4Str","字符转4浮点型"),
			ApiBreakPointInfo("","__vbar8Str","字符转8浮点型"),
			ApiBreakPointInfo("","__vbavaradd","变量值相加"),
			ApiBreakPointInfo("","__vbavarsub","变量值相减"),
			ApiBreakPointInfo("","__vbavarmul","变量值相乘"),
			ApiBreakPointInfo("","__vbavaridiv","变量值相除"),
			ApiBreakPointInfo("","__vbavarxor","变量值异或"),
			ApiBreakPointInfo("","__vbavarcat","变量值相连"),
			ApiBreakPointInfo("","__vbaStrCat","字符串相连"),
			ApiBreakPointInfo("","__vbaVarCat","连接字串"),
			ApiBreakPointInfo("","__vbaStrCmp","字符串比较"),
			ApiBreakPointInfo("","__vbaStrComp","字符串比较"),
			ApiBreakPointInfo("","__vbaVarTstEq","比较变量"),
			ApiBreakPointInfo("","__vbaFreeStr",""),
			ApiBreakPointInfo("","__vbaStrCopy",""),
			ApiBreakPointInfo("","__vbaLenBstr",""),
			ApiBreakPointInfo("","__vbavarfornext","循环结构"),
			ApiBreakPointInfo("","__vbafreeobj","释放对象"),
		}
	},
	{
		"VC/MFC",
		{
			ApiBreakPointInfo("","lstrcmpA","字符串比较"),
			ApiBreakPointInfo("","DefWindowProcA","调用默认窗口过程"),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","RegisterClassA","注册窗口类"),
			ApiBreakPointInfo("","RegisterClassW",""),
			ApiBreakPointInfo("","RegisterClassExA",""),
			ApiBreakPointInfo("","RegisterClassExW",""),
			ApiBreakPointInfo("","FindResourceA","查找资源"),
			ApiBreakPointInfo("","FindResourceW",""),
			ApiBreakPointInfo("","LoadResource","加载资源"),
			ApiBreakPointInfo("","SetHandleCount","取变量地址"),
			ApiBreakPointInfo("","IsWindowEnabled","可否输入键鼠"),
		}
	},
	{
		"加密狗/穿山甲",
		{
			ApiBreakPointInfo("","CreateThread","寻找OEP"),
			ApiBreakPointInfo("","GetModuleHandleA","魔幻跳转"),
			ApiBreakPointInfo("","OpenMutexA","1转单进程两次改跳"),
			ApiBreakPointInfo("","GetSystemTime","补丁KEY"),
			ApiBreakPointInfo("","VirtualProtect","2EAX为401000返回"),
			ApiBreakPointInfo("","CreateFileMappingA","辅助"),
			ApiBreakPointInfo("","LoadLibraryA","载入DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","RefreshDeviceList","深思3"),
			ApiBreakPointInfo("","DeviceIoControl","操作设备"),
			ApiBreakPointInfo("","Prestochangoselector",""),
			ApiBreakPointInfo("","FreeEnvironmentStringsA","释放环境字串块"),
			ApiBreakPointInfo("","GetLogicalDriveStringsA","取列表"),
			ApiBreakPointInfo("","GetLogicalDrives","取驱动器列表"),
			ApiBreakPointInfo("","GetDriveTypeA","判断驱动器类型"),
			ApiBreakPointInfo("","CreateFileA","读狗驱动"),
			ApiBreakPointInfo("","FindFirstFileA","查找文件"),
		}
	},
	{
		"保留",
		{
		}
	},
	{
		"保留2",
		{
		}
	},
};

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

HWND hChecks[CHECK_COUNT];

HWND hTabControl;

HINSTANCE hInst;
HWND hMain;
WNDPROC DefTabControlProc;

int CurTab = 0;


DWORD WINAPI MsgLoopThread(LPVOID);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void DefBreakPointCallback() {}

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	//SetAPIBreakPoint("kernelbase.dll", "VirtualAlloc", UE_BREAKPOINT, UE_APIEND, DefBreakPointCallback);

	return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
	_plugin_menuaddentry(hMenu, MENU_MAINWINDOW_POPUP, "Set Api Breakpoint");

	// automaticly show main window, for test
	//if (!bIsMainWindowShow)
	//{
	//	CloseHandle(CreateThread(0, 0, MsgLoopThread, 0, 0, 0));
	//	bIsMainWindowShow = true;
	//}
}

// doing msg loop like WinMain
DWORD WINAPI MsgLoopThread(LPVOID)
{
	MSG msg;
	WNDCLASSA wc;
	HWND hwnd;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	wc.lpszMenuName = NULL;
	wc.lpszClassName = PLUGIN_NAME;

	RegisterClassA(&wc);

	hwnd = CreateWindowA(
		PLUGIN_NAME,
		"Standard Window",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		MAINWINDOW_WIDTH,
		MAINWINDOW_HEIGHT,
		NULL,
		NULL,
		g_hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	bIsMainWindowShow = false;

	return (int)msg.wParam;
}

VOID CenterDialog(HWND hDlg)
{
	HWND hwndOwner = NULL;
	RECT rcOwner, rcDlg, rc;
	// Get the owner window and dialog box rectangles. 			
	if ((hwndOwner = GetParent(hDlg)) == NULL)
	{
		hwndOwner = GetDesktopWindow();
	}
	GetWindowRect(hwndOwner, &rcOwner);
	GetWindowRect(hDlg, &rcDlg);
	CopyRect(&rc, &rcOwner);

	// Offset the owner and dialog box rectangles so that right and bottom 
	// values represent the width and height, and then offset the owner again 
	// to discard space taken up by the dialog box. 

	OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
	OffsetRect(&rc, -rc.left, -rc.top);
	OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

	// The new position is the sum of half the remaining space and the owner's 
	// original position. 

	SetWindowPos(hDlg,
		HWND_TOP,
		rcOwner.left + (rc.right / 2),
		rcOwner.top + (rc.bottom / 2),
		0, 0,          // Ignores size arguments. 
		SWP_NOSIZE);
}

// called when tab changed, update checkbox check(uncheck) and show(hide) state
void UpdateCheckBoxs()
{
	CurTab = TabCtrl_GetCurSel(hTabControl);
	size_t len = Groups[CurTab].apiList.size();
	for (size_t i = 0; i < CHECK_COUNT; i++)
	{
		if (i < len)
		{
			SetWindowTextA(hChecks[i], std::string(Groups[CurTab].apiList[i].apiName + " " + Groups[CurTab].apiList[i].description).c_str());
			if (Groups[CurTab].apiList[i].bWantToSetBp)
			{
				CheckDlgButton(hMain, IDC_CHECKS[i], BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hMain, IDC_CHECKS[i], BST_UNCHECKED);
			}
			ShowWindow(hChecks[i], SW_SHOW);
		}
		else
		{
			ShowWindow(hChecks[i], SW_HIDE);
		}
	}
}

// initialize main window, register tab control and checkbox
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCITEMA ti;
	HFONT defaultFont;
	hMain = hwnd;

	switch (iMsg)
	{
	case WM_CREATE:
	{
		defaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		InitCommonControls();

		hTabControl = CreateWindowA("SysTabControl32", "", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
			0, 0, MAINWINDOW_WIDTH-20, 22, hwnd, (HMENU)IDC_TABCTRL, hInst, NULL);

		for (int i = 0; i < TAB_COUNT; i++)
		{
			ti.mask = TCIF_TEXT;
			ti.pszText = (LPSTR)Groups[i].groupName.c_str();
			TabCtrl_InsertItem(hTabControl, i, &ti);
		}

		for (int i = 0; i < CHECK_COUNT; i++)
		{
			hChecks[i] = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "CreateThread(some descrition here)",
				WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_GROUP, 5 + (i / 25) * 250, 30 + 20 * (i % 25) + 5, 250, 20, hwnd, (HMENU)IDC_CHECKS[i], hInst, NULL);
			SendMessageA(hChecks[i], WM_SETFONT, (WPARAM)defaultFont, TRUE);
		}

		SendMessageA(hwnd, WM_SETFONT, (WPARAM)defaultFont, TRUE);
		SendMessageA(hTabControl, WM_SETFONT, (WPARAM)defaultFont, TRUE);

		TabCtrl_SetCurSel(hTabControl, 0);
		SetWindowTextA(hMain, PLUGIN_NAME);

		CenterDialog(hwnd);

		UpdateCheckBoxs();
	}
	return 0;
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{

		case TCN_SELCHANGE:
		{
			UpdateCheckBoxs();

			return TRUE;
		}
		}
	}
	return 0;
	case WM_COMMAND:
		for (int i = 0; i < CHECK_COUNT; i++)
		{
			if (LOWORD(wParam) == IDC_CHECKS[i])
			{
				if (IsDlgButtonChecked(hwnd, IDC_CHECKS[i]))
				{
					// checked, means user want to set bp here, then we'll try to use bp instruction set one.
					Groups[CurTab].apiList[i].bWantToSetBp = true;
					std::string cmd = "bp " + Groups[CurTab].apiList[i].apiName;
					Cmd(cmd.c_str());
				}
				else
				{
					Groups[CurTab].apiList[i].bWantToSetBp = false;
					std::string cmd = "bc " + Groups[CurTab].apiList[i].apiName;
					Cmd(cmd.c_str());
				}
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcA(hwnd, iMsg, wParam, lParam);
}


// set delay breakpoint when dll loaded
EXTERN_C __declspec(dllexport) void _cdecl CBLOADDLL(
	CBTYPE bType, // event type, one of the `cbType` CB_* values listed above
	PLUG_CB_LOADDLL* callbackInfo // pointer to a structure of information
)
{
	// check if there are any breakpoint can be set
	for (size_t i = 0; i < TAB_COUNT; i++)
	{
		for (size_t j = 0; j < Groups[i].apiList.size(); j++)
		{
			if (Groups[i].apiList[j].bWantToSetBp)
			{
				std::string cmd = "bp " + Groups[i].apiList[j].apiName;
				Cmd(cmd.c_str());
			}
		}
	}
}

// register menu to popup main window
extern "C" __declspec(dllexport) void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
	switch (info->hEntry)
	{
	case MENU_MAINWINDOW_POPUP:
		if (!bIsMainWindowShow && DbgIsDebugging())
		{
			CloseHandle(CreateThread(0, 0, MsgLoopThread, 0, 0, 0));
			bIsMainWindowShow = true;
		}

		break;
	}
}



