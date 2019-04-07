#include <algorithm>
#include <iostream>
#include <string>
#include <omp.h>

class SharedArray
{
	private:
	char* array;
	int   index;
	int   size;
	bool  usemutex;

	public:
	SharedArray(int n, bool use) : size(n), index(0), usemutex(use)
	{
		array = new char[size];
		std::fill(array, array+size, '-');
	}

	~SharedArray()
	{
		delete[] array;
	}

	void addChar(char c)
	{
		if(usemutex)
		{
			#pragma omp critical
			{
				array[index] = c;
				spendSomeTime();
				index++;
			}
		}
		else
		{
			array[index] = c;
			spendSomeTime();
			index++;
		}
	}

	int countOccurrences(char c)
	{
		return std::count(array, array+size, c);
	}

	std::string toString()
	{
		return std::string(array, size);
	}

	private:
	void spendSomeTime()
	{
		int i,j;

		for(i = 0; i < 10000; i++)
		{
			for(j = 0; j < 100; j++)
			{
			/* These loops shouldn't be removed by the compiler */
			}
		}
	}
};

class ArrayFiller
{
	private:
	int nThreads, wSize;
	SharedArray* array;

	public:
	ArrayFiller(int nthreads, int worksize, bool usemutex) : nThreads(nthreads), wSize(worksize)
	{
		array = new SharedArray(wSize, usemutex);
	}

	void fillArrayConcurrently()
	{
		int i;

		#pragma omp parallel for schedule(runtime) private(i)
		for(i = 0; i < wSize; i++)
		{
			array->addChar('A'+ omp_get_thread_num());
		}
	}
	
	void printStats()
	{
		std::cout << array->toString() << " ";

		int i, j = 0, aux = 0;

		for(i = 0; i < nThreads; ++i)
		{
			aux = array->countOccurrences('A'+i);
			j += aux;
			std::cout << (char) ('A'+i) << "=" << aux << " ";
		}

		std::cout  << "S=" << j << std::endl;
	}

	~ArrayFiller()
	{
		delete array;
	}
};

int main(int argc, char** argv)
{
	int nthreads, worksize;

	if(argc != 3)
	{
		std::cout << "Uso:" << argv[0] << " <nthreads> <worksize>" << std::endl;

		exit(EXIT_FAILURE);
	}

	nthreads = atoi(argv[1]);
	worksize = atoi(argv[2]); /* worksize = tamanho do array */

	omp_set_num_threads(nthreads);

	ArrayFiller t1ct(nthreads,worksize,true);
	ArrayFiller t1cf(nthreads,worksize,false);
	ArrayFiller t1st(nthreads,worksize,true);
	ArrayFiller t1sf(nthreads,worksize,false);
	ArrayFiller t2ct(nthreads,worksize,true);
	ArrayFiller t2cf(nthreads,worksize,false);
	ArrayFiller t2st(nthreads,worksize,true);
	ArrayFiller t2sf(nthreads,worksize,false);
	ArrayFiller t3ct(nthreads,worksize,true);
	ArrayFiller t3cf(nthreads,worksize,false);
	ArrayFiller t3st(nthreads,worksize,true);
	ArrayFiller t3sf(nthreads,worksize,false);
	ArrayFiller t4nt(nthreads,worksize,true);
	ArrayFiller t4nf(nthreads,worksize,false);
	ArrayFiller t5nt(nthreads,worksize,true);
	ArrayFiller t5nf(nthreads,worksize,false);

	t4nt.fillArrayConcurrently();
	t4nf.fillArrayConcurrently();

	omp_set_schedule(omp_sched_static,4);
	t1ct.fillArrayConcurrently();
	t1cf.fillArrayConcurrently();

	omp_set_schedule(omp_sched_static,-1);
	t1st.fillArrayConcurrently();
	t1sf.fillArrayConcurrently();

	omp_set_schedule(omp_sched_dynamic,4);
	t2ct.fillArrayConcurrently();
	t2cf.fillArrayConcurrently();

	omp_set_schedule(omp_sched_dynamic,-1);
	t2st.fillArrayConcurrently();
	t2sf.fillArrayConcurrently();

	omp_set_schedule(omp_sched_guided,4);
	t3ct.fillArrayConcurrently();
	t3cf.fillArrayConcurrently();

	omp_set_schedule(omp_sched_guided,-1);
	t3st.fillArrayConcurrently();
	t3sf.fillArrayConcurrently();

	omp_set_schedule(omp_sched_auto,-1);
	t5nt.fillArrayConcurrently();
	t5nf.fillArrayConcurrently();

	std::cout << "Correct results should total exactly " << worksize << " chars" << std::endl;
	std::cout << "static  chunk mutex "; t1ct.printStats();
	std::cout << "static   nop  mutex "; t1st.printStats();
	std::cout << "dynamic chunk mutex "; t2ct.printStats();
	std::cout << "dynamic  nop  mutex "; t2st.printStats();
	std::cout << "guided  chunk mutex "; t3ct.printStats();
	std::cout << "guided   nop  mutex "; t3st.printStats();
	std::cout << "runtime  nop  mutex "; t4nt.printStats();
	std::cout << "auto     nop  mutex "; t5nt.printStats();
	std::cout << std::endl;
	std::cout << "static  chunk  nop  "; t1cf.printStats();
	std::cout << "static   nop   nop  "; t1sf.printStats();
	std::cout << "dynamic chunk  nop  "; t2cf.printStats();
	std::cout << "dynamic  nop   nop  "; t2sf.printStats();
	std::cout << "guided  chunk  nop  "; t3cf.printStats();
	std::cout << "guided   nop   nop  "; t3sf.printStats();
	std::cout << "runtime  nop   nop  "; t4nf.printStats();
	std::cout << "auto     nop   nop  "; t5nf.printStats();

	return EXIT_SUCCESS;
}
