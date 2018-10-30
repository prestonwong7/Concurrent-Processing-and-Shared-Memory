all: SwimMill Fish Pellets

SwimMill: SwimMill.c
	gcc -o SwimMill SwimMill.c

Fish: Fish.c
	gcc -o Fish Fish.c -lm

Pellets: Pellets.c
	gcc -o Pellets Pellets.c

