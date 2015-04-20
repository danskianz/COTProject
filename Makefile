CXX=g++ 
CXXFLAGS=-Wno-write-strings -fverbose-asm -march=native -O0 -pipe -fstack-protector --param=ssp-buffer-size=4 -std=c++0x 



all: MainStandardDES

MainStandardDES: MainStandardDES.o 
	$(CXX) $(CXXFLAGS) -g $(INCLUDES) MainStandardDES.o 

MainStandardDES.o: MainStandardDES.s
	$(CXX) $(CXXFLAGS) -g -c $(INCLUDES) MainStandardDES.s -o MainStandardDES.o 

MainStandardDES.i: MainStandardDES.cpp StandardDES.h 
	$(CXX) $(CXXFLAGS) -g -E $(INCLUDES) MainStandardDES.cpp -o MainStandardDES.i 

MainStandardDES.s: MainStandardDES.i
	$(CXX) $(CXXFLAGS) -g -S $(INCLUDES) MainStandardDES.i -o MainStandardDES.s 

clean:
	rm -f MainStandardDES.o main MainStandardDES.s MainStandardDES.i 
