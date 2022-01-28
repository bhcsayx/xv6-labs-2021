#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int r){
	int base;
	if(read(r, &base, sizeof(int)) == 0) {
		exit(0);
	}
	else {
		printf("prime %d\n", base);
	}
	int p[2];
	pipe(p);
	if(fork()==0){
		close(p[1]);
		prime(p[0]);
		close(p[0]);
	}
	
	else {
		close(p[0]);
		int n,eof;
		do {
			eof = read(r, &n, sizeof(int));
			if(n%base != 0) {
				write(p[1], &n, sizeof(int));
			}
		} while (eof);
		
		close(p[1]);
	}
	
	wait((int*)0);
	exit(0);
}
	

int main(int argc, char const *argv[]) {
	int p[2];
	pipe(p);
	if(fork()) { // parent process
		close(p[0]);
		for(int i=2;i<36;i++) {
			write(p[1], &i, sizeof(int));
		}
		close(p[1]);
	}
	else {
		close(p[1]);
		prime(p[0]);
		close(p[0]);
	}
	wait((int*)0);
	exit(0);
}
