# the compiler: clang++ for C++ programs, use just clang for C programs
CXX = clang++

# compiler flags:
#  -g    		adds debugging information to the executable file
#  -Wall 		turns on most, but not all, compiler warnings
#  -std=c++11 	Allow C++11 code
CFLAGS = -g -Wall -std=c++11

# the build target executables
TARGET = d1s1 d1s2 d2s1 d2s2 d3s1 d4s1 d4s2 d5s1 d5s2 d6s1 d6s2 d7s1

# the all rule that "make" defaults to
all: $(TARGET)

# Rule for building binaries with .cc inputs
$(TARGET): %: %.cc
	$(CXX) $(CFLAGS) -o $@ $<

# the "make clean" rule
clean:
	$(RM) -rf $(TARGET) *.dSYM
