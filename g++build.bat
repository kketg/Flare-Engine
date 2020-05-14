@echo Building...
cd bin
g++ -c -I. ../src/main.cpp ../include/glad/glad.c
g++ -o Flare.exe main.o glad.o -L. -lglfw3 -lopengl32 -lgdi32
.\Flare
PAUSE