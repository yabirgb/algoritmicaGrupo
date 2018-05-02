all:
	g++ -o cheap cheapInserction.cpp -std=c++11
	g++ -o near nearestNeighbour.cpp -std=c++11

run:
	./cheap datosTSP/pr2392.tsp pr2392
	./near datosTSP/pr2392.tsp pr2392	
	./plot.sh cheap pr2392
	./plot.sh nearest pr2392


ulysses:
	./cheap datosTSP/ulysses16.tsp ulysses16
	./near datosTSP/ulysses16.tsp ulysses16	
	./plot.sh cheap ulysses16
	./plot.sh nearest ulysses16
