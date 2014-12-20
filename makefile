CFLAGS = -Wall -pedantic
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image -lSDL_mixer -lSDL_gfx
OBJS   = main.o
PROG = asteroids
CXX = gcc

all: $(PROG)

install:
	sudo apt-get install libsdl1.2debian
	sudo apt-get install libsdl-image1.2-dev
	sudo apt-get install libsdl-mixer1.2-dev
	sudo apt-get install libsdl-gfx1.2-dev

%.o: src/%.c src/%.h
	$(CXX) $(CFLAGS) -c -s $<

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS) -lm

clean:
	rm $(PROG) *.o