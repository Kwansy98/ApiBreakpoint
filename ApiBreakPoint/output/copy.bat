set x64dbgdir="D:\retools\snapshot_2022-10-18_22-09\release\"
::set x64dbgdir="D:\retools\snapshot_2022-01-21_09-58\release\"
set batdir=%~dp0
echo %batdir%
copy %batdir%\ApiBreakPoint.dp32 %x64dbgdir%\x32\plugins\
copy %batdir%\ApiBreakPoint.dp64 %x64dbgdir%\x64\plugins\