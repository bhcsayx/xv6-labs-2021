#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
	int p0[2];
	pipe(p0);
	
	int p1[2];
	pipe(p1);
	
	int child_id = fork();
	if (child_id < 0) {
		write(1, "fork error", 11);
		exit(-1);
	}
	
	if (child_id == 0) {
		close(p1[0]);
		close(p0[1]);
		char a[2];
		read(p0[0], a, 1);
		printf("%d: received ping\n", getpid());
		write(p1[0], "a", 1);
		exit(0);
	}
	
	if (child_id > 0) {
		close(p1[1]);
		close(p0[0]);
		write(p0[1], "a", 1);
		char a[2];
		read(p1[0], a, 1);
		printf("%d: received pong\n", getpid());
		wait((int*) 0);
		exit(0);
	}
		
	return 0;
}	
		
