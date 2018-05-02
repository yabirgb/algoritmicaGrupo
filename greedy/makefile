all:
	g++ -o cheap cheapInserction.cpp -std=c++11
	./cheap datosTSP/pr2392.tsp datosTSP/pr2392.opt.tour
	./plot.sh

run:
	g++ -o cheap cheapInserction.cpp -std=c++11
	./cheap datosTSP/pr2392.tsp datosTSP/pr2392.opt.tour
	./plot.sh


ulysses:
	g++ -o cheap cheapInserction.cpp -std=c++11
	./cheap datosTSP/ulysses16.tsp datosTSP/ulysses16.opt.tour
	./plot.sh

genetic:
	g++ -o genetic genetic.cpp -std=c++11
	./genetic datosTSP/ulysses16.tsp datosTSP/ulysses16.opt.tour
	./plot.sh

genetic-big:
	g++ -o genetic genetic.cpp -std=c++11
	./genetic datosTSP/pr2392.tsp datosTSP/pr2392.opt.tour
	./plot.sh
