#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define STRING_SIZE 1024
int curr_time;
int total_memory;
int available_memory;
int total_devices;
int available_devices;
int quantum_time;
int next_time; // the time between now, and when the next thing arrives

typedef struct{
    int job_num;
    int memory_needed;
    int max_device;
    int runtime_left;
    int priority;
    int quantum_left;
    int devices_allocated;
}Job;
struct Node{
    Job * j;
    struct Node * next;
}Node;
typedef struct{
    struct Node * front;
    struct Node * rear;
}Queue;

Job * create_job(){
    Job * j = (Job*)malloc(sizeof(Job));
    return j;
}
struct Node * create_node(){
    struct Node * n = (struct Node*)malloc(sizeof(struct Node));
    return n;
}

Queue * create_queue(){
    Queue * q = (Queue*)malloc(sizeof(Queue));
    return q;
}

void enqueue(Queue * q, Job * j){
    struct Node * temp = create_node();
    temp->j = j;
    
    if(q->front == NULL){
        q->front = q->rear = temp;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->rear->next = NULL;
    

}

struct Node * dequeue (Queue * q){
    if (q->front == NULL)
       return NULL;
    struct Node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
       q->rear = NULL;
    return temp;
}
void swapNodes(struct Node** head_ref, struct Node* currX,
               struct Node* currY, struct Node* prevY){
  /* Methods for Sorting Linked Lists */
  // function to swap nodes 'currX' and 'currY' in a
  // linked list without swapping data
  // make 'currY' as new head
  *head_ref = currY;

  // adjust links
  prevY->next = currX;

  // Swap next pointers
  struct Node* temp = currY->next;
  currY->next = currX->next;
  currX->next = temp;
}
struct Node* recurSelectionSort(struct Node* head){
  /*Sort queue for SJF */
  // if there is only a single node
  if (head->next == NULL)
  return head;

  // 'min' - pointer to store the node having
  // minimum data value
  struct Node* min = head;

  // 'beforeMin' - pointer to store node previous
  // to 'min' node
  struct Node* beforeMin = NULL;
  struct Node* ptr;

  // traverse the list till the last node
  for (ptr = head; ptr->next != NULL; ptr = ptr->next) {

    // if true, then update 'min' and 'beforeMin'
    if (ptr->next->j->runtime_left < min->j->runtime_left) {
    min = ptr->next;
    beforeMin = ptr;
    }
  }

  // if 'min' and 'head' are not same,
  // swap the head node with the 'min' node
  if (min != head)
   swapNodes(&head, head, min, beforeMin);

  // recursively sort the remaining list
  head->next = recurSelectionSort(head->next);

  return head;
}
void sort(struct Node** head_ref){
  // function to sort the given linked list
  // if list is empty
  if ((*head_ref) == NULL)
  return;

  // sort the list using recursive selection
  // sort technique
  *head_ref = recurSelectionSort(*head_ref);
}

void print_queue(Queue * q){
    struct Node * curr = q->front;
    while(curr != NULL){
        printf("---------------------\n");
        printf("job_num: %d ", curr->j->job_num);
        printf("job_mem: %d ", curr->j->memory_needed);
        printf("job_max_dev: %d ", curr->j->max_device);
        printf("run_time_left: %d ", curr->j->runtime_left);
        printf("job_priority: %d ", curr->j->priority);
        printf("\n---------------------\n");
        curr = curr->next;

    }
}

void print_array(int * arr,int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d ",arr[i]);

    }
    printf("\n");
}
int get_num(char * string){
    int i; 
    for(i = 0; i<strlen(string); i++){
        if isdigit(string[i]){
            //printf("digit: %d\n",atoi(&string[i]));
            return atoi(&string[i]);
        }
    }
}
int get_time(char * string){
    char * time;
    char * new_string = (char*)malloc(STRING_SIZE);
    strcpy(new_string,string);
    time = strtok(new_string,"C A Q L D ");
    return atoi(time);
    
    
}
void return_args (char * line,int * args){
    char * params;
    int * arguments;

    params = strtok(line,"C A Q L D "); //strip type name off of it
    //printf("args line: %s\n",params);
    int i = 0;
    while(params != NULL){
        //printf("args line: %s\n",params);
        //printf("digit %d\n", get_num(params));
        args[i] = get_num(params);
        i+=1;
        params = strtok(NULL," ");
        
    }

}
int main(int argc, char ** argv){

    Queue * submit_q = create_queue();
    Queue * hold_q1 = create_queue();
    Queue * hold_q2 = create_queue();
    Queue * rdy_q = create_queue();
    Queue * waitq = create_queue();
    Queue * complete_q = create_queue();

    char filename[STRING_SIZE];
    printf("enter config. file name: \n");
    scanf("%s", filename);
    FILE * file;
    FILE * file2;
    file = fopen(filename, "r");
    file2 = fopen(filename, "r");
    size_t buffer = STRING_SIZE;
    size_t buffer2 = STRING_SIZE;
    char * line = (char*)malloc(STRING_SIZE*sizeof(char));
    char * line2 = (char*)malloc(STRING_SIZE*sizeof(char));
    if(file){
        getline(&line2,&buffer2,file2);
        while(getline(&line,&buffer,file)>=0){      //GET NEXT TASK
            getline(&line2,&buffer2,file2);         //GET TASK AFTER
            curr_time = get_time(line);             //START TIME OF CURRENT TASK
            next_time = get_time(line2) - curr_time; //TIME BETWEEN THIS TASK AND THE NEXT
            int * attributes;
            if(line[0] == 'C'){                     //CONFIG JOB
                attributes = (int*)malloc(sizeof(int)*4);
                return_args(line,attributes);
                curr_time = attributes[0];
                total_memory = available_memory = attributes[1];
                total_devices = available_devices = attributes[2];
                quantum_time = attributes[3];
            }
            else if (line[0] == 'A'){                   //JOB ARRIVAL
                attributes = (int*)malloc(sizeof(int)*5);
                return_args(line,attributes);
                
                if(attributes[2]<total_memory || attributes[3]<total_devices){ //ONLY MAKE A JOB IF THERE ARE ENOUGH TOTAL RESOURCES
                    Job * j = create_job();
                    j->job_num = attributes[1];
                    j->memory_needed = attributes[2];
                    j->max_device = attributes[3];
                    j->runtime_left = attributes[4];
                    j->priority = attributes[5];

                    if(j->memory_needed > available_memory && j->priority == 1){
                        //printf("adding to hq1\n");
                        enqueue(hold_q1,j);
                        sort(&(hold_q1->front));                //Sorts SJF
                    }
                    else if(j->memory_needed > available_memory && j->priority == 2){
                        //printf("adding to hq2\n");
                        enqueue(hold_q2,j);
                    }
                    else if(j->memory_needed < available_memory){
                        //printf("adding to ready\n");
                        enqueue(rdy_q,j);   //add to the ready queue
                        available_memory -= j->memory_needed; //allocate memory
                    }
                }else{printf("job rejected\n");
                    }

            }
            else if(line[0] == 'Q'){                        //TODO
                attributes = (int*)malloc(sizeof(int)*3);
                return_args(line,attributes);
                //print_array(attributes,3);
            }
            else if(line[0] == 'L'){                        //TODO   
                attributes = (int*)malloc(sizeof(int)*3);
                return_args(line,attributes);

                //print_array(attributes,3);
            }
            else if(line[0] == 'D'){
                attributes = (int*)malloc(sizeof(int));
                return_args(line,attributes);
                //print_array(attributes,1);
            }else{
                printf("error. invalid line in file\n");
            }


            //NEXT WE NEED TO GO TO THE FRONT OF THE READY QUEUE AND IMPLEMENT THAT PART. SEE THE PSUEDO_CODE FILE!!!
        
    // printf("--------------------statistics-------------------------\n");
    // printf("curr_time: %d\navailable_memory: %d\navailable_devices: %d\nnext_time: %d\n", curr_time,available_memory,available_devices,next_time);
    printf("/////////////////////////////////////////////\n");
    printf("hold_q1: \n");
    printf("/////////////////////////////////////////////\n");
    print_queue(hold_q1); 
   // printf("hold_q1: \n");
    // print_queue(hold_q2); 
    // printf("readyq: \n");
    // print_queue(rdy_q); 
    // printf("wait: \n");
    // print_queue(waitq); 
    }
        
        
    }


    
}



