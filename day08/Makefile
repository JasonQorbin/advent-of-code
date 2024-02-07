CXX=g++
CXXFLAGS= -Wall -g
TARGET=main
TARGET_PATH=bin/$(TARGET)

# Get a list of all the cpp filepaths
SRCS=$(shell find src -name *.cpp)

# Create a list object filespaths by swapping the .cpp for .o
OBJS=$(subst src, build, $(SRCS:%.cpp=%.o))

# Default rule to build the target executable with the object files as dependencies.
bin/main: $(OBJS)
	echo Building executable
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET_PATH)

# Template rule to compile an .o file from every .cpp file
build/%.o : src/%.cpp
	echo Objects: $(OBJS)
	echo Compiling $@ from $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f build/*.o
	rm $(TARGET_PATH)

