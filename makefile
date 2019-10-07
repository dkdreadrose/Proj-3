p3OBJECTS = client.o testServer.o
p3INCLUDES = testServer.h

%.o: %.c ${p3INCLUDES}
	gcc –g –c $<

server: testServer.o
	gcc -g -o server testServer.o

client: client.o
	gcc –g –o client client.o

clean:
	rm –f ${p3OBJECTS}
