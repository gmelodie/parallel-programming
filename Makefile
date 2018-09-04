sumVec:
	gcc sumVec.c -pthread
	./a.out

hello:
	gcc hello.c -pthread
	./a.out

all:
	sumVec
	hello
