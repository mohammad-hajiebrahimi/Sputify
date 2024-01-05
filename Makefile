CC_EXEC= g++
CC_FLAGS= -c

CC= ${CC_EXEC} ${CC_FLAGS}
BUILD_DIR= build
SRC_DIR= src

Sputify.out: ${BUILD_DIR}/main.o
	g++ ${BUILD_DIR}/main.o -o Sputify.out

${BUILD_DIR}/main.o: main.cpp ${SRC_DIR}/client.cc ${SRC_DIR}/magic.hpp ${SRC_DIR}/music.cc ${SRC_DIR}/playlist.cc ${SRC_DIR}/help.cc ${SRC_DIR}/music_exeption.cc ${SRC_DIR}/playlist_exeption.cc ${SRC_DIR}/user_exeption.cc
	g++ -c main.cpp -o ${BUILD_DIR}/main.o

${SRC_DIR}/client.cc: ${SRC_DIR}/client.hpp

clean:
	rm ${BUILD_DIR}/*.o Sputify.out

run:
	./Sputify.out
