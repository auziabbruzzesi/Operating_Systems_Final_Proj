
//NOTE: we still need to implement a way to get next_time. we can do this using the Line2 and a helper function that just returns the time.

while(next_time > 0){

//NOTE: next_time is the amount of time until the next_time, it's not the actual next time
//if we can finish our quantum by the time the next task comes in,
//and we can finish executing the entire job before the next task comes in
if(RdyQ->front->j->quantum_left <= next_time && RdyQ->front-j->run_time <= RdyQ->front->j->quantum_left){
    next_time -= RdyQ->front->j->run_time; //subtract the run time from next time
    available_memory += RdyQ->front->j->memory_needed; //give back resources
    available_devices+ += RdyQ->front->j->devices_allocated;
    enqueue(completeQ,dequeue(RdyQ));//move the job to the complete Queue
}
//if we can finish the quantum before the next task comes in
//but our job won't finish executing in one quantum
else if(RdyQ->front->j->quantum_left <= next_time && RdyQ->front->j->run_time > RdyQ->front->j->quantum_left){
    next_time -= rdyQ->front->j->quantum_left //completing an entire quantum. subtract that from next time
    RdyQ->front->j->run_time -= RdyQ->front->j->quantum_left;
    RdyQ->front->j->quantum_left = quantum_time//quantum_time is a global variable
    enqueue(RdyQ,dequeue(RdyQ)); //pop of the queue and move it to the back of the line.
}
}