# Sanele Mpangalala
#23 March 2016

driver.run: driver.o volimage.o
	g++ -o driver.run driver.o volimage.o
driver.o: driver.cpp volimage.h
	g++ -c -o driver.o driver.cpp
volimage.o: volimage.cpp volimage.h
	g++ -c -o volimage.o volimage.cpp
clean:
	rm -f *.o
	rm -f driver.run
