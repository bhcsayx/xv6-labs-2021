#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int strncmp(char *a, char *b, int n)
{
  for (int i = 0; i < n; ++i)
  {
    if (a[i] < b[i])
      return -1;
    if (a[i] > b[i])
      return 1;
  }
  return 0;
}

int contain(char *target, char *pattern) {
	int target_size = strlen(target);
	int pattern_size = strlen(pattern);
	for(int i=0; i<=target_size-pattern_size; i++) {
		if(strncmp(target+i, pattern, pattern_size) == 0) {
			return 1;
		}
	}
	return 0;
}

void find(char *pathname, char *filename) {
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(pathname, 0)) < 0){
	    fprintf(2, "ls: cannot open %s\n", pathname);
	    return;
	}

	if(fstat(fd, &st) < 0){
	    fprintf(2, "ls: cannot stat %s\n", pathname);
	    close(fd);
	    return;
	}
	
	switch(st.type){
		case T_FILE: {
			if(strcmp(pathname, filename) == 0) {
				printf("%s\n", pathname);
			}
			break;
		}
		case T_DIR: {
		    strcpy(buf, pathname);
		    p = buf+strlen(buf);
		    *p++ = '/';
		    while(read(fd, &de, sizeof(de)) == sizeof(de)){
		    	if(de.inum == 0 || 0 == strcmp(de.name, ".") || 0 == strcmp(de.name, ".."))
		    	    continue;
		    	memmove(p, de.name, DIRSIZ);
		    	p[DIRSIZ] = 0;
		    	if(stat(buf, &st) < 0){
        			printf("ls: cannot stat %s\n", buf);
		    	    continue;
		    	}
		    	switch(st.type){
					case T_FILE: {
		    			if(contain(buf, filename))
		    				printf("%s\n", buf);
		    			break;
		    		}
		    		case T_DIR: {
		    			find(buf, filename);
		    			break;
		    		}
		    	}
			}
			break;
		}
	}
	close(fd);
}

int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("too few arguments\n");
		exit(1);
	}
	find(argv[1], argv[2]);
	exit(0);
}
	
