incVar:
	gcc incVar.c -pthread -g
	./a.out

sumVec:
	gcc sumVec.c -pthread -g
	./a.out

hello:
	gcc hello.c -pthread -g
	./a.out

all:
	incVar
	sumVec
	hello
