load kernel and xam modules from the symsrv directory in ida against symbols
	- simply place the exe/dll beside the matching .pdb and load the exe/dll with default options with ida, let it load symbols

use the included .idc script to list the exports
	- right click on message window and clear it
	- file -> script -> choose the idc

copy and paste the kernel exports into a file called kernel.def
	- right click on message window, select all, and copy
copy and paste the xam exports into a file called xam.def beside deffix.exe and _runit.bat
	- right click on message window, select all, and copy, paste into a new text file

run _runit.bat

profit, xam.def and kernel.def will now have all functions findable through libdump and sdk libraries commented out
as well as the library version string added directly from the libdump info to the .def header, as well as any manually
added function in manuals_xam.txt. Set up a new target and rename the files accordingly.

