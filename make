# Define the list of .o files for p3
p3OBJECTS = client.o testServer.o
p3INCLUDES = testServer.h

# Default Rules for building each .o
%.o: %.c ${p3INCLUDES}
gcc –g –c $<

# Rule for building the executable
p3: ${p3OBJECTS}
gcc –g –o p3 ${p3OBJECTS}

# Special rule to remove the .o files
clean:
 rm –f ${p3OBJECTS}
