CFLAGS = -Wall -pedantic -Werror
LFLAGS = `sdl-config --libs` -lSDL -lSDL_image -lSDL_mixer
OBJS   = main.o
PROG = asteroids
CXX = gcc

all: $(PROG)

install:
	sudo apt-get install libsdl1.2debian
	sudo apt-get install libsdl-image1.2-dev
	sudo apt-get install libsdl-mixer1.2-dev

%.o: src/%.c src/%.h
	$(CXX) $(CFLAGS) -c -s $<

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LFLAGS)

clean:
	rm $(PROG) *.o
