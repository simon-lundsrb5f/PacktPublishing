all:
	glib-compile-resources --generate-source --target MyLogoResource.c MyLogoResource.xml
	glib-compile-resources --generate-header --target MyLogoResource.h MyLogoResource.xml
	gcc -o MyLogo.exe -w -g main.c MyLogo.c MyLogoResource.c `pkg-config --libs --cflags gtk+-3.0`