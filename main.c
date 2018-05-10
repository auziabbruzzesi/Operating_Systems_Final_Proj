#include<stdio.h>
#include<stdlib.h>
#define STRING_SIZE 1024

typedef struct{
  //make job
}Job;

typedef struct {
  //make queue
}Queue;

typedef struct{
  //make node
}Node;

//EnqueueSJF
//EnqueueFIFO
//Dequeue

//makeJob

//makeNode


//Banker's algorithm

void parse(File * file){
  //while file newline stuff

  //if config line:
    //config(params);
  //if job line:
    //new_job(params)
  //if device request
    //device_request(params)
  //if release device request
    //device_release(params)
  //if system status
    //system_status()
  
}

int main(int argc, char ** argv){
  char filename[STRING_SIZE];
  FILE *file;
  file = fopen(filename, "r");
  size_t buffer = STRING_SIZE;
  char * line = (char*)malloc(STRING_SIZE*sizeof(char));
  
  
  getline(&line,&buffer,file);
  printf("enter config. file name: \n");
  scanf("%s", filename);

  printf("%s",line);

  //TODO write parse function to parse the text file

}