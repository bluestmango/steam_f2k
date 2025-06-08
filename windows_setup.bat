@echo OFF
schtasks /create /tn steamf2k /xml "%~dp0config/schedule.xml"
if %ERRORLEVEL% NEQ 0 (
	echo Setup error. Make sure to run as administrator
	pause
	exit /b %ERRORLEVEL%
)
echo Setup will now launch the Windows Task Scheduler
pause
taskschd.msc
exit /b 0