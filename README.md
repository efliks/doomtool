# doomtool

Doomtool is a super simple wrapper for classic DOOM that calculates 
the number of frames per second of a DOOM timedemo.

Put doomtool.exe in the same folder as doom.exe. Then type in 
something like this:

    c:\doom > doomtool.exe doom.exe -timedemo demo3

Doomtool will start a DOOM timedemo, intercept realtics from the output, 
and convert them to frames per second.

## Installation instructions

To compile Doomtool, use WATCOM 1.9. Simply run wmake in the main folder:

    c:\doomtool > wmake -f makefile.wc

Note that it is necessary to have gitver.h. This file can be generated 
automatically by CMake in Linux. Copy it over to your DOS machine.

Optionally, you may compile doom.exe, a mock used for testing etc.:

    c:\doomtool > wmake -f makefile.wc doom.exe
