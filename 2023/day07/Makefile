CXX=g++
CXXFLAGS= -Wall -g

SRCS=$(shell find src -name *.cpp)
OBJS=$(subst src, build, $(SRCS:%.cpp=%.o))
# OBJS=build/day07.o build/card.o build/cardhand.o


bin/main: $(OBJS)
	echo Building executable
	$(CXX) $(CXXFLAGS) $(OBJS) -o bin/main

build/%.o : src/%.cpp
	echo Objects: $(OBJS)
	echo Compiling $@ from $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f build/*.o
	rm bin/main

