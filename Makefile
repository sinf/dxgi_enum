
# todo: figure out the proper way to compile this
dxgi_enum.exe: dxgi_enum.c
	winegcc -o $@ $< -DINITGUID -DCOBJMACROS -ld3d11 -ldwmapi -ldxgi
	#x86_64-w64-mingw32-gcc -o $@ $< -Wall -DINITGUID -DCOBJMACROS -L/usr/lib/wine/x86_64-windows -I/usr/include/wine -ld3d11 -ldxgi -ldwmapi


