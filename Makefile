files = common.h macros.h main.h main.c src/frog.h src/frog.c src/map.h src/map.c src/render.h src/render.c src/logic.h src/logic.c src/bullet.h src/bullet.c src/plants.h src/plants.c src/crocodile.h src/crocodile.c collision.h collision.c

build: $(files)
	gcc $(files) -lncurses -o game

run:
	./game

clean:
	rm -f *.o