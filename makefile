# Christopher Kane, jwi705
# Sarah Marynak, oos266

p3OBJECTS = client.o testServer.o

server: testServer.o
	gcc -g -o server testServer.o

client: client.o
	gcc -g -o client client.o

clean:
	rm -f ${p3OBJECTS}
