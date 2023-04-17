#
# Makefile to build test imrsnd ( player )
#
# Macro to perform cleanup
#
define cleanup
	mv prog bin
	rm *.o
endef
#
vpath %.h ../../include
CC := g++
FLAGS := -I ../../include
CCF := -L../../lib -limrsnd
PROG := prog
OBJ := test_player.o 
$(PROG): $(OBJ)
	$(CC) $(CCF) $^ -O2 -s -DNDEBUG -o $@ && $(cleanup)
test_player.o: test_player.cpp AudioDevice.h MIDIDevice.h Player.h AudioSystem.h MIDISystem.h
	$(CC) $(FLAGS) -c $<

