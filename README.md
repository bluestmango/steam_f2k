Monitors steam and sends a notification every time a new free to keep game appears.
It is recommended to delete the notification email once you're done with it

I plan to add better config in the future, rather than hardcoding most fields

### Setup 
Anything beyond this point only needs to be done if you want to host this yourself.
these instructions might move to separate files included in releases. For now, they're going here so i don't forget

#### Windows
1. Run the setup script. When it finishes. it will launch the Windows Task Scheduler
2. Right-click the "steamf2k" task, and select "Properties"
3. Under the "Actions" tab, select the "Start a program" action and click "Edit"
4. Set the "Start in" field to your "steam_f2k" folder. This should be the folder that contains "steamf2k.exe"
5. Set the path to "steamf2k.exe" in the "Program/script" field
6. Save the changes

#### Linux
Add the following line to the crontab: "11-59/20 * * * * cd /home/YOUR_FILEPATH_HERE/steam_f2k/ && ./steamf2k"
Remove the quotes of course

### Building

Requires libcurl to build. Make is also heavily suggested, though technically not required