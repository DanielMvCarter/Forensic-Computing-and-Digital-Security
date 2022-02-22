#include "../lib/user/syscall.h"

int main (int argc, char *argv[])
{
	const char *file = "BIGOLTEST";

	bool success = create(file, 32);
	int filedesc = open(file);
	char bufferw[33] = "pebi52";
	char bufferr[32];
	int size = write(filedesc, bufferw, sizeof bufferw);
	seek(filedesc, 0);
	size = read(filedesc, bufferr, sizeof bufferr);

	
	return 0;
}