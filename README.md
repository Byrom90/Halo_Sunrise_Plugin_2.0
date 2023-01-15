# Halo Sunrise Plugin 2.0

A Dashlaunch plugin designed to re-enable matchmaking on Xbox 360 Halo 3 by redirecting to custom servers. Based on the work of craftycodie found here: https://github.com/craftycodie/Sunrise-Plugin

This is a completely new plugin rather than a fork of the original hence the name 2.0

New features:
 - Disc tray bypass support - Plugin will detect the tray state during init and unload if it's open.
 - Unload support - Plugin can now be unloaded using tools etc.
 - Xex timestamp checking - Plugin will now check the xex timestamp against a known supported list before hooking/patching.
 - Ini config file - Some options can now be toggle true/false in the auto-generated Sunrise2.ini. Config values are checked each time Halo is loaded.

Credits:

 - craftycodie - Halo hooks and addresses
 - FreestyleDash Team - xkelib