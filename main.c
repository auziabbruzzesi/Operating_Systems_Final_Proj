#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void config(int start_time, int M, int S, int Q){
  //TODO
}

void parse(char * line){
 // printf("parsing line: %s\n", line);
  
  char * cmd_type;
  const char config = 'C';
  const char job_arrival = 'A';
  const char device_request = 'Q';
  const char device_release = 'L';
  const char system_status = 'D';
  int start_time;
  char * params;
  char * vals;
  //printf("first char: %c\n",line[0]);
  //while file newline stuff
  
  int M;
  int S;
  int Q;
  int J; 
  int R;
  int P;
  switch(line[0]){
    case 'C':
      
      printf("this is a config line!\n");
      params = strtok(line,"C ");
      //printf("params: %s\n", params);
      printf("%s\n",params);
      
      printf("parameter line: %s\n",params);
      start_time = atoi(params);
      params = strtok(params,"C M= S= Q= ");
      M = atoi(params);
      params = strtok(params,"C M= S= Q= ");
      S = atoi(params);
      params = strtok(params,"C M= S= Q= ");
      Q = atoi(params);
      params = strtok(params,"C M= S= Q= ");
      printf("Start time = %d, M = %d, S = %d, Q = %d\n", start_time, M, S, Q);

      
      
      
    case 'A':
      printf("this is a job arrival\n");
    case 'Q':
      printf("this is a device request\n");
    case 'L':
      printf("This is a device release\n");
    case 'D':
      printf("this is a system status\n");
  }

  
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
  printf("enter config. file name: \n");
  scanf("%s", filename);
  FILE *file;
  file = fopen(filename, "r");
  size_t buffer = STRING_SIZE;
  char * line = (char*)malloc(STRING_SIZE*sizeof(char));
  if(file){
    while(getline(&line,&buffer,file)>=0){
      parse(line);

    }







  }
  
  
  
  
  

  

  //TODO write parse function to parse the text file

}