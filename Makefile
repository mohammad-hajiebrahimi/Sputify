CC_EXEC= g++
CC_FLAGS= -c

CC= ${CC_EXEC} ${CC_FLAGS}
BUILD_DIR= build
SRC_DIR= src

Sputify.out: ${BUILD_DIR}/main.o
	g++ ${BUILD_DIR}/main.o -o Sputify.out

${BUILD_DIR}/main.o: main.cpp
	g++ -c main.cpp -o ${BUILD_DIR}/main.o

clean:
	rm ${BUILD_DIR}/*.o Sputify.out

run:
	./Sputify.out
