Mac OS:

1.install the X11
http://xquartz.macosforge.org/landing/

2.install the macports
https://www.macports.org

3.install the xorg-libxcb by macports
sudo port install xorg-libxcb

4.make sure the below flags is using in src/Makefile
-------------------------------------------------------------------------------------------
#for Mac OS install libxcb use macports
LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/opt/local/include/
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -L/opt/local/lib -lxcb
-------------------------------------------------------------------------------------------

other UNIX:

1.cause almost all the UNIX support X11 it is builtin

2.install the libxcb use package managers (apt-get, pkg, pacman...)
sudo apt-get install libxcb

3.make sure the below flags is using in src/Makefile
-------------------------------------------------------------------------------------------
#for UNIX-like OS
LINK_HEAD = -I/usr/local/include/monkc -I/usr/local/include/lemontea -I/usr/local/include/
LINK_BIN = -lpthread -L/usr/local/lib -lmonkc -llemontea -lxcb
-------------------------------------------------------------------------------------------