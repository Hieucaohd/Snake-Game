all: Main.cpp Game.hpp Game.cpp 
	g++ Main.cpp Game.hpp Game.cpp -w -lSDL2 -o RanSanMoi