//Jacob McConomy
//Austin Abbruzzesi

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define STRING_SIZE 1000000

int curr_time;
int total_memory;
int available_memory;
int total_devices;
int available_devices;
int quantum_time;
int next_time; // the time between now, and when the next thing arrives
int job_released = 0;
int final_json = 0;


char buffer[STRING_SIZE];

typedef struct{
    int job_num;
    int memory_needed;
    int max_device;
    int runtime_left;
    int priority;
    int quantum_left;
    int devices_allocated;
    int arrival_time;
    int completion_time;
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
char * print_queue(Queue * q, char * buffer){
    int offset = 0;
    struct Node * curr = q->front;
    offset+=snprintf(buffer+offset,STRING_SIZE-offset,"[");
    while(curr != NULL){
       // printf("here\n");
        if(curr->next!= NULL){
            offset += snprintf(buffer+offset,STRING_SIZE-offset,"%d,",curr->j->job_num);
           // printf("here: %d\n",curr->next->j->job_num);
        }else{
            offset += snprintf(buffer+offset,STRING_SIZE-offset,"%d",curr->j->job_num);
        }
       curr = curr->next;
    }
    offset += snprintf(buffer+offset,STRING_SIZE-offset,"]");
    //printf("here too\n");
    return buffer;
}

Queue * create_queue(){
    Queue * q = (Queue*)malloc(sizeof(Queue));
    return q;
}

void sortedInsert(struct Node** head_ref, struct Node* new_node)
{
    struct Node* current;
    struct Node* temp;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->j->runtime_left <= new_node->j->runtime_left)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = *head_ref;
        while (current->next!=NULL &&
               current->next->j->runtime_left > new_node->j->runtime_left)
        {
            current = current->next;
        }
        
        new_node->next = current->next;
        current->next = new_node;
    }
}
void enqueueH1(Queue * q, Job * j){
    struct Node * temp = create_node();
    temp->j = j;
    
    if(q->front == NULL){
        q->front = q->rear = temp;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->rear->next = NULL;

     struct Node *sorted = NULL;
     struct Node *current = (q->front);
     while (current != NULL)

     {
         // Store next for next iteration
         struct Node *next = current->next;
  
         // insert current in sorted linked list
         sortedInsert(&sorted, current);
  
         // Update current
         current = next;
     }
  
     // Update head_ref to point to sorted linked list
     (q->front) = sorted;
 
     
    
    return;

}

void enqueue(Queue * q, Job * j){
    // printf("before enqueue: %s\n", print_queue(q,buffer));
     struct Node * temp = create_node();
     temp->j = j;
     
     if(q->front == NULL){
         q->front = q->rear = temp;
     }
     q->rear->next = temp;
     q->rear = temp;
     q->rear->next = NULL;
     //printf("after enqueue: %s\n", print_queue(q,buffer));
   
 
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

void print_array(int * arr,int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d ",arr[i]);

    }
    printf("\n");
}
char * print_jobs(Queue * q, char * buffer){
    int offset = 0;
    struct Node * curr = q->front;
    
    offset+=snprintf(buffer+offset,STRING_SIZE-offset,"[");
    if(!final_json){
        while(curr != NULL){
        // printf("here\n");
            if(curr->next!= NULL){
                offset += snprintf(buffer+offset,STRING_SIZE-offset,"{\"arrival_time\": %d,\"devices_allocated\": %d,\"id\":%d,\"remaining_time\":%d},",
                curr->j->arrival_time,curr->j->devices_allocated,curr->j->job_num,curr->j->runtime_left);
            // printf("here: %d\n",curr->next->j->job_num);
            }else{
                offset += snprintf(buffer+offset,STRING_SIZE-offset,"{\"arrival_time\": %d,\"devices_allocated\": %d,\"id\":%d,\"remaining_time\":%d}",
                curr->j->arrival_time,curr->j->devices_allocated,curr->j->job_num,curr->j->runtime_left);
            }
        curr = curr->next;
        }
    }else{
        while(curr != NULL){
        // printf("here\n");
            if(curr->next!= NULL){
                offset += snprintf(buffer+offset,STRING_SIZE-offset,"{\"arrival_time\": %d,\"id\":%d,\"remaining_time\":%d,\"completion_time\":%d},",
                curr->j->arrival_time,curr->j->job_num,curr->j->runtime_left,curr->j->completion_time);
            // printf("here: %d\n",curr->next->j->job_num);
            }else{
               offset += snprintf(buffer+offset,STRING_SIZE-offset,"{\"arrival_time\": %d,\"id\":%d,\"remaining_time\":%d,\"completion_time\":%d}",
                curr->j->arrival_time,curr->j->job_num,curr->j->runtime_left,curr->j->completion_time);
            }
            curr = curr->next;
        }

    }
    offset += snprintf(buffer+offset,STRING_SIZE-offset,"]");
    //printf("here too\n");
    return buffer;


}
int get_num(char * string){
    int i; 
    for(i = 0; i<strlen(string); i++){
        if (isdigit(string[i])){
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
void generateJSON(Queue * hold_q1, Queue * hold_q2, Queue * rdy_q, Queue * waitq, Queue * complete_q, Queue * all_jobs){
    char filename[STRING_SIZE];
    snprintf(filename, STRING_SIZE,"D%d.json",curr_time);
    FILE * file;
    file = fopen(filename,"w");
    char line[STRING_SIZE];
    fprintf(file,"{");
    fprintf(file,"\"readyq\": %s,",print_queue(rdy_q,line));
    fprintf(file,"\"current_time\": %d,",curr_time);
    fprintf(file,"\"total_memory\": %d,",total_memory);
    fprintf(file,"\"available_memory\": %d,",available_memory);
    fprintf(file,"\"total_devices\": %d,",total_devices);
    if(!final_json && rdy_q->front != NULL){
        fprintf(file,"\"running\": %d,",rdy_q->front->j->job_num);
    }
    fprintf(file,"\"submitq\": [],");
    fprintf(file,"\"holdq2\": %s,",print_queue(hold_q2,line));
    fprintf(file,"\"job\": %s,",print_jobs(all_jobs,line));
    fprintf(file,"\"holdq1\": %s,",print_queue(hold_q1,line));
    fprintf(file,"\"available_devices\": %d,",available_devices);
    fprintf(file,"\"quantum\": %d,",quantum_time);
    fprintf(file,"\"completeq\": %s,",print_queue(complete_q,line));
    fprintf(file,"\"waitq\": %s",print_queue(waitq,line));
    fprintf(file,"}");

    
}
int main(int argc, char ** argv){

    Queue * submit_q = create_queue();
    Queue * hold_q1 = create_queue();
    Queue * hold_q2 = create_queue();
    Queue * rdy_q = create_queue();
    Queue * waitq = create_queue();
    Queue * complete_q = create_queue();

    Queue * all_jobs = create_queue();

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
                printf("C\n");
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
                if(attributes[2]<total_memory && attributes[3]<total_devices){ //ONLY MAKE A JOB IF THERE ARE ENOUGH TOTAL RESOURCES
                    Job * j = create_job();
                    j->job_num = attributes[1];
                    j->memory_needed = attributes[2];
                    j->max_device = attributes[3];
                    j->runtime_left = attributes[4];
                    j->priority = attributes[5];
                    j->devices_allocated = 0;
                    j->arrival_time = attributes[0];
                    enqueue(all_jobs,j);
                    if(j->memory_needed > available_memory && j->priority == 1){
                        enqueueH1(hold_q1,j);
                    }
                    else if(j->memory_needed > available_memory && j->priority == 2){
                        enqueue(hold_q2,j);
                    }
                    else if(j->memory_needed < available_memory){
                        enqueue(rdy_q,j);   //add to the ready queue
                        available_memory -= j->memory_needed; //allocate memory
                    }
                }else{printf("job rejected\n");
                    }

            }
            else if(line[0] == 'Q'){                        //TODO
                attributes = (int*)malloc(sizeof(int)*3);
                return_args(line,attributes);
                available_devices -= attributes[2];
                if(rdy_q->front != NULL && rdy_q->front->j->job_num == attributes[1]){
                    rdy_q->front->j->devices_allocated += attributes[2];
                }
             
            }
            else if(line[0] == 'L'){
                attributes = (int*)malloc(sizeof(int)*3);
                return_args(line,attributes);
                available_devices += attributes[2];
                if(rdy_q->front != NULL && rdy_q->front->j->job_num == attributes[1]){
                    rdy_q->front->j->devices_allocated -= attributes[2];
                }
            }
            else if(line[0] == 'D'){
                attributes = (int*)malloc(sizeof(int));
                return_args(line,attributes);
                if(attributes[0] == 9999){
                    final_json = 1;
                } 
                generateJSON(hold_q1,hold_q2,rdy_q,waitq,complete_q,all_jobs);
                
            }else{
                printf("error. invalid line in file\n");
            }
            free(attributes);
        while(rdy_q->front!= NULL && next_time > 0 ){
            while(rdy_q->front!=NULL && available_devices < rdy_q->front->j->max_device){
                    
                    enqueue(waitq,dequeue(rdy_q)->j);
            }
            
            if(job_released){
                while(hold_q1->front != NULL && available_memory >= hold_q1->front->j->memory_needed && available_devices >= hold_q1->front->j->max_device){
                    available_memory -= hold_q1->front->j->memory_needed;
                    enqueue(rdy_q,dequeue(hold_q1)->j);

                }

                while(hold_q2->front != NULL && available_memory >= hold_q2->front->j->memory_needed && available_devices >= hold_q2->front->j->max_device){
                    available_memory -= hold_q2->front->j->memory_needed;
                    enqueue(rdy_q,dequeue(hold_q2)->j);
                }

                while(waitq->front != NULL && available_devices >= waitq->front->j->max_device){

                    enqueue(rdy_q,dequeue(waitq)->j);
                }
               
                job_released = 0;
            }
            
        /*if we can finish our quantum by the time the next task comes in,
        and we can finish executing the entire job before the next task comes in */
            if(rdy_q->front != NULL && rdy_q->front->j->quantum_left <= next_time && rdy_q->front->j->runtime_left <= rdy_q->front->j->quantum_left){
                next_time -= rdy_q->front->j->runtime_left;
                
                available_memory += rdy_q->front->j->memory_needed;
                rdy_q->front->j->memory_needed = 0;
                available_devices += rdy_q->front->j->devices_allocated;
                job_released = 1;
                
                //printf("enqueuing job %d in complete q from rdy_q\n", rdy_q->front->j->job_num);
                rdy_q->front->j->runtime_left = 0;
                rdy_q->front->j->completion_time = get_time(line2) - next_time;
                enqueue(complete_q,dequeue(rdy_q)->j);

                
            }
            /*if we can finish the quantum before the next task comes in
             but our job won't finish executing in one quantum*/
            else if(rdy_q->front != NULL && rdy_q->front->j->quantum_left <= next_time && rdy_q->front->j->runtime_left > rdy_q->front->j->quantum_left){
                next_time -= rdy_q->front->j->quantum_left;
                rdy_q->front->j->runtime_left -= quantum_time;
                rdy_q->front->j->quantum_left = quantum_time;
                enqueue(rdy_q,dequeue(rdy_q)->j);
                 
            }
           
            else if( rdy_q->front!= NULL && rdy_q->front->j->quantum_left > next_time){
                rdy_q->front->j->runtime_left -= next_time;
                rdy_q->front->j->quantum_left -= next_time;
                next_time = 0;
            }

        }
        char buffer[STRING_SIZE];
        printf("------------------------------------\n");
        printf("time: %d\n",curr_time);
        printf("total memory:%d\n",total_memory);
        printf("total devices:%d\n",total_devices);
        printf("available memory:%d\n", available_memory);
        printf("available devices:%d\n",available_devices);
        printf("ready_queue: %s\n", print_queue(rdy_q,buffer));
        printf("hq1: %s\n",print_queue(hold_q1,buffer));
        printf("hq2: %s\n",print_queue(hold_q2,buffer));
        printf("wait_q: %s\n", print_queue(waitq,buffer));
        printf("complete_q: %s\n",print_queue(complete_q,buffer));
    }
    free(line);
    free(line2);
    free(rdy_q);
    free(wait_q);
    free(complete_q);
    free(hold_q1);
    free(hold_q2);
    
        
        
    }


    
}



