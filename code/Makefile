# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Executable name
TARGET = main.app

# Object files
OBJS = main.o stack.o

# Rule to make everything
all: $(TARGET)

# Rule to remake everything. Touches all the sources
rebuild: clean all

# Rule to link the program and delete object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	rm -f $(OBJS) # Command added to delete object files

# Rule to compile the source files
main.o: main.cpp stack.h
	$(CXX) $(CXXFLAGS) -c main.cpp

stack.o: stack.cpp stack.h node.h
	$(CXX) $(CXXFLAGS) -c stack.cpp

# Rule to clean files
clean:
	rm -f $(TARGET) *.o

# Valgrind memory leak check
memcheck:
	valgrind --leak-check=full ./$(TARGET)
	