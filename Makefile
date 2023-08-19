default:
	gcc ./parser.c -o parser.exe -O3 -Wall  -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm