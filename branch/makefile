all:
	g++ -o bin/cheap src/cheapInserction.cpp -std=c++11 -O2
	g++ -o bin/cena src/cena.cpp -std=c++11 -O2

run:
	./bin/cheap datosTSP/pr2392.tsp pr2392
	./plot.sh cheap pr2392

#pdf:
#	pdflatex report/main.tex
#	mv main.pdf report/branch.pdf
#	latexmk -c report/main.tex

ulysses:
	./bin/cheap datosTSP/ulysses16.tsp ulysses16
	./plot.sh cheap ulysses16

genetic:
	g++ -o bin/antiguo_genetic src/antiguo_genetic.cpp -std=c++11
	./bin/antiguo_genetic datosTSP/ulysses16.tsp ulysses16
	./plot.sh genetic ulysses16
