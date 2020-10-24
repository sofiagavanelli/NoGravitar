LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++

all: game

%.o: %.cpp
	$(CXX) -c $< 

%.o: %.h
	$(CXX) $< -o $@

game: bullet.o bunker.o game.o main.o menu.o planet.o spaceship.o tank.o terrain.o textBox.o
	@echo "** Building the game"
	$(CXX) -o $@ $^ $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f game *.o


