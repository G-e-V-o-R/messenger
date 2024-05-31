# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g -std=c++20 -Wall -Wextra -I$(HOME)/Downloads/boost_1_85_0 -I$(HOME)/Downloads/boost_1_85_0/libs/beast/example/common/ -I/usr/include/postgresql/ -I$(HOME)/Downloads/jwt-cpp-master/include -I$(HOME)/Desktop/messenger/inc 
		
# Linker flags
LDFLAGS = -L./lib -linternal -lssl -lcrypto -lpqxx -lpq
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin




bin/all: bin/messenger

bin/messenger: src/server.cpp #lib/internal.a
	$(CXX) $(CXXFLAGS)  src/server.cpp -o bin/messenger $(LDFLAGS)

#lib/internal.a: obj/handleRequests.o
#	ar -cvq lib/libinternal.a obj/handleRequests.o

#obj/handleRequests.o: src/handleRequests.cpp inc/handleRequests.h
#	g++ -c $(CXXFLAGS)  $(SRC_DIR)/handleRequests.cpp -o $(OBJ_DIR)/handleRequests.o $(LDFLAGS)
	
# Clean object and binary files
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

