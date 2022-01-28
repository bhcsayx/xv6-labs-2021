#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[]) {
	char buf[512];
	int from, to;
	from = 0;
	to = 0;
	
	char **argv2 = malloc((argc+1) * sizeof(char*));
	for(int i=0; i<argc+1; i++)
		argv2[i] = argv[i+1];
	argv2[argc] = 0;
	
	while(1) {
		char c;
		if(read(0, &c, sizeof(char)) == 0)
			break;
		buf[to++] = c;
		
		if(c == '\n') {
			buf[to-1] = '\0';
			argv2[argc-1] = buf + from;
			
			int pid = fork();
			if(pid == 0) {
				exec(argv2[0], argv2);
			}
			
			else
				wait((int*) 0);
			
			from = to;
		}
	}
	
	exit(0);
}
