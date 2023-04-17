#
# Makefile to build test imrsnd ( recorder )
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
OBJ := test_recorder.o 
$(PROG): $(OBJ)
	$(CC) $(CCF) $^ -O2 -s -DNDEBUG -o $@ && $(cleanup)
test_recorder.o: test_recorder.cpp AudioDevice.h AudioSystem.h Player.h AudioPlayer.h AudioRecorder.h AudioFile.h WaveAudioFile.h
	$(CC) $(FLAGS) -c $<

