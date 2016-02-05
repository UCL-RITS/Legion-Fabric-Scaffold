#include <stdio.h>

void handle_error( cudaError_t error, const char* message)
{
	if(error!=cudaSuccess) {
		fprintf(stderr,"ERROR: %s : %s\n",message,cudaGetErrorString(error));
		exit(-1);
	}
}
