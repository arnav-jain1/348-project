# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Executable name
TARGET = main.out

# Object files
OBJS = main.o

# Rule to make everything
all: $(TARGET)

# Rule to remake everything. Touches all the sources
rebuild: clean all

# Rule to link the program and delete object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	rm -f $(OBJS) # Command added to delete object files

# Rule to compile the source files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Rule to clean files
clean:
	rm -f $(TARGET) *.o

# Valgrind memory leak check
memcheck:
	valgrind --leak-check=full ./$(TARGET)
	