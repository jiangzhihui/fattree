run:compile
	./a.out 
compile:
	g++ -Wall -g Main.cc fattree.cc host.cc debug.cc utility.cc AggrSwitch.cc EdgeSwitch.cc CoreSwitch.cc
