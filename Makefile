
PREFIX			:=	/Users/genelisp
PROJECT			:=  SpaceShipGame3D

CXX				:=	g++
CXX_FLAGS		:= -ggdb -DALMAAZ_DEBUG -Wall -Werror -pedantic-errors -Wno-long-long


FRAMEWORKS		:=  -F$(PREFIX)/Library/Frameworks -framework SFML\
					-framework sfml-graphics -framework sfml-system\
					-framework sfml-window -framework OpenGL

GO				:=	$(CXX) $(CXX_FLAGS)\
					-I$(PREFIX)/Library/Frameworks/SFML.framework/Headers\
					-I/sw/include

OUT				:=	$(PREFIX)/$(PROJECT)/spaceship_game_3d


all: Main.o Player.o Projectile.o Enemy.o BoundingBox.o 
	$(GO) $(FRAMEWORKS) $^ -o $(OUT)

Main.o: Main.cpp Player.cpp Enemy.cpp BoundingBox.h Projectile.cpp 
	$(GO) -c $<

Player.o:		Player.cpp Player.h
	$(GO) -c $<

Projectile.o:	Projectile.cpp BoundingBox.h
	$(GO) -c $<

Enemy.o:	Enemy.cpp Enemy.h BoundingBox.h
	$(GO) -c $<

BoundingBox.o:	BoundingBox.cpp BoundingBox.h
	$(GO) -c $<

clean:
	rm -f *.o;\
	rm -f $(PREFIX)/$(PROJECT)/spaceship_game_3d

