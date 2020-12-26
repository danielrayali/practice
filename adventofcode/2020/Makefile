# the compiler: clang++ for C++ programs, use just clang for C programs
CXX = clang++

# compiler flags:
#  -g    		adds debugging information to the executable file
#  -Wall 		turns on most, but not all, compiler warnings
#  -std=c++11 	Allow C++11 code
CFLAGS = -g -Wall -std=c++11

# the build target executable:
TARGET = d1s1 d1s2 d2s1 d2s2

all: $(TARGET)

# Rule for building binaries with .cc inputs
$(TARGET): %: %.cc
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	$(RM) -rf $(TARGET) *.dSYM
