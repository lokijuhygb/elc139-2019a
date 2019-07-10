#include <complex>
#include <iostream>

#include "tbb/tbb.h"

int main(int argc, char *argv[])
{
	int max_row, max_column, max_n;
	std::cin >> max_row;
	std::cin >> max_column;
	std::cin >> max_n;

	char **mat = (char**)malloc(sizeof(char*)*max_row);

	int nthreads = atoi(argv[1]);
	tbb::task_scheduler_init init(nthreads);

	for (int i=0; i<max_row;i++)
	{
		mat[i]=(char*)malloc(sizeof(char)*max_column);
	}

	tbb::parallel_for(0, max_row, 1, [&](int r)
	{
		for(int c = 0; c < max_column; ++c)
		{
			std::complex<double> z;
			int n = 0;

			while(abs(z) < 2 && ++n < max_n)
				z = std::pow(z, 2) + decltype(z)((double)c * 2 / max_column - 1.5,(double)r * 2 / max_row - 1);
			
			mat[r][c]=(n == max_n ? '#' : '.');
		}
	});

	for(int r = 0; r < max_row; ++r)
	{
		std::cout << std::string(mat[r]) << std::endl;
	}
}


