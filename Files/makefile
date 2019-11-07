CC = c++
DEPS = player3.h
OBJ = player3.o testd.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

player2: $(OBJ)
	$(CC) -o $@ $^
