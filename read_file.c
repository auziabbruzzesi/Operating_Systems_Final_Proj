#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define STRING_SIZE 1024
int get_num(char * string){
    int i; 
    for(i = 0; i<strlen(string); i++){
        if isdigit(string[i]){
            //printf("digit: %d\n",atoi(&string[i]));
            return atoi(&string[i]);
        }
    }
}

void print_array(int * arr,int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d ",arr[i]);

    }
    printf("\n");
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
// char *read_next_line(char *buffer, size_t size, FILE *file)
// {

//    if (fgets(buffer, size, file))
//    {
//        return buffer;
//    }
//    // error or EOF
//    if (!feof(file)) return NULL; // error
//    fseek(file, 0, SEEK_SET);
//    return fgets(buffer, size, file);
// }

char * read_next_line(char * line,size_t buffer,FILE * file){
    getline(&line,&buffer,file);
}

int main(int argc, char ** argv){
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
        while(getline(&line,&buffer,file)>=0){
            getline(&line2,&buffer2,file2);
            printf("line: %s", line);
            //printf("line2: %s\n",line2);
            int * attributes;
            if(line[0] == 'C'){
                attributes = (int*)malloc(sizeof(int)*4);
                return_args(line,attributes);
                print_array(attributes,4);
            }
            else if (line[0] == 'A'){
                attributes = (int*)malloc(sizeof(int)*5);
                return_args(line,attributes);
                 print_array(attributes,6);
            }
            else if(line[0] == 'Q'){
                attributes = (int*)malloc(sizeof(int)*3);
                return_args(line,attributes);
                print_array(attributes,3);
            }
            else if(line[0] == 'L'){
                attributes = (int*)malloc(sizeof(int)*3);
                return_args(line,attributes);
                print_array(attributes,3);
            }
            else if(line[0] == 'D'){
                attributes = (int*)malloc(sizeof(int));
                return_args(line,attributes);
                print_array(attributes,1);
            }
            
        
        
        }
    }
}