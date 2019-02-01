CXX=		g++
CXXFLAGS=	-g -Wall -g3 -gdwarf-2 -std=gnu++11 -lSDL2 -lSDL2_image -lSDL -lSDL_mixer
LD=		g++ -static-libstdc++
LDFLAGS=
SHELL=		bash
#MEASURE=	measure

all:		solution

solution:	MarioFirst.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@ 

#39_tiling.o:	39_tiling.cpp
#	$(LD) $(LDFLAGS) -o 39_tiling.o 39_tiling.cpp
clean:
	rm -f solution

#test:		test-output test-memory test-time
#
#test-output:	solution
#	@echo Testing output...
#	@diff --suppress-common-lines -y <(./solution < input) output
#
#test-memory:	solution
#	@echo Testing memory...
#	@[ `valgrind --leak-check=full ./solution < input 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]
#
#test-time:	measure.c solution
#	@echo Testing time...
#	@gcc -Wall -std=gnu99 -o measure measure.c
#	@./measure ./solution < input | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
#
#
