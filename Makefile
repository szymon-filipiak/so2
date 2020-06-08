
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -pthread
CXX := g++

all: main_app

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.h
	$(CXX) -c $< -o $@

main_app: main.o src/Bee.o src/Beekeeper.o src/PositionGenerator.o src/Position.o src/Hive.o src/Flower.o
	@echo "** Building the game"
	$(CXX) -o main_app main.o src/Bee.o src/Beekeeper.o src/PositionGenerator.o src/Position.o src/Hive.o src/Flower.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."					      
	rm -f thegame src/*.o

																 
