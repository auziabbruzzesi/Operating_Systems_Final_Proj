//Jacob McConomy

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

typedef struct Node {
  Job data;           /*  --> Changes done here */
  struct Node *pNext; /* Reference to the next node address */
} NODE;


void addJob(struct Node** head_ref, int start_time_in, int job_num_in, 
            int priority_in, int memory_req_in, int device_req_in)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
 
    struct Node *last = *head_ref;  /* used in step 5*/
 
    /* 2. put in the data  */
    new_node->data.start_time  = start_time_in;
    new_node->data.job_num = job_num_in;
    new_node->data.priority = priority_in;
    new_node->data.memory_req = memory_req_in;
    new_node->data.device_req = device_req_in;
 
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->pNext = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
 
    /* 5. Else traverse till the last node */
    while (last->pNext != NULL)
        last = last->pNext;
 
    /* 6. Change the next of last node */
    last->pNext = new_node;
    return;
}
 
// This function prints contents of linked list starting from head
void printQueue(struct Node *node)
{
 
  while (node != NULL)
  {
     printf("Job number %d has start time: %d \npriority: %d \nmempry_req: %d \ndevice_req: %d \n\n", node->data.job_num, 
            node->data.start_time, node->data.priority, node->data.memory_req, node->data.device_req);
     node = node->pNext;
  }
}


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
  /*
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
  */

  /*Test Queue!
  First make empty queue..*/
  struct Node* head = NULL;
  /*Add Job!*/
  addJob(&head, 10, 1, 3, 500, 200);
  /*And Another!*/
  addJob(&head, 10, 2, 8, 400, 100);
  /* Print Jobs*/
  printQueue(head);






  }
  
  
  
  
  

  

  //TODO write parse function to parse the text file

