@echo off

mkdir ..\build
pushd ..\build

cl -Zi ..\src\main.cpp ..\src\mandelbrot.cpp ..\src\scomplex.cpp user32.lib Gdi32.lib

popd

