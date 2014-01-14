run:compile
	rm -f result 
	time ./a.out 
compile:
	g++ -Wall -g Main.cc fattree.cc host.cc debug.cc utility.cc AggrSwitch.cc EdgeSwitch.cc CoreSwitch.cc Cache.cc CachePlaceComp.cc
