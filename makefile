CC=gcc
CFLAGS=-Wall -g -Wextra
IN= main.c graphics.c lacg.c
OUT= 3dprp
SDL=-IC:\Users\janba\Dev\i686-w64-mingw32\include -LC:\Users\janba\Dev\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lm

default:
	$(CC) $(IN) -o $(OUT) $(CFLAGS) $(SDL)

debug:
	$(CC) $(IN) -o $(OUT) $(CFLAGS) $(SDL)
	./$(OUT)