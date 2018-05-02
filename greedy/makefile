all:
	g++ -o cheap cheapInserction.cpp -std=c++11 -O2
	g++ -o near nearestNeighbour.cpp -std=c++11 -O2

run:
	./cheap datosTSP/pr2392.tsp pr2392
	./near datosTSP/pr2392.tsp pr2392	
	./plot.sh cheap pr2392
	./plot.sh nearest pr2392

pdf:
	pdflatex report/main.tex
	mv main.pdf report/greedy.pdf
	latexmk -c report/main.tex

ulysses:
	./cheap datosTSP/ulysses16.tsp ulysses16
	./near datosTSP/ulysses16.tsp ulysses16	
	./plot.sh cheap ulysses16
	./plot.sh nearest ulysses16


genetic:
	g++ -o genetic genetic.cpp -std=c++11
	./genetic datosTSP/ulysses16.tsp ulysses16
	./plot.sh genetic ulysses16

genetic-big:
	g++ -o genetic genetic.cpp -std=c++11
	./genetic datosTSP/pr2392.tsp pr2392
	./plot.sh genetic pr2392
