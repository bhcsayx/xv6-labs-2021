#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		write(1, "Too few arguments", 18);
		exit(1);
	}
	
	int length = atoi(argv[1]);
	sleep(length);
	
	exit(0);
}
