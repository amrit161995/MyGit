CC=g++
CFLAGS= -Wall -std=c++1z
DEPS= gitInit.h gitAdd.h
OBJ= gitInit.o mainRunner.o gitAdd.o

gitAdd.o: gitAdd.cpp 
	$(CC) $(CFLAGS) -lcrypto -lssl -o $@ $<

gitInit.o: gitInit.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

mainRunner.o: mainRunner.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	
mygit: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
		-rm *.o $(objects) mygit