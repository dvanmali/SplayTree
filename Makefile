CXX=g++ -Wall
OBJS = SplayTree.cpp
LIST = README Makefile main.cpp BSTNode.cpp BSTNode.h SplayTree.cpp SplayTree.h input.txt script.sh script_prof.sh

all:
	g++ main.cpp $(OBJS) -o prog2
	@echo "	Use a command with syntax './prog2 < input.txt' to test"
	@echo "	Test file format:"
	@echo "		First Line should be number of operations that follow"
	@echo "		Next few lines must be that many operations that follow"
	@echo "		Last Line should be print command"

turnin:
	turnin prog2@cs130a $(LIST)

clean:
	rm -f *~ prog1
