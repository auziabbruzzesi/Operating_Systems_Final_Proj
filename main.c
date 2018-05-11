#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRING_SIZE 1024
//change comment
typedef struct{
  int start_time;
  int job_num;
  int priority;
  int memory_req;
  int device_req;
   
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
  int D;
  switch(line[0]){
    case 'C':
      //printf("this is a config line!\n");
      params = strtok(line,"C ");
      //printf("params: %s\n", params);
      start_time = atoi(params);
      params = strtok(NULL,"C M= S= Q= ");
      M = atoi(params);
      params = strtok(NULL,"C M= S= Q= ");
      S = atoi(params);
      params = strtok(NULL,"C M= S= Q= ");
      Q = atoi(params);
      params = strtok(NULL,"C M= S= Q= ");
      printf("Start time = %d, M = %d, S = %d, Q = %d\n", start_time, M, S, Q);
      break;
    case 'A':
      //printf("this is a job arrival\n");
      params = strtok(line,"A ");
      start_time = atoi(params);
      params = strtok(NULL,"A J= M= S= R= P= ");
      J = atoi(params);
      params = strtok(NULL,"A J= M= S= R= P= ");
      M = atoi(params);
      params = strtok(NULL,"A J= M= S= R= P= ");
      S = atoi(params);
      params = strtok(NULL,"A J= M= S= R= P= ");
      R = atoi(params);
      params = strtok(NULL,"A J= M= S= R= P= ");
      P = atoi(params);
      printf("job arrival start time = %d, J = %d, M = %d, S = %d, R = %d, P = %d\n",start_time, J, M, S, R, P);
      break;
    case 'Q':
      //printf("this is a device request\n");
      params = strtok(line,"Q ");
      start_time = atoi(params);
      params = strtok(NULL,"Q J= D= ");
      J = atoi(params);
      params = strtok(NULL,"Q J= D= ");
      D = atoi(params);
      printf("Device request start time = %d, J = %d, D = %d\n",start_time, J, D);
      break;
    case 'L':
      //printf("This is a device release\n");
      params = strtok(line,"L ");
      start_time = atoi(params);
      params = strtok(NULL,"L J= D= ");
      J = atoi(params);
      params = strtok(NULL,"L J= D= ");
      D = atoi(params);
      printf("Device release start time = %d, J = %d, D = %d\n",start_time, J, D);
      break;
    case 'D':
      params = strtok(line,"D ");
      start_time = atoi(params);
      printf("system status time %d\n",start_time);
                
      //printf("this is a system status\n");
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