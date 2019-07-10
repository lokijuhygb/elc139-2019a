FLAGS=-O3 -std=c++11
CXXFLAGS=-Wall -Wextra -pedantic
LDFLAGS=-fopenmp
LDDFLAGS=-ltbb

RM=rm -f

TARGET = mandelbrot_serial mandelbrot_openmp mandelbrot_openmp_simd mandelbrot_tbb mandelbrot_tbb_simd

all: $(TARGET)

mandelbrot_serial:
	$(CXX) $(FLAGS) mandelbrot_serial.cpp -c -o mandelbrot_serial.o
	$(CXX) $(FLAGS) mandelbrot_serial.o -o mandelbrot_serial

mandelbrot_openmp:
	$(CXX) $(FLAGS) $(LDFLAGS) mandelbrot_openmp.cpp -c -o mandelbrot_openmp.o
	$(CXX) $(FLAGS) $(LDFLAGS) mandelbrot_openmp.o -o mandelbrot_openmp

mandelbrot_openmp_simd:
	$(CXX) $(FLAGS) $(LDFLAGS) mandelbrot_openmp_simd.cpp -c -o mandelbrot_openmp_simd.o
	$(CXX) $(FLAGS) $(LDFLAGS) mandelbrot_openmp_simd.o -o mandelbrot_openmp_simd

mandelbrot_tbb:
	$(CXX) $(FLAGS) $(LDDFLAGS) $(LDFLAGS) mandelbrot_tbb.cpp -c -o mandelbrot_tbb.o
	$(CXX) $(FLAGS) $(LDDFLAGS) $(LDFLAGS) mandelbrot_tbb.o -o mandelbrot_tbb

mandelbrot_tbb_simd:
	$(CXX) $(FLAGS) $(LDDFLAGS) $(LDFLAGS) mandelbrot_tbb_simd.cpp -c -o mandelbrot_tbb_simd.o
	$(CXX) $(FLAGS) $(LDDFLAGS) $(LDFLAGS) mandelbrot_tbb_simd.o -o mandelbrot_tbb_simd

clean:
	$(RM) *.o $(TARGET)
