CC=g++
CFLAGS= -Wall -std=c++1z
DEPS= generateSHA.h gitInit.h indexCreate.h gitAdd.h tree.h gitCommit.h cat-file.h gitLog.h gitStatus.h gitCheckout.h diff.h gitRevert.h
OBJ= generateSHA.o gitInit.o indexCreate.o gitAdd.o tree.o gitCommit.o cat-file.o gitLog.o gitStatus.o gitCheckout.o diff.o gitRevert.o
TEMP=-lssl -lcrypto

mygit: mainRunner.cpp $(DEPS) 
	$(CC) $(CFLAGS) mainRunner.cpp cat-file.cpp gitInit.cpp gitAdd.cpp generateSHA.cpp indexCreate.cpp gitCommit.cpp tree.cpp gitLog.cpp gitStatus.cpp diff.cpp gitRevert.cpp gitCheckout.cpp $(TEMP) -o $@

gitInit.o: gitInit.cpp $(DEPS)
	$(CC) $(CFLAGS) gitInit.cpp -o $@

generateSHA.o: generateSHA.cpp $(DEPS)
	$(CC) $(CFLAGS) generateSHA.cpp $(TEMP) -o $@


indexCreate.o: indexCreate.cpp $(DEPS)
	$(CC) $(CFLAGS) indexCreate.cpp generateSHA.cpp $(TEMP) -o $@

gitAdd.o: gitAdd.cpp $(DEPS)
	$(CC) $(CFLAGS) gitAdd.cpp indexCreate.cpp generateSHA.cpp $(TEMP) -o $@

tree.o: tree.cpp $(DEPS)
	$(CC) $(CFLAGS) tree.cpp indexCreate.cpp generateSHA.cpp $(TEMP) -o $@

gitCommit.o: gitCommit.cpp $(DEPS)
	$(CC) $(CFLAGS) gitCommit.cpp tree.cpp indexCreate.cpp generateSHA.cpp $(TEMP) -o $@

cat-file.o: cat-file.cpp $(DEPS)
	$(CC) $(CFLAGS) cat-file.cpp gitCommit.cpp tree.cpp indexCreate.cpp generateSHA.cpp gitAdd.cpp $(TEMP) -o $@

gitInit.o: gitLog.cpp $(DEPS)
	$(CC) $(CFLAGS) gitLog.cpp -o $@

gitStatus.o: gitStatus.cpp $(DEPS)
	$(CC) $(CFLAGS) gitStatus.cpp indexCreate.cpp generateSHA.cpp -o $@

gitCheckout.o: gitCheckout.cpp $(DEPS)
	$(CC) $(CFLAGS) gitCheckout.cpp gitAdd.cpp indexCreate.cpp generateSHA.cpp $(TEMP) -o $@

diff.o: diff.cpp $(DEPS)
	$(CC) $(CFLAGS) diff.cpp -o $@

gitRevert.o: gitRevert.cpp $(DEPS)
	$(CC) $(CFLAGS) gitRevert.cpp diff.cpp gitStatus.cpp gitCommit.cpp tree.cpp indexCreate.cpp generateSHA.cpp gitAdd.cpp $(TEMP) -o $@

.PHONY : clean
clean :
		-rm *.o $(objects) mygit
