all: plot

CMP=g++-11
CMP_KEYS=-Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -pedantic

plot: run
	#gnuplot plot.plt

run: build $(wildcard data.dat)
	./fft

build: $(wildcard *.cpp *.h Makefile)
	$(CMP) -std=c++17 $(CMP_KEYS) *.cpp -o fft

clear:
	rm -rf fft result.dat abs.dat
