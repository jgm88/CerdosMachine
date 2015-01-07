GCC=g++
CFLAGS=-std=c++11
INC_DIR=include/
LIB_DIR=lib/
MAINFILE=main

all: $(MAINFILE) 

$(MAINFILE): $(MAINFILE).cpp
	$(GCC) $(CFLAGS) $(MAINFILE).cpp -o $(MAINFILE) -I$(INC_DIR) -L$(LIB_DIR)


