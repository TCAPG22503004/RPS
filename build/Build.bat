@echo off

rem ---------------------------
rem List of File 
rem (Link from under to upper)
rem ---------------------------
set f0=main
set f1=title
set f2=menu
set f3=game
set f4=gameimage
set f5=gamebet
set f6=gameselect
set f7=gameresult
set f8=gameplayer
set f9=gameother
set f10=gameonline
set f11=result
set f12=click
set f13=mysql




rem ------------------------------
rem Not need to change under here
rem ------------------------------

rem -- create variable of file's name --

setlocal enabledelayedexpansion
set fc= 
set fo= 
set i=0

:FOREACH_FILELIST
set f=!f%i%!
if defined f (
	set fc=%f%.cpp %fc%
	set fo=%f%.o %fo%
	set /a i+=1
	goto :FOREACH_FILELIST
)



rem -- Build and execute --

cd ../src
g++ -c %fc% -I../../../DxLibFile -I../../../MysqlConnectorC/include -I../include -DDX_GCC_COMPILE -fexec-charset=UTF-8
g++ %fo% -o ../build/RPS.exe -L../../../DxLibFile -L../../../MysqlConnectorC/lib -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt -Wl,-subsystem,windows -lmysql
del *.o
cd ../build/
start RPS.exe
cd ../miscellaneous
