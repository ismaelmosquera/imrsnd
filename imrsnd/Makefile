#
# Makefile to build imrsnd.dll
#
# Macro to perform reordering and cleanup
#
define cleanup
	mv imrsnd.dll lib
	rm *.o
endef
#
vpath %.h include
VPATH := src
CC := g++
FLAGS := -I include
SLIB := imrsnd.dll
OBJ := Audio.o AudioFileHeader.o EndianUtil.o FileUtil.o WaveAudioFile.o AudioSystem.o AudioInDevice.o AudioOutDevice.o AudioPlayer.o AudioRecorder.o \
MIDITrack.o MIDISong.o MIDIFile.o MIDIUtil.o MIDIPlayer.o MIDIInDevice.o MIDIOutDevice.o MIDISystem.o
$(SLIB): $(OBJ)
	$(CC) $^ -shared -lwinmm -lpthread -lm -O2 -s -DNDEBUG -o $@ && $(cleanup)	
Audio.o: Audio.cpp Audio.h
	$(CC) $(FLAGS) -c $<
AudioFileHeader.o: AudioFileHeader.cpp AudioFileHeader.h
	$(CC) $(FLAGS) -c $<
EndianUtil.o: EndianUtil.cpp EndianUtil.h
	$(CC) $(FLAGS) -c $<
FileUtil.o: FileUtil.cpp FileUtil.h
	$(CC) $(FLAGS) -c $<
WaveAudioFile.o: WaveAudioFile.cpp WaveAudioFile.h EndianUtil.h FileUtil.h
	$(CC) $(FLAGS) -c $<
AudioSystem.o: AudioSystem.cpp AudioSystem.h AudioDevice.h AudioInDevice.h AudioOutDevice.h Player.h AudioPlayer.h AudioRecorder.h AudioFile.h WaveAudioFile.h
	$(CC) $(FLAGS) -c $<
AudioInDevice.o: AudioInDevice.cpp AudioInDevice.h
	$(CC) $(FLAGS) -c $<
AudioOutDevice.o: AudioOutDevice.cpp AudioOutDevice.h
	$(CC) $(FLAGS) -c $<
AudioPlayer.o: AudioPlayer.cpp AudioPlayer.h AudioFile.h WaveAudioFile.h
	$(CC) $(FLAGS) -c $<
AudioRecorder.o: AudioRecorder.cpp AudioRecorder.h 
	$(CC) $(FLAGS) -c $<
MIDITrack.o: MIDITrack.cpp MIDITrack.h MIDIEvent.h
	$(CC) $(FLAGS) -c $<
MIDISong.o: MIDISong.cpp MIDISong.h MIDITrack.h
	$(CC) $(FLAGS) -c $<
MIDIFile.o: MIDIFile.cpp MIDIFile.h MIDIEvent.h MIDITrack.h FileUtil.h
	$(CC) $(FLAGS) -c $<
MIDIUtil.o: MIDIUtil.cpp MIDIUtil.h MIDIEvent.h
	$(CC) $(FLAGS) -c $<
MIDIPlayer.o: MIDIPlayer.cpp MIDIPlayer.h MIDIEvent.h MIDIFile.h MIDIUtil.h
	$(CC) $(FLAGS) -c $<
MIDIInDevice.o: MIDIInDevice.cpp MIDIInDevice.h MIDIDevice.h
	$(CC) $(FLAGS) -c $<
MIDIOutDevice.o: MIDIOutDevice.cpp MIDIOutDevice.h MIDIDevice.h
	$(CC) $(FLAGS) -c $<
MIDISystem.o: MIDISystem.cpp MIDISystem.h MIDIInDevice.h MIDIOutDevice.h MIDIPlayer.h MIDIFile.h
	$(CC) $(FLAGS) -c $<
