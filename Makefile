CC=g++
CFLAGS= -Wall -std=c++1z
DEPS= generateSHA.h gitInit.h gitAdd.h gitStatus.h gitLog.h gitCommit.h
OBJ= generateSHA.o gitInit.o mainRunner.o gitAdd.o gitStatus.o gitLog.o gitCommit.o

generateSHA.o: generateSHA.cpp $(DEPS)
	$(CC) $(CFLAGS) -lcrypto -lssl -o $@ $<

gitAdd.o: gitAdd.cpp $(DEPS)
	$(CC) $(CFLAGS) -lcrypto -lssl -o $@ $<

gitInit.o: gitInit.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

mainRunner.o: mainRunner.cpp $(DEPS) 
	$(CC) $(CFLAGS) -c -o $@ $<

gitStatus.o: gitStatus.cpp $(DEPS)
	$(CC) $(CFLAGS) -lcrypto -lssl -o $@ $<

gitLog.o: gitLog.cpp $(DEPS)
	$(CC) $(CFLAGS) -lcrypto -lssl -o $@ $<

gitCommit.o: gitCommit.cpp $(DEPS)
	$(CC) $(CFLAGS) -lcrypto -lssl -o $@ $<

mygit: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
		-rm *.o $(objects) mygit
