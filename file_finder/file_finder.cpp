#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <errno.h>

#define MAX_SIZE_OF_CURRENT_DIR_NAME 1000

using namespace std;

void make_path(char *path, char *current_dir, char *d_name, struct stat *buf);
void find_file(char *current_dir, int depth, char *needed_file);
 
int main(int argc, char * argv[]) {
	char a[MAX_SIZE_OF_CURRENT_DIR_NAME] = {0};
	strcpy(a, "..");
	find_file(a, atoi(argv[1]), argv[2]);
	cout << endl;
}

void find_file(char *current_dir, int depth, char *needed_file) {
	struct dirent * id;
	struct stat buf;
	DIR *dirp = opendir(current_dir);
	if(dirp == NULL) {
		cout << "ERROR IS THERE:" << current_dir << endl;
		perror("dirp");
		exit(25); 
	}	
	while(1) {
		id = readdir(dirp);
		if(id == NULL) {
			break;
		}
		char path[MAX_SIZE_OF_CURRENT_DIR_NAME] = {0};
	//	cout << current_dir << endl;
		make_path(path, current_dir, id->d_name, &buf);
		if(S_ISDIR(buf.st_mode)) {
			if(depth != 0) {
				if(strcmp(id->d_name, ".") == 0 || strcmp(id->d_name, "..") == 0);
				else find_file(path, depth - 1, needed_file);
			}
		}
		else if(strcmp(needed_file, id->d_name) == 0) {
			cout << current_dir << endl;
		}
	}
	closedir(dirp);
}

void make_path(char *path, char *current_dir, char *d_name, struct stat *buf) {
	strcpy(path, current_dir);
	strcat(path, "/");
	strcat(path, d_name);
	stat(path, buf);
}
