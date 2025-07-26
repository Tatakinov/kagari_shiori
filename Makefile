LIBRARY	= libkagari.so
OBJ=kagari.o kagari_unix.o

CXX = g++
LD = g++

CXXFLAGS	= -std=c++17 -O2 -I include -fPIC $(shell pkg-config --cflags lua)
LDFLAGS	= -shared $(shell pkg-config --libs lua)

.PHONY: all clean

.SUFFIXES: .cpp .o

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	$(RM) $(LIBRARY) $(OBJ)
