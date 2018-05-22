all:
	g++ -o bin/bb src/bb.cpp -std=c++11 -O2
#	g++ -o bin/cena src/cena.cpp -std=c++11 -O2

run:
	./bin/bb datosTSP/ulysses16.tsp ulysses16
	./plot.sh bb ulysses16
	
random:
	./bin/bb aleatorios/aleatorio16.tsp aleatorio16
	./plot.sh bb aleatorio16
	
val:
	g++ -o bin/bb src/bb.cpp -std=c++11 -O2 -g
	valgrind --leak-check=full ./bin/bb datosTSP/ulysses16.tsp ulysses16
	

#pdf:
#	pdflatex report/main.tex
#	mv main.pdf report/branch.pdf
#	latexmk -c report/main.tex

big:
	./bin/bb datosTSP/pr2392.tsp pr2392
	./plot.sh bb pr2392

genetic:
	g++ -o bin/genetic src/genetic.cpp -std=c++11
	./bin/genetic datosTSP/ulysses16.tsp ulysses16
	./plot.sh genetic ulysses16
