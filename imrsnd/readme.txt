IMRSND readme file

This readme file explains how to build a shared library for this project.
The compiler we used is MinGW ( Minimalist GNU for Windows ).
If you have it already installed, ensure you got the pthreads ( posix pthreads ) package too,
if not, you can get it executing the mingw-get command line installer :

mingw-get install pthreads-w32

and the package will be downloaded and installed.
If you don't have the MinGW compiler installed yet, you can download the command line
installer from:

https://github.com/ismaelmosquera/cwmidi/

and also look at the paper 'MIDI Programming for Windows in C' in the 'Tools' chapter
to know how to install it easyly.

The 'imrsnd.dll' library should be already inside the 'lib' folder,
but if you want to rebuild it just type:

make

and the library will be built again and place it in the 'lib' folder.

