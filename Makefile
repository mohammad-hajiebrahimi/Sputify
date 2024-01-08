CC_EXEC= g++
CC_FLAGS= -c

CC= ${CC_EXEC} ${CC_FLAGS}
BUILD_DIR= build
SRC_DIR= src

Sputify.out: ${BUILD_DIR}/main.o
	g++ ${BUILD_DIR}/main.o -o Sputify.out

${BUILD_DIR}/main.o: main.cpp  ${SRC_DIR}/magic.hpp ${BUILD_DIR}/client.o ${BUILD_DIR}/music.o ${BUILD_DIR}/playlist.o

	g++ -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/music.o: ${SRC_DIR}/music.cc ${SRC_DIR}/music.hpp
	g++ -c ${SRC_DIR}/music.cc -o ${BUILD_DIR}/music.o

${BUILD_DIR}/client.o: ${SRC_DIR}/client.cc ${SRC_DIR}/client.hpp
	g++ -c ${SRC_DIR}/client.cc -o ${BUILD_DIR}/client.o

${BUILD_DIR}/playlist.o: ${SRC_DIR}/playlist.cc ${SRC_DIR}/playlist.hpp
	g++ -c ${SRC_DIR}/playlist.cc -o ${BUILD_DIR}/playlist.o

${BUILD_DIR}/help.o: ${SRC_DIR}/help.cc ${SRC_DIR}/help.hpp
	g++ -c ${SRC_DIR}/help.cc -o ${BUILD_DIR}/help.o

${BUILD_DIR}/music_exeption.o: ${SRC_DIR}/music_exeption.cc ${SRC_DIR}/music_exeption.hpp
	g++ -c ${SRC_DIR}/music_exeption.cc -o ${BUILD_DIR}/music_exeption.o

clean:
	rm ${BUILD_DIR}/*.o Sputify.out

run:
	./Sputify.out
