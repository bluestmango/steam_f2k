@echo OFF
schtasks /create /tn steamf2k /xml config\schedule.xml
if %ERRORLEVEL% NEQ 0 (
	echo Setup error. Make sure to run as administrator
	pause
	exit /b %ERRORLEVEL%
)
schtasks /run /tn steamf2k
echo Setup will now launch the Windows Task Scheduler
pause
taskschd.msc
exit /b 0