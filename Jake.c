

while(next_time > 0){
    

    /*if we can finish our quantum by the time the next task comes in,
    and we can finish executing the entire job before the next task comes in */

    if(RdyQ->front->j->quantum_left <= next_time && RdyQ->front-j->run_time <= RdyQ->front->j->quantum_left){
        
        next_time -= RdyQ->front->j->run_time; 
        //release resources
        available_memory += RdyQ->front->j->memory_needed; 
        available_devices+ += RdyQ->front->j->devices_allocated;
        job_released = true; //global?
        //move the job to the complete Queue
        enqueue(completeQ,dequeue(RdyQ));
       
    }
    /*if we can finish the quantum before the next task comes in
    but our job won't finish executing in one quantum*/

    else if(RdyQ->front->j->quantum_left <= next_time && RdyQ->front->j->run_time > RdyQ->front->j->quantum_left){
        next_time -= rdyQ->front->j->quantum_left
        RdyQ->front->j->run_time -= RdyQ->front->j->quantum_left;
        //reset the quantum time
        RdyQ->front->j->quantum_left = quantum_time;
        //pop of the queue and move it to the back of the line.
        enqueue(RdyQ,dequeue(RdyQ)); 
    }
    
    /*quantum won't be finished by the time the next task comes in
    but our job will finish within this quantum*/
    else if(RdyQ->front->j->quantum_left > next_time && RdyQ->front->j->run_time <= RdyQ->front->j->quantum_left){

        RdyQ->front->j->run_time -= RdyQ->front->j->next_time;
        RdyQ->front->j->quantum_left -= next_time;
        next_time = 0;
       
       
       
    }
    
    /*the quantum won't be finished by the time the next task comes in 
    also our job won't be done executing by the time the quantum eventually finishes*/
    else if(RdyQ->front->j->quantum_left > next_time && RdyQ->front->j->run_time > RdyQ->front->j->quantum_left){

        RdyQ->front->j->run_time -= RdyQ->front->j->next_time;
        RdyQ->front->j->quantum_left -= next_time;
        next_time = 0;
    }
}

if(job_released){

    
            while(available_memory >= holdQ1->front->j->memory_needed && available_devices >= holdQ1->front->max_device &&
                holdQ1->front->j!=NULL){
            enqueue(RdyQ,dequeue(Hold1Q));
            }

    else{
            while(available_memory >= holdQ2->front->j->memory_needed && available_devices >= holdQ2->front->max_device &&
                holdQ2->front->j!=NULL){
            enqueue(RdyQ,dequeue(Hold2Q));
            }
        }
        job_released = false;
    }