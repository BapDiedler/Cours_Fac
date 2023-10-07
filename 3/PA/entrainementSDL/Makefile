CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = main.c
OBJ = $(SRC:%.c=%.o)

PROG = spacebattle

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

MarioLike: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
