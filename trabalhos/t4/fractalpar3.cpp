/*
Fractal code for CS 4380 / CS 5351

Copyright (c) 2018, Texas State University. All rights reserved.

Redistribution and usage in source and binary form, with or without
modification, is only permitted for educational use.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Author: Martin Burtscher
*/

#include <cstdlib>
#include <sys/time.h>
#include <omp.h>
#include "fractal/fractal.h"

static const double Delta = 0.001;
static const double xMid  = 0.23701;
static const double yMid  = 0.521;

int main(int argc, char *argv[])
{
	// check command line
	if(argc != 4)
	{
		fprintf(stderr, "usage: %s frame_width num_frames num_threads\n", argv[0]);
		exit(-1);
	}

	int width = atoi(argv[1]);
	if(width < 10)
	{
		fprintf(stderr, "error: frame_width must be at least 10\n");
		exit(-1);
	}

	int frames = atoi(argv[2]);
	if(frames < 1)
	{
		fprintf(stderr, "error: num_frames must be at least 1\n");
		exit(-1);
	}

	int nthreads = atoi(argv[3]);
	if(nthreads < 1)
	{
		fprintf(stderr, "error: num_threads must be at least 1\n");
		exit(-1);
	}
// 	printf("computing %d frames of %d by %d fractal with %d nthreads\n", frames, width, width, nthreads);

	omp_set_num_threads(nthreads);
	
	// allocate picture array
	unsigned char* pic = new unsigned char[frames * width * width];

	// start time
	timeval start, end;
	gettimeofday(&start, NULL);

		// compute frames
		double delta = Delta;

		for(int frame = 0; frame < frames; frame++)
		{
			const double xMin = xMid - delta;
			const double yMin = yMid - delta;
			const double dw = 2.0 * delta / width;

			#pragma omp parallel for schedule(dynamic)
			for(int rowcol = 0; rowcol < width*width; rowcol++)
			{
				int row = rowcol%width;
				int col = rowcol/width;
				
				const double cx = xMin + row * dw;
				double x = cx;
				double y = yMin + col * dw;
				int depth = 256;
				double x2, y2;

				do
				{
					x2 = x * x;
					y2 = y * y;
					y = 2 * x * y + (yMin + col * dw);
					x = x2 - y2 + cx;
					depth--;
				}
				while((depth > 0) && ((x2 + y2) < 5.0));

				pic[frame * width * width + col * width + row] = (unsigned char)depth;
			}

			delta *= 0.98;
		}

	// end time
	gettimeofday(&end, NULL);
	long runtime = (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
	//printf("compute time: %ld usec\n", runtime);
	printf("3,%d,%d,%d,%ld\n", width, frames, nthreads, runtime);

	// verify result by writing frames to BMP files
	if((width <= 256) && (frames <= 100))
	{
		for(int frame = 0; frame < frames; frame++)
		{
			char name[32];
			sprintf(name, "fractal%d.bmp", frame + 1000);
			writeBMP(width, width, &pic[frame * width * width], name);
		}
	}

	delete [] pic;
	return 0;
}
