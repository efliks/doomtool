# doomtool

Doomtool is a super simple wrapper for classic DOOM that calculates 
the number of frames per second of a DOOM timedemo.

Put doomtool.exe in the same directory where doom.exe is. Then type in 
something like this:

    c:\doom > doomtool.exe doom.exe -timedemo demo3

Doomtool will start a DOOM timedemo, intercept realtics from the output, 
and convert them to frames per second.

So much easier than convering them manually at every DOOM benchmark!

## Installation instructions

To compile Doomtool, use WATCOM 1.9. Simply run wmake in the build folder:

    c:\doomtool > wmake -f makefile.wc

Optionally, compile doom.exe, a mock used for testing etc.:

    c:\doomtool > wmake -f makefile.wc doom.exe

Then, copy doomtool.exe to your folder containing classic DOOM.
