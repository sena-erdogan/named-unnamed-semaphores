#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define READ_FLAGS O_RDONLY

char INGREDIENTS[1024];
char SHNAME[20] = "/mssgsaddafd";

char* NAME;

int isMilk = 0;
int isFlour = 0;
int isWalnut = 0;
int isSugar = 0;

sem_t *milk;
sem_t *flour;
sem_t *walnut;
sem_t *sugar;

sem_t *milk2;
sem_t *flour2;
sem_t *walnut2;
sem_t *sugar2;

sem_t *chef1;
sem_t *chef2;
sem_t *chef3;
sem_t *chef4;
sem_t *chef5;
sem_t *chef6;

sem_t *wsaler; /*wholesaler sem*/

sem_t *m; /*mutex*/

void ingred(char a){
	if(a == 'W')		printf("Walnuts");
	else if(a == 'F')	printf("Flour");
	else if(a == 'M')	printf("Milk");
	else if(a == 'S')	printf("Sugar");

}

int wholesaler(){

	int mem = 0, desserts = 0, temp = 0;
	/*int i;*/
	
	chef1 = sem_open("/chessdsgaagddsd1", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (chef1 == SEM_FAILED) {
        	perror("chef1");
        	exit(1);
   	}
	chef2 = sem_open("/schssdgagdsdade2", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (chef2 == SEM_FAILED) {
        	perror("chef2");
        	exit(1);
   	}
	chef3 = sem_open("/chfsdggaadsadde3", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (chef3 == SEM_FAILED) {
        	perror("chef3");
        	exit(1);
   	}
	chef4 = sem_open("/chsdfgsgaadsadde4", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (chef4 == SEM_FAILED) {
        	perror("chef4");
        	exit(1);
   	}
	chef5 = sem_open("/chsedsdgfgdsaad5", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (chef5 == SEM_FAILED) {
        	perror("chef5");
        	exit(1);
   	}
	chef6 = sem_open("/chesgaddgdsag6", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (chef6 == SEM_FAILED) {
        	perror("chef6");
        	exit(1);
   	}
	
	int memfd = shm_open(SHNAME, O_CREAT | O_EXCL | O_RDWR, 0600);
	
	if(memfd < 0){
		perror("shm_open() error\n");
		return EXIT_FAILURE;
	}
	
	if(ftruncate(memfd, 2) == -1)	perror("ftruncate");
	
	char *data = (char*)mmap(0, 2, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0);
	
	while(mem != strlen(INGREDIENTS)){
		memcpy(data, INGREDIENTS + mem, 2);
		mem += 2;
		
		/*for(i=0; i<6; i++){*/
			if(fork() == 0){
				memfd = shm_open(SHNAME, O_RDONLY, 0666);
		
				if(memfd < 0){
					perror("shm_open() error\n");
					return EXIT_FAILURE;
				}
				
				data = (char*)mmap(0, 2, PROT_READ, MAP_SHARED, memfd, 0);
				
				printf("the wholesaler (pid %d) delivers ", getppid());
				ingred(data[0]);
				printf(" and ");
				ingred(data[1]);
				printf("\n");
				
				printf("the wholesaler (pid %d) is waiting for the dessert\n", getppid());
				
				if((data[0] == 'W' && data[1] == 'S') || (data[0] == 'S' && data[1] == 'W')){ 
					printf("char array elements are: %c and %c\n", data[0], data[1]);
					printf("chef1 has (pid %d) taken the ", getpid());
					ingred(data[0]);
					printf("\n");
					printf("chef1 has (pid %d) taken the ", getpid());
					ingred(data[1]);
					printf("\n");
					sem_post(chef1);
					printf("chef1 has (pid %d) is preparing the dessert\n", getpid());
					printf("the wholesaler (pid %d) has obtained the dessert and left\n", getppid());
				
				}else if((data[0] == 'F' && data[1] == 'W') || (data[0] == 'W' && data[1] == 'F')){ 
					printf("char array elements are: %c and %c\n", data[0], data[1]);
					printf("chef2 has (pid %d) taken the ", getpid());
					ingred(data[0]);
					printf("\n");
					printf("chef2 has (pid %d) taken the ", getpid());
					ingred(data[1]);
					printf("\n");
					sem_post(chef2);
					printf("chef2 has (pid %d) is preparing the dessert\n", getpid());
					printf("the wholesaler (pid %d) has obtained the dessert and left\n", getppid());
				
				}else if((data[0] == 'S' && data[1] == 'F') || (data[0] == 'F' && data[1] == 'S')){ 
					printf("char array elements are: %c and %c\n", data[0], data[1]);
					printf("chef3 has (pid %d) taken the ", getpid());
					ingred(data[0]);
					printf("\n");
					printf("chef3 has (pid %d) taken the ", getpid());
					ingred(data[1]);
					printf("\n");
					sem_post(chef3);
					printf("chef3 has (pid %d) is preparing the dessert\n", getpid());
					printf("the wholesaler (pid %d) has obtained the dessert and left\n", getppid());
				
				}else if((data[0] == 'M' && data[1] == 'F') || (data[0] == 'F' && data[1] == 'M')){
					printf("char array elements are: %c and %c\n", data[0], data[1]);
					printf("chef4 has (pid %d) taken the ", getpid());
					ingred(data[0]);
					printf("\n");
					printf("chef4 has (pid %d) taken the ", getpid());
					ingred(data[1]);
					printf("\n");
					sem_post(chef4);
					printf("chef4 has (pid %d) is preparing the dessert\n", getpid());
					printf("the wholesaler (pid %d) has obtained the dessert and left\n", getppid());
				
				}else if((data[0] == 'M' && data[1] == 'W') || (data[0] == 'W' && data[1] == 'M')){
					printf("char array elements are: %c and %c\n", data[0], data[1]);
					printf("chef5 has (pid %d) taken the ", getpid());
					ingred(data[0]);
					printf("\n");
					printf("chef5 has (pid %d) taken the ", getpid());
					ingred(data[1]);
					printf("\n");
					sem_post(chef5);
					printf("chef5 has (pid %d) is preparing the dessert\n", getpid());
					printf("the wholesaler (pid %d) has obtained the dessert and left\n", getppid());
				
				}else if((data[0] == 'S' && data[1] == 'M') || (data[0] == 'M' && data[1] == 'S')){
					printf("char array elements are: %c and %c\n", data[0], data[1]);
					printf("chef6 has (pid %d) taken the ", getpid());
					ingred(data[0]);
					printf("\n");
					printf("chef6 has (pid %d) taken the ", getpid());
					ingred(data[1]);
					printf("\n");
					sem_post(chef6);
					printf("chef6 has (pid %d) is preparing the dessert\n", getpid());
					printf("the wholesaler (pid %d) has obtained the dessert and left\n", getppid());
				
				}
				exit(0);
			}
		/*}*/
		
		/*for(i=0; i<6; i++)*/	wait(NULL);
	}
	
	sem_getvalue(chef1, &temp);
	desserts += temp;
	printf("chef1 has prepared %d desserts\n", temp);
	sem_getvalue(chef2, &temp);
	desserts += temp;
	printf("chef2 has prepared %d desserts\n", temp);
	sem_getvalue(chef3, &temp);
	desserts += temp;
	printf("chef3 has prepared %d desserts\n", temp);
	sem_getvalue(chef4, &temp);
	desserts += temp;
	printf("chef4 has prepared %d desserts\n", temp);
	sem_getvalue(chef5, &temp);
	desserts += temp;
	printf("chef5 has prepared %d desserts\n", temp);
	sem_getvalue(chef6, &temp);
	desserts += temp;
	printf("chef6 has prepared %d desserts\n", temp);
	
	printf("the wholesaler (pid %d) is done (total desserts: %d)\n", getpid(), desserts);
	
	munmap(data, 2);
	close(memfd);
	shm_unlink(SHNAME);

	return EXIT_SUCCESS;
	
}

int main(int argc, char *argv[]){

	int i;
	int bytesread, fd;
	char buf[2];
	
	if(argc != 5){
		perror("\nUsage: Baker's simulation\nformat: ./hw3named -i inputFilePath -n name\n");
		return 1;
	}
	
	for(i=1; i<=4; i+=2){
		if(strcmp(argv[i], "-i") == 0){
			if((fd = open(argv[i+1], READ_FLAGS)) == -1){
				perror("Failed to open input file\n");
				return 1;
			}
		}else if(strcmp(argv[i], "-n") == 0){
			NAME = (char*)malloc(strlen(argv[i+1]));
			strcpy(NAME, argv[i+1]);
		}else{
			perror("\nInvalid command\nformat: ./hw3named -i inputFilePath -n name\n");
			return 1;
		}
	}
	
	for( ; ; ){
		while(((bytesread = read(fd, buf, 2)) == -1) && (errno == EINTR));
		
		if(bytesread <= 0)	break;
		
		strcat(INGREDIENTS, buf);
		
		while(((bytesread = read(fd, buf, 1)) == -1) && (errno == EINTR));
		
		if(bytesread <= 0)	break;
	}
	
	wholesaler();
	
	if(close(fd) == -1){
		perror("Failed to close input file\n");
		return 1;
	}
	
	free(NAME);
	
	return 0;
}
