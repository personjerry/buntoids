OBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

ARCH=`uname -m`

PLATFORM=Linux
PROG=buntoids
DEST=../$(PROG)_$(ARCH)

LFLAGS=	`sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_gfx -lopenal -lvorbisfile
CFLAGS=	-c -ggdb3 -O0 -pedantic -std=c++98 -Weffc++ -Wall -Wextra -Wshadow \
		-Wunknown-pragmas -Wwrite-strings -Wdisabled-optimization \
		-Wconversion

main:$(OBJS)
	@echo -n "Linking..."
	@g++ $(OBJS) -o $(DEST) $(LFLAGS)
	@echo " Done"

%.o:%.cpp
	@echo "Compiling: $<"
	@g++ $< $(CFLAGS) -D$(PLATFORM)

clean:
	@echo -n "Cleaning up..."
	@rm -f *.o
	@echo " Done"

bak:
	@make clean
	@zip -q -j backup/$(PROG)_`date "+%x_(%X)"`.zip *

loc:
	@cat *.cpp *.h | wc -l

upx:
	@strip --strip-all $(DEST)
	@upx-nrv -q --ultra-brute -9 $(DEST)

