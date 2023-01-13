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


HWND hTabControl;
HWND hMain;
int CurTab = 0;

// checkbox handle
HWND hChecks[CHECK_COUNT];



/*
 * Add API Breakpoint here.
 * You can change display text language here if you want.
 * Dll name are not necessary so far cause we are using "bp" rather than SetBPX()
 * If the function name appears in multiple dlls, the behavior depends on the bp instruction
 */
#define CHINESE
#ifdef CHINESE
ApiGroup Groups[TAB_COUNT] =
{
	{
		"样本调试",
		{
			ApiBreakPointInfo("","LoadLibraryA","加载DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","GetModuleHandleA","查找模块"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetModuleHandleExA",""),
			ApiBreakPointInfo("","GetModuleHandleExW",""),
			ApiBreakPointInfo("","CreateFileA","创建或打开文件"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","ReadFile","读文件"),
			ApiBreakPointInfo("","WriteFile","写文件"),
			ApiBreakPointInfo("","DeleteFileA","删除文件"),
			ApiBreakPointInfo("","DeleteFileW",""),
			ApiBreakPointInfo("","CreateThread","创建线程"),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","OpenProcess","打开进程"),
			ApiBreakPointInfo("","WriteProcessMemory","跨进程写内存"),
			ApiBreakPointInfo("","ReadProcessMemory","跨进程读内存"),
			ApiBreakPointInfo("","CreateMutexA","创建互斥体"),
			ApiBreakPointInfo("","CreateMutexW",""),
			ApiBreakPointInfo("","OpenMutexA","打开互斥体"),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","CreateToolhelp32SnapShot","枚举进程"),
			ApiBreakPointInfo("","Heap32ListFirst",""),
			ApiBreakPointInfo("","Heap32ListNext",""),
			ApiBreakPointInfo("","Heap32First",""),
			ApiBreakPointInfo("","Heap32Next",""),
			ApiBreakPointInfo("","Module32First","枚举模块"),
			ApiBreakPointInfo("","Module32Next",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Process32First","枚举进程"),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","PostQuitMessage",""),
			ApiBreakPointInfo("","Toolhelp32ReadProcessMemory",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
			ApiBreakPointInfo("","SetTimer",""),
			ApiBreakPointInfo("","GetTempPathA",""),
			ApiBreakPointInfo("","GetTempPathW",""),
			ApiBreakPointInfo("","CreateProcessA","创建进程"),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","ShellExecuteA",""),
			ApiBreakPointInfo("","ShellExecuteW",""),
			ApiBreakPointInfo("","WinExec",""),
			ApiBreakPointInfo("","UrlDownloadToFileA","下载文件"),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
			ApiBreakPointInfo("","GetDesktopWindow",""),
		}
	},
	{
		// https://anti-debug.checkpoint.com/
		"对抗分析",
		{
			ApiBreakPointInfo("","IsDebuggerPresent","检测调试器"),
			ApiBreakPointInfo("","CheckRemoteDebuggerPresent","检测调试器"),
			ApiBreakPointInfo("","NtQueryInformationProcess","多个标志位检测调试器，检测父进程"),
			ApiBreakPointInfo("","UnhandledExceptionFilter",""),
			ApiBreakPointInfo("","OutputDebugStringA","检查错误码探测调试器"),
			ApiBreakPointInfo("","OutputDebugStringW",""),
			ApiBreakPointInfo("","GetThreadContext","探测硬件断点"),
			ApiBreakPointInfo("","GetProcessHeap","LFH:低碎片堆"),
			ApiBreakPointInfo("","GetProcAddress","检测HOOK"),
			ApiBreakPointInfo("","NtSetInformationThread","向调试器隐藏线程"),
			ApiBreakPointInfo("","NtYieldExecution","检测调试器"),
			ApiBreakPointInfo("","ReadProcessMemory","int3断点检测"),
			ApiBreakPointInfo("","VirtualProtect","修改内存权限触发异常检测调试器"),
			ApiBreakPointInfo("","VirtualProtectEx","修改内存权限触发异常检测调试器"),
			ApiBreakPointInfo("","RtlQueryProcessHeapInformation","堆标志位检测调试器"),
			ApiBreakPointInfo("","RtlQueryProcessDebugInformation","堆标志位检测调试器"),
			ApiBreakPointInfo("","NtQuerySystemInformation","检测调试器"),
			ApiBreakPointInfo("","OpenProcess","打开csrss.exe成功表示有调试器"),
			ApiBreakPointInfo("","CreateFileA","独占方式打开文件，失败表示有调试器"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","NtClose","捕获EXCEPTION_INVALID_HANDLE异常表示存在调试器"),
			ApiBreakPointInfo("","CloseHandle",""),
			ApiBreakPointInfo("","NtQueryObject","探测调试对象"),
			ApiBreakPointInfo("","SetUnhandledExceptionFilter","如果存在调试器，则回调不调用"),
			ApiBreakPointInfo("","RaiseException","抛出DBG_CONTROL_C等特殊异常，未接管则有调试器"),
			ApiBreakPointInfo("","RtlRaiseException","抛出DBG_CONTROL_C等特殊异常，未接管则有调试器"),
			ApiBreakPointInfo("","GetLocalTime","执行耗时估算，超时认为被调试"),
			ApiBreakPointInfo("","GetSystemTime","执行耗时估算，超时认为被调试"),
			ApiBreakPointInfo("","GetTickCount","执行耗时估算，超时认为被调试"),
			ApiBreakPointInfo("","NtGetTickCount","执行耗时估算，超时认为被调试"),
			ApiBreakPointInfo("","QueryPerformanceCounter","执行耗时估算，超时认为被调试"),
			ApiBreakPointInfo("","timeGetTime","执行耗时估算，超时认为被调试"),
			ApiBreakPointInfo("","NtQueryVirtualMemory","内存断点检测"),
			ApiBreakPointInfo("","AddVectoredExceptionHandler","注册VEH"),
			ApiBreakPointInfo("","RemoveVectoredExceptionHandler","移除VEH"),
			ApiBreakPointInfo("","DebugActiveProcess","创建子进程调试自己"),
			ApiBreakPointInfo("","DbgUiDebugActiveProcess","创建子进程调试自己"),
			ApiBreakPointInfo("","NtDebugActiveProcess","创建子进程调试自己"),
			ApiBreakPointInfo("","SetConsoleCtrlHandler","拦截CTRL_C_EVENT异常"),
			ApiBreakPointInfo("","BlockInput","一直返回TRUE表明被HOOK"),
			ApiBreakPointInfo("","EnumWindows","检测父进程窗口标题"),
			ApiBreakPointInfo("","SwitchDesktop","切换桌面反调试"),
			ApiBreakPointInfo("","FindWindowA","探测调试器窗口类名"),
			ApiBreakPointInfo("","FindWindowW","探测调试器窗口类名"),
			ApiBreakPointInfo("","FindWindowExA","探测调试器窗口类名"),
			ApiBreakPointInfo("","FindWindowExW","探测调试器窗口类名"),
			ApiBreakPointInfo("","DbgSetDebugFilterState",""),
			ApiBreakPointInfo("","SwitchToThread",""),
			ApiBreakPointInfo("","GetWriteWatch",""),
		}
	},
	{
		"注入",
		{
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
		"对话框",
		{
			ApiBreakPointInfo("","MessageBoxA","弹对话框"),
			ApiBreakPointInfo("","MessageBoxW",""),
			ApiBreakPointInfo("","MessageBoxExA",""),
			ApiBreakPointInfo("","MessageBoxExW",""),
			ApiBreakPointInfo("","MessageBoxIndirectA",""),
			ApiBreakPointInfo("","MessageBoxIndirectW",""),
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
		"其他",
		{
			ApiBreakPointInfo("","FindFirstFileA","查找文件"),
			ApiBreakPointInfo("","ExitProcess","程序退出"),
			ApiBreakPointInfo("","GetStartupInfoA","获取启动信息"),
			ApiBreakPointInfo("","GetFileSize","获取文件大小"),
			ApiBreakPointInfo("","VirtualProtect","Vmp脱壳"),
			ApiBreakPointInfo("","ExitWindowsEx","关机断点"),
			ApiBreakPointInfo("","CreateFileA","自校验"),
			ApiBreakPointInfo("","GetVersion","易语言脱壳"),
			ApiBreakPointInfo("","send","发送封包"),
			ApiBreakPointInfo("","WSASend","发送封包"),
			ApiBreakPointInfo("","recv","接收封包"),
			ApiBreakPointInfo("","RtlAdjustPrivilege","易语言快速关机"),
			ApiBreakPointInfo("","SHFormatDrive","格盘API"),
			ApiBreakPointInfo("","RemoveDirectoryA","删除目录"),
			ApiBreakPointInfo("","DeleteFileA","删除文件"),
			ApiBreakPointInfo("","GetLastError","返回错误码"),
		}
	},
};

#else

ApiGroup Groups[TAB_COUNT] =
{
	{
		"Common",
		{
			ApiBreakPointInfo("","FindFirstFileA","search file"),
			ApiBreakPointInfo("","ExitProcess",""),
			ApiBreakPointInfo("","GetStartupInfoA",""),
			ApiBreakPointInfo("","GetFileSize",""),
			ApiBreakPointInfo("","VirtualProtect","modify memory protect"),
			ApiBreakPointInfo("","ExitWindowsEx","shutdown breakpoint"),
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","GetVersion",""),
			ApiBreakPointInfo("","send",""),
			ApiBreakPointInfo("","WSASend",""),
			ApiBreakPointInfo("","recv",""),
			ApiBreakPointInfo("","RtlAdjustPrivilege",""),
			ApiBreakPointInfo("","SHFormatDrive","Format Disk"),
			ApiBreakPointInfo("","RemoveDirectoryA",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","GetLastError",""),
		}
	},
	{
		"Dialog",
		{
			ApiBreakPointInfo("","MessageBoxA","popup a message box"),
			ApiBreakPointInfo("","MessageBoxW",""),
			ApiBreakPointInfo("","MessageBoxExA",""),
			ApiBreakPointInfo("","MessageBoxExW",""),
			ApiBreakPointInfo("","MessageBoxIndirectA",""),
			ApiBreakPointInfo("","MessageBoxIndirectW",""),
			ApiBreakPointInfo("","GetWindowTextA","get control text"),
			ApiBreakPointInfo("","GetWindowTextW",""),
			ApiBreakPointInfo("","SetWindowTextA","set control text"),
			ApiBreakPointInfo("","SetWindowTextW",""),
			ApiBreakPointInfo("","GetDlgItemTextA",""),
			ApiBreakPointInfo("","GetDlgItemTextW",""),
			ApiBreakPointInfo("","SetDlgItemTextA","set control text"),
			ApiBreakPointInfo("","SetDlgItemTextW",""),
			ApiBreakPointInfo("","GetDlgItemInt",""),
			ApiBreakPointInfo("","SetDlgItemInt",""),
			ApiBreakPointInfo("","SendMessageA",""),
			ApiBreakPointInfo("","SendMessageW",""),
			ApiBreakPointInfo("","SendDlgItemMessage",""),
			ApiBreakPointInfo("","IsDialogMessageA",""),
			ApiBreakPointInfo("","IsDialogMessageW",""),
			ApiBreakPointInfo("","DispatchMessageA",""),
			ApiBreakPointInfo("","DispatchMessageW",""),
			ApiBreakPointInfo("","CallWindowProcA",""),
			ApiBreakPointInfo("","CallWindowProcW",""),
			ApiBreakPointInfo("","DefWindowProcA",""),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","MessageBeep",""),
			ApiBreakPointInfo("","DrawTextA",""),
			ApiBreakPointInfo("","DrawTextW",""),
			ApiBreakPointInfo("","DrawTextExA",""),
			ApiBreakPointInfo("","DrawTextExW",""),
			ApiBreakPointInfo("","FindWindowA",""),
			ApiBreakPointInfo("","FindWindowW",""),
			ApiBreakPointInfo("","GetClipboardData",""),
			ApiBreakPointInfo("","CoInitialize","initialize COM library"),
			ApiBreakPointInfo("","CoCreateInstance","create COM instance"),
			ApiBreakPointInfo("","LoadIconA",""),
			ApiBreakPointInfo("","LoadIconW",""),
			ApiBreakPointInfo("","SetWindowLongA","change window attribute"),
			ApiBreakPointInfo("","SetWindowLongW",""),
			ApiBreakPointInfo("","SetWindowLongPtrA",""),
			ApiBreakPointInfo("","SetWindowLongPtrW",""),
			ApiBreakPointInfo("","ShowWindow",""),
			ApiBreakPointInfo("","UpdateWindow",""),
			ApiBreakPointInfo("","CreateWindowExA",""),
			ApiBreakPointInfo("","CreateWindowExW",""),
			ApiBreakPointInfo("","CreateWindowA",""),
			ApiBreakPointInfo("","CreateWindowW",""),
			ApiBreakPointInfo("","DestroyWindow",""),
			ApiBreakPointInfo("","DialogBoxA",""),
			ApiBreakPointInfo("","DialogBoxW",""),
			ApiBreakPointInfo("","DialogBoxParamA",""),
			ApiBreakPointInfo("","DialogBoxParamW",""),
			ApiBreakPointInfo("","DialogBoxIndirectA",""),
			ApiBreakPointInfo("","DialogBoxIndirectW",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamA",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamW",""),
			ApiBreakPointInfo("","EndDialog",""),
			ApiBreakPointInfo("","TranslateMessage",""),
			ApiBreakPointInfo("","GetMessageA",""),
			ApiBreakPointInfo("","GetMessageW",""),
			ApiBreakPointInfo("","PeekMessageA",""),
			ApiBreakPointInfo("","PeekMessageW",""),
			ApiBreakPointInfo("","SetMenu",""),
			ApiBreakPointInfo("","DestroyMenu",""),
			ApiBreakPointInfo("","DeleteMenu",""),
			ApiBreakPointInfo("","EnableMenuItem",""),
			ApiBreakPointInfo("","EnableWindow",""),
		}
	},
	{
		"File",
		{
			ApiBreakPointInfo("","CreateFileA","create or open file"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","OpenFile",""),
			ApiBreakPointInfo("","ReadFile",""),
			ApiBreakPointInfo("","WriteFile",""),
			ApiBreakPointInfo("","GetFileSize",""),
			ApiBreakPointInfo("","FindFirstFileA",""),
			ApiBreakPointInfo("","FindFirstFileW",""),
			ApiBreakPointInfo("","GetModuleFileNameA",""),
			ApiBreakPointInfo("","GetModuleFileNameW",""),
			ApiBreakPointInfo("","OpenFileMappingA",""),
			ApiBreakPointInfo("","OpenFileMappingW",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetModuleHandleExA",""),
			ApiBreakPointInfo("","GetModuleHandleExW",""),
			ApiBreakPointInfo("","CreateFileMappingA",""),
			ApiBreakPointInfo("","CreateFileMappingW",""),
			ApiBreakPointInfo("","CopyFileA",""),
			ApiBreakPointInfo("","CopyFileW",""),
			ApiBreakPointInfo("","CopyFileExA",""),
			ApiBreakPointInfo("","CopyFileExW",""),
			ApiBreakPointInfo("","SetFilePointer",""),
			ApiBreakPointInfo("","MoveFileA",""),
			ApiBreakPointInfo("","MoveFileW",""),
			ApiBreakPointInfo("","MoveFileExA",""),
			ApiBreakPointInfo("","MoveFileExW",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW",""),
			ApiBreakPointInfo("","LoadCursorFromFileA",""),
			ApiBreakPointInfo("","LoadCursorFromFileW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA",""),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","GetPrivateProfileIntA",""),
			ApiBreakPointInfo("","GetPrivateProfileIntW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA",""),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","WritePrivateProfileStringA",""),
			ApiBreakPointInfo("","WritePrivateProfileStringW",""),
		}
	},
	{
		"Register",
		{
			ApiBreakPointInfo("","RegOpenKeyA",""),
			ApiBreakPointInfo("","RegOpenKeyW",""),
			ApiBreakPointInfo("","RegOpenKeyExA",""),
			ApiBreakPointInfo("","RegOpenKeyExW",""),
			ApiBreakPointInfo("","RegCreateKeyExA",""),
			ApiBreakPointInfo("","RegCreateKeyExW",""),
			ApiBreakPointInfo("","RegQueryValueA",""),
			ApiBreakPointInfo("","RegQueryValueW",""),
			ApiBreakPointInfo("","RegQueryValueExA",""),
			ApiBreakPointInfo("","RegQueryValueExW",""),
			ApiBreakPointInfo("","RegCreateKeyA",""),
			ApiBreakPointInfo("","RegCreateKeyW",""),
			ApiBreakPointInfo("","RegCloseKey",""),
			ApiBreakPointInfo("","RegDeleteKeyA",""),
			ApiBreakPointInfo("","RegDeleteKeyW",""),
			ApiBreakPointInfo("","RegEnumKeyExA",""),
			ApiBreakPointInfo("","RegEnumKeyExW",""),
			ApiBreakPointInfo("","RegSetValueA",""),
			ApiBreakPointInfo("","RegSetValueW",""),
			ApiBreakPointInfo("","RegSetValueExA",""),
			ApiBreakPointInfo("","RegSetValueExW",""),
		}
	},
	{
		"Time/Date",
		{
			ApiBreakPointInfo("","SetSystemTime",""),
			ApiBreakPointInfo("","TimerProc",""),//what is this
			ApiBreakPointInfo("","SetLocalTime",""),
			ApiBreakPointInfo("","GetLocalTime",""),
			ApiBreakPointInfo("","GetSystemTime",""),
			ApiBreakPointInfo("","GetCurrentTime",""),
			ApiBreakPointInfo("","GetFileTime",""),
			ApiBreakPointInfo("","GetTickCount",""),
			ApiBreakPointInfo("","CompareFileTime",""),
			ApiBreakPointInfo("","SetTimer",""),
			ApiBreakPointInfo("","KillTimer",""),
			ApiBreakPointInfo("","timeSetEvent",""),
		}
	},
	{
		"Process",
		{
			ApiBreakPointInfo("","CreateThread",""),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","OpenMutexA",""),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","WriteProcessMemory",""),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory",""),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
			ApiBreakPointInfo("","CreateProcessA",""),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","OpenProcess",""),
			ApiBreakPointInfo("","ExitProcess",""),
			ApiBreakPointInfo("","ExitThread",""),
			ApiBreakPointInfo("","TerminateProcess",""),
			ApiBreakPointInfo("","TerminateThread",""),
			ApiBreakPointInfo("","CreateToolhelp32Snapshot","enum process"),
			ApiBreakPointInfo("","Process32First",""),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","Module32Next",""),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Heap32ListFirst",""),
			ApiBreakPointInfo("","Heap32ListNext",""),
			ApiBreakPointInfo("","GetProcessHeap",""),
			ApiBreakPointInfo("","Heap32First",""),
			ApiBreakPointInfo("","Heap32Next",""),
			ApiBreakPointInfo("","PostQuitMessage",""),
			ApiBreakPointInfo("","IsDebuggerPresent",""),
			ApiBreakPointInfo("","OpenProcessToken",""),
			ApiBreakPointInfo("","OpenThreadToken",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
		}
	},
	{
		"Network",
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
		"Memory",
		{
			ApiBreakPointInfo("","FindWindow",""),
			ApiBreakPointInfo("","GetWindowThreadProcessId",""),
			ApiBreakPointInfo("","OpenProcess",""),
			ApiBreakPointInfo("","VirtualAllocEx",""),
			ApiBreakPointInfo("","WriteProcessMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory",""),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","CreateMutexA",""),
			ApiBreakPointInfo("","CreateMutexW",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetProcAddress",""),
			ApiBreakPointInfo("","VirtualAlloc",""),
			ApiBreakPointInfo("","HeapAlloc",""),
			ApiBreakPointInfo("","VirtualFree",""),
			ApiBreakPointInfo("","HeapFree",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","GetVersion",""),
			ApiBreakPointInfo("","ZwAllocateVirtualMemory",""),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
		}
	},
	{
		"Disk",
		{
			ApiBreakPointInfo("","GetDiskFreeSpaceA",""),
			ApiBreakPointInfo("","GetDiskFreeSpaceExA",""),
			ApiBreakPointInfo("","GetDiskFreeSpaceExW",""),
			ApiBreakPointInfo("","GetDriveTypeA",""),
			ApiBreakPointInfo("","GetDriveTypeW",""),
			ApiBreakPointInfo("","GetLogicalDrives",""),
			ApiBreakPointInfo("","GetLogicalDriveStringsA",""),
			ApiBreakPointInfo("","GetLogicalDriveStringsW",""),
		}
	},
	{
		"Malware",
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
			ApiBreakPointInfo("","FindResourceA",""),
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","GetVolumeInformation",""),
			ApiBreakPointInfo("","MultiByteToWideChar",""),
			ApiBreakPointInfo("","WideCharToMultiByte",""),
			ApiBreakPointInfo("","GetFileSize",""),
			ApiBreakPointInfo("","VarCyFromStr",""),
			ApiBreakPointInfo("","arBstrFromI2",""),
			ApiBreakPointInfo("","rtcFileLen",""),
			ApiBreakPointInfo("","rtcFileLenth",""),
			ApiBreakPointInfo("","rtcMsgBox",""),
			ApiBreakPointInfo("","rtcInputBox",""),
			ApiBreakPointInfo("","GetMemStr",""),
			ApiBreakPointInfo("","rtcR8ValFromBstr",""),
			ApiBreakPointInfo("","rtcGetPresendDate",""),
			ApiBreakPointInfo("","rtcBeep",""),
			ApiBreakPointInfo("","rtcTrimBstr",""),
			ApiBreakPointInfo("","rtcMidCharVar",""),
			ApiBreakPointInfo("","rtcLeftCharVar",""),
			ApiBreakPointInfo("","rtcRightCharVar",""),
			ApiBreakPointInfo("","StrConv","转换字符串"),
			ApiBreakPointInfo("","rtcT8ValFromBstr",""),
			ApiBreakPointInfo("","__vbaI2Str",""),
			ApiBreakPointInfo("","__vbaI4Str",""),
			ApiBreakPointInfo("","__vbar4Str",""),
			ApiBreakPointInfo("","__vbar8Str",""),
			ApiBreakPointInfo("","__vbavaradd",""),
			ApiBreakPointInfo("","__vbavarsub",""),
			ApiBreakPointInfo("","__vbavarmul",""),
			ApiBreakPointInfo("","__vbavaridiv",""),
			ApiBreakPointInfo("","__vbavarxor",""),
			ApiBreakPointInfo("","__vbavarcat",""),
			ApiBreakPointInfo("","__vbaStrCat",""),
			ApiBreakPointInfo("","__vbaVarCat",""),
			ApiBreakPointInfo("","__vbaStrCmp",""),
			ApiBreakPointInfo("","__vbaStrComp",""),
			ApiBreakPointInfo("","__vbaVarTstEq",""),
			ApiBreakPointInfo("","__vbaFreeStr",""),
			ApiBreakPointInfo("","__vbaStrCopy",""),
			ApiBreakPointInfo("","__vbaLenBstr",""),
			ApiBreakPointInfo("","__vbavarfornext",""),
			ApiBreakPointInfo("","__vbafreeobj",""),
		}
	},
	{
		"VC/MFC",
		{
			ApiBreakPointInfo("","lstrcmpA",""),
			ApiBreakPointInfo("","DefWindowProcA",""),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","RegisterClassA",""),
			ApiBreakPointInfo("","RegisterClassW",""),
			ApiBreakPointInfo("","RegisterClassExA",""),
			ApiBreakPointInfo("","RegisterClassExW",""),
			ApiBreakPointInfo("","FindResourceA",""),
			ApiBreakPointInfo("","FindResourceW",""),
			ApiBreakPointInfo("","LoadResource",""),
			ApiBreakPointInfo("","SetHandleCount",""),
			ApiBreakPointInfo("","IsWindowEnabled",""),
		}
	},
	{
		"Unpack",
		{
			ApiBreakPointInfo("","CreateThread",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","OpenMutexA",""),
			ApiBreakPointInfo("","GetSystemTime",""),
			ApiBreakPointInfo("","VirtualProtect",""),
			ApiBreakPointInfo("","CreateFileMappingA",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","RefreshDeviceList",""),
			ApiBreakPointInfo("","DeviceIoControl",""),
			ApiBreakPointInfo("","Prestochangoselector",""),
			ApiBreakPointInfo("","FreeEnvironmentStringsA",""),
			ApiBreakPointInfo("","GetLogicalDriveStringsA",""),
			ApiBreakPointInfo("","GetLogicalDrives",""),
			ApiBreakPointInfo("","GetDriveTypeA",""),
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","FindFirstFileA",""),
		}
	},
	{
		"Reserve",
		{
		}
	},
	{
		"Reserve2",
		{
		}
	},
};


#endif




DWORD WINAPI MsgLoopThread(LPVOID);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
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
			SetWindowTextA(hChecks[i], std::string(Groups[CurTab].apiList[i].apiName + "  " + Groups[CurTab].apiList[i].description).c_str());
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
			0, 0, MAINWINDOW_WIDTH-20, 22, hwnd, (HMENU)IDC_TABCTRL, g_hInstance, NULL);

		for (int i = 0; i < TAB_COUNT; i++)
		{
			ti.mask = TCIF_TEXT;
			ti.pszText = (LPSTR)Groups[i].groupName.c_str();
			TabCtrl_InsertItem(hTabControl, i, &ti);
		}

		for (int i = 0; i < CHECK_COUNT; i++)
		{
			
			hChecks[i] = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "CreateThread(some descrition here)",
				WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_GROUP,
				5 + (i / 25) * (MAINWINDOW_WIDTH/3), 30 + 20 * (i % 25) + 5, (MAINWINDOW_WIDTH / 3), 20, 
				hwnd, (HMENU)IDC_CHECKS[i], g_hInstance, NULL);
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



