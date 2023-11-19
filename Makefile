# Configura o compilador
CC = gcc

# Gera warnings detalhadas ao compilar
CFLAGS = -Wall

LDLIBS = `pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_image-5 allegro_acodec-5 --libs --cflags`

# objetos a serem compilados
objs = spaceinvaders.o game.o enemies.o player.o obstacles.o shots.o utils.o display.o

out = spaceinvaders

# Regra principal
all: spaceinvaders

# Regras de ligacao
spaceinvaders: $(objs)

# Regras de compilacao
spaceinvaders.o: spaceinvaders.c game.h player.h display.h enemies.h obstacles.h shots.h utils.h
game.o: game.c game.h player.h display.h enemies.h  shots.h
enemies.o: enemies.c player.h display.h enemies.h shots.h utils.h
player.o: player.c enemies.h game.h player.h display.h obstacles.h shots.h
obstacles.o: obstacles.c display.h enemies.h utils.h
shots.o: shots.c player.h enemies.h obstacles.h shots.h utils.h
utils.o: utils.c utils.h
display.o: display.c display.h 
# Remove arquivos temporarios
clean:
	-rm -f *~ $(objs)

# Remove todos os arquivos do programa sem ser o codigo fonte
purge: clean
	-rm -f spaceinvaders