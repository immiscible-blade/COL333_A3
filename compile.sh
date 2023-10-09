CC=g++
CFLAGS=-Wall -std=c++17 -O3 -funroll-loops -DASIO_STANDALONE

INCLUDES=-Iinclude #-I/opt/homebrew/opt/openssl@1.1/include/

$(CC) $(CFLAGS) $(INCLUDES) src/inputmaker.cpp src/orgstosat.cpp -o bin/orgstosat