#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NCHAR 64
typedef struct passengers{
    char *name;
    int id;
    char *wanted;
    char *sold;
    int priority;
}Passengers;
typedef struct Queue{
    int *queue,rear,front,size;
}Queue;
typedef struct Stack{
    int *stack, top,size;
}Stack ;
typedef struct Flights{
    char *flight_name;
    int busines_count,economy_count,standard_count;
    Passengers *yolcular;
    Queue *siralar;
    Stack *empty_seats;
    int Readable,toplam_yolcu;
    struct Flights *next;

}Flights;
typedef struct NodeFlights{
    Flights *s;
    struct NodeFlights *next;
}Nodeflights;
typedef struct NodeQueue{
    char *name;
    struct NodeQueue *next;
}Nodequeue;
void pop(Stack *stack){
    if (stack->size!=0) {
        stack->stack = realloc(stack->stack, sizeof(int) * (--stack->size));
    }
}
int addseat_control(char *class, char *adet) {
    int i;
    for (i = 0; i < strlen(adet); ++i) {
        if (!isdigit(adet[i])) {
            return 1;
        }
    }
    if (!strcmp(class, "business") == 0 && !strcmp(class, "economy") == 0 && !strcmp(class, "standard") == 0) {
        return 1;
    }
    return 0;
}
Flights * findFlight(struct Flights *head, char *name) {
    Flights *current;
    current=head;
    while (current!=NULL){
        if(strcmp(current->flight_name,name)==0){
            return current;
        }
        current=current->next;
    }
    return NULL;
}
void push(int value,Stack *stack){

    stack->stack[stack->size++]=value;
    stack->top++;

}
void insert(Flights *fl,Queue *q,int id,int priority){
    int i,j;
    int item=-1;
    if((*q).size==0){
        (*q).queue[0]=id;
    }
    if(priority){
        for (i = 0; i <q->size; ++i) {
            if(fl->yolcular[q->queue[i]].priority){

                item=i;
            }
        }
        if(item==-1){
            for (i = q->size; i >0; --i) {
                q->queue[i]=q->queue[i-1];
            }
            q->queue[0]=id;
        }
        else{
            for (i = q->size; i >item; --i) {
                q->queue[i]=q->queue[i-1];
            }
            q->queue[item+1]=id;
        }
    }
    else {
        q->queue[q->size]=id;

    }

    (q)->size++;
}
void addSeat(char *name, char *class, int adet, Flights **head,int *count, FILE *output) {
    int i;
    Flights *flights=NULL;
    flights=findFlight(*head,name);
    if(flights==NULL){
        flights=malloc(sizeof(Flights));
        flights->next=NULL;
        flights->flight_name= malloc(sizeof(char) * strlen(name));
        strcpy(flights->flight_name, name);
        flights->Readable = 1;
        flights->busines_count = 0;
        flights->economy_count = 0;
        flights->standard_count = 0;
        flights->empty_seats = malloc(sizeof(Stack) * 3);
        for (i = 0; i <3 ; ++i) {
            flights->empty_seats[i].top = -1;
            flights->empty_seats[i].size = 0;
            flights->empty_seats[i].stack = malloc(sizeof(int));
        }

        flights->siralar = malloc(sizeof(Queue) * 6);
        for (i = 0; i < 6; ++i) {
            flights->siralar[i].size = 0;
            flights->siralar[i].front = 0;
            flights->siralar[i].rear = 0;
            flights->siralar[i].queue = malloc(sizeof(int));
        }
        flights->toplam_yolcu = 0;
        flights->yolcular = malloc(sizeof(Passengers));

        if (strcmp(class, "business") == 0) {
            flights->empty_seats[0].stack = realloc(flights->empty_seats[0].stack, sizeof(int) * (adet));
            for (i = 0; i < adet; ++i) {
                push(12, &flights->empty_seats[0]);
            }
        } else if (strcmp(class, "economy") == 0) {

            flights->empty_seats[1].stack = realloc(flights->empty_seats[1].stack, sizeof(int) * (adet));
            for (i = 0; i < adet; ++i) {
                push(12, &flights->empty_seats[1]);
            }
        } else if (strcmp(class, "standard") == 0) {
            flights->empty_seats[2].stack = realloc(flights->empty_seats[2].stack, sizeof(int) * (adet));
            for (i = 0; i < adet; ++i) {
                push(12, &flights->empty_seats[2]);
            }
        }
        flights->next=*head;
        *head=flights;
    }
    else{

        if (strcmp(class, "business") == 0) {

            flights->empty_seats[0].stack = realloc(flights->empty_seats[0].stack, sizeof(int) * (adet));
            for (i = 0; i < adet; ++i) {
                push(12, &flights->empty_seats[0]);
            }
        } else if (strcmp(class, "economy") == 0) {

            flights->empty_seats[1].stack = realloc(flights->empty_seats[1].stack, sizeof(int) * (adet));
            for (i = 0; i < adet; ++i) {
                push(12, &flights->empty_seats[1]);
            }
        } else if (strcmp(class, "standard") == 0) {
            flights->empty_seats[2].stack = realloc(flights->empty_seats[2].stack, sizeof(int) * (adet));
            for (i = 0; i < adet; ++i) {
                push(12, &flights->empty_seats[2]);
            }
        }
    }
    fprintf(output,"addseats %s %d %d %d\n",flights->flight_name,flights->empty_seats[0].size,flights->empty_seats[1].size,flights->empty_seats[2].size);
}
void enqueue(Flights *flights,char* passname,char*class,int priority,FILE *output){
    flights->yolcular=realloc(flights->yolcular, sizeof(Passengers)*(flights->toplam_yolcu+1));
    flights->yolcular[flights->toplam_yolcu].name=malloc(sizeof(char)*strlen(passname));
    strcpy(flights->yolcular[flights->toplam_yolcu].name,passname);
    flights->yolcular[flights->toplam_yolcu].id=flights->toplam_yolcu;
    flights->yolcular[flights->toplam_yolcu].sold=malloc(sizeof(char)*strlen("none"));
    strcpy(flights->yolcular[flights->toplam_yolcu].sold,"none");
    flights->yolcular[flights->toplam_yolcu].wanted=malloc(sizeof(char)*strlen(class));
    strcpy(flights->yolcular[flights->toplam_yolcu].wanted,class);
    flights->yolcular[flights->toplam_yolcu].priority=priority;
    if(strcmp(class,"business")==0){
        flights->siralar[0].queue=realloc(flights->siralar[0].queue, sizeof(int)*(flights->siralar[0].size+1));
        insert(flights,&flights->siralar[0],flights->toplam_yolcu,priority);
        fprintf(output,"queue %s %s %s %d\n",flights->flight_name,passname,class,flights->siralar[0].size);
    }
    else if (strcmp(class,"economy")==0){
        flights->siralar[1].queue=realloc(flights->siralar[1].queue, sizeof(int)*(flights->siralar[1].size+1));
        insert(flights,&flights->siralar[1],flights->toplam_yolcu,priority);
        fprintf(output,"queue %s %s %s %d\n",flights->flight_name,passname,class,flights->siralar[1].size);

    } else if (strcmp(class,"standard")==0){
        flights->siralar[2].queue=realloc(flights->siralar[2].queue, sizeof(int)*(flights->siralar[2].size+1));
        insert(flights,&flights->siralar[2],flights->toplam_yolcu,0);
        fprintf(output,"queue %s %s %s %d\n",flights->flight_name,passname,class,flights->siralar[2].size);
    }

    flights->toplam_yolcu++;

}
int dequeue(Queue *q){
    int i;

    if (q->size==0){
        return -1;
    }
    int temp=q->queue[0];
    for (i = 0; i < q->size-1; ++i) {
        q->queue[i]=q->queue[i+1];
    }
    q->size=q->size-1;
    q->queue=realloc(q->queue,q->size);
    return temp;
}
void sellticket(Flights *flights,FILE *output){
    int i;
    int temp=flights->empty_seats[0].size;
    int temp1=flights->empty_seats[1].size;
    int temp2=flights->empty_seats[2].size;
    for (i = 0; i <temp ; ++i) {
        int pass_id=dequeue(&flights->siralar[0]);
        if (pass_id==-1){
            break;
        }
        else{
            flights->yolcular[pass_id].sold=malloc(sizeof(char)*strlen("business"));
            strcpy(flights->yolcular[pass_id].sold,"business");
            flights->siralar[3].queue=realloc(flights->siralar[3].queue, sizeof(int)*(flights->siralar[3].size+1));
            flights->siralar[3].queue[flights->siralar[3].size++]=pass_id;
            pop(&flights->empty_seats[0]);
        }
    }
    for (i = 0; i <temp1 ; ++i) {
        int pass_id=dequeue(&flights->siralar[1]);
        if (pass_id==-1){
            break;
        }
        else{
            flights->yolcular[pass_id].sold=malloc(sizeof(char)*strlen("economy"));
            strcpy(flights->yolcular[pass_id].sold,"economy");
            flights->siralar[4].queue=realloc(flights->siralar[4].queue, sizeof(int)*(flights->siralar[4].size+1));
            flights->siralar[4].queue[flights->siralar[4].size++]=pass_id;
            pop(&flights->empty_seats[1]);
        }
    }
    for (i = 0; i <temp2 ; ++i) {

        int pass_id=dequeue(&flights->siralar[2]);

        if (pass_id==-1){
            break;
        }
        else{
            flights->yolcular[pass_id].sold=malloc(sizeof(char)*strlen("standard"));
            strcpy(flights->yolcular[pass_id].sold,"standard");
            flights->siralar[5].queue=realloc(flights->siralar[5].queue, sizeof(int)*(flights->siralar[5].size+1));
            flights->siralar[5].queue[flights->siralar[5].size++]=pass_id;
            pop(&flights->empty_seats[2]);
        }
    }
    temp=flights->empty_seats[2].size;
    for (i = 0; i <temp ; ++i) {
        int pass_id=dequeue(&flights->siralar[0]);

        if (pass_id==-1){
            break;
        }
        else{
            flights->yolcular[pass_id].sold=malloc(sizeof(char)*strlen("standard"));
            strcpy(flights->yolcular[pass_id].sold,"standard");
            flights->siralar[5].queue=realloc(flights->siralar[5].queue, sizeof(int)*(flights->siralar[5].size+1));
            flights->siralar[5].queue[flights->siralar[5].size++]=pass_id;
            pop(&flights->empty_seats[2]);
        }
    }
    temp=flights->empty_seats[2].size;
    for (i = 0; i <temp ; ++i) {
        int pass_id=dequeue(&flights->siralar[1]);
        if (pass_id==-1){
            break;
        }
        else{
            flights->yolcular[pass_id].sold=malloc(sizeof(char)*strlen("standard"));
            strcpy(flights->yolcular[pass_id].sold,"standard");
            flights->siralar[5].queue=realloc(flights->siralar[5].queue, sizeof(int)*(flights->siralar[5].size+1));
            flights->siralar[5].queue[flights->siralar[5].size++]=pass_id;
            pop(&flights->empty_seats[2]);
        }
    }
    fprintf(output,"sold %s %d %d %d\n",flights->flight_name,flights->siralar[3].size,flights->siralar[4].size,flights->siralar[5].size);
}
char *readline(FILE *fp, char **buffer,FILE *output) {
    int ch;
    size_t buflen = 0, nchar = NCHAR;
    *buffer = malloc(nchar);    /* allocate buffer nchar in length */
    if (!*buffer) {
        fprintf(output, "readline() error: virtual memory exhausted.\n");
        return NULL;
    }
    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        (*buffer)[buflen++] = ch;
        if (buflen + 1 >= nchar) {  /* realloc */
            char *tmp = realloc(*buffer, nchar * 2);
            if (!tmp) {
                fprintf(output, "error: realloc failed, "
                                "returning partial buffer.\n");
                (*buffer)[buflen] = 0;
                return *buffer;
            }
            *buffer = tmp;
            nchar *= 2;
        }
    }
    (*buffer)[buflen] = 0;           /* nul-terminate */

    if (buflen == 0 && ch == EOF) {  /* return NULL if nothing read */
        free(*buffer);
        *buffer = NULL;
    }
    return *buffer;
}
int main(int argc, char **argv) {
    Flights *headFlight=NULL;
    int num_of_F=0;
    char *line = NULL;
    size_t idx = 0;
    int counter = 0;
    FILE *output=fopen(argv[2],"w");
    FILE *fp = argc > 1 ? fopen(argv[1], "r") : stdin;
    if (!fp) {
        fprintf(output, "error: file open failed '%s'.\n", argv[1]);
        return 1;
    }
    char *newline;
    char **array = (char **) malloc(sizeof(char *) * 1);
    while (readline(fp, &line,output)) {  /* read each line in 'fp' */
        int i = 0;
        newline = calloc(strlen(line), sizeof(char));
        char *ptr = NULL;
        int ch = '\r';
        ptr = strchr(line, ch);
        if (ptr != NULL) {
            strncpy(newline, line, strlen(line) - 1);
        } else {
            strncpy(newline, line, strlen(line));
        }
        char *p = strtok(newline, " ");
        while (p != NULL) {
            array = realloc(array, sizeof(char *) * (counter + 1));
            array[counter++] = p;
            p = strtok(NULL, " ");
        }
        if (strcmp(array[0], "addseat") == 0) {
            if (counter != 4) {
                fprintf(output,"error\n");
            } else if (addseat_control(array[2], array[3])) {
                fprintf(output,"error\n");
            } else {
                addSeat(array[1], array[2], atoi(array[3]), &headFlight, &num_of_F,output);
            }
        } else if (strcmp(array[0], "enqueue") == 0) {
            if (findFlight(headFlight, array[1]) == NULL) {
                fprintf(output,"error\n");
            } else if (!(counter == 5 || counter == 4)) {
                fprintf(output,"error\n");
            } else if (counter == 5) {
                if (findFlight(headFlight, array[1])->Readable == 0) {
                    fprintf(output,"error\n");
                } else if (strcmp(array[2], "business") == 0 && strcmp(array[4], "diplomat") == 0) {
                    enqueue(findFlight(headFlight, array[1]), array[3], array[2], 1,output);
                } else if (strcmp(array[2], "economy") == 0 && strcmp(array[4], "veteran") == 0) {
                    enqueue(findFlight(headFlight, array[1]), array[3], array[2], 1,output);
                } else if (strcmp(array[2], "standard") == 0) {
                    fprintf(output,"error\n");
                } else {
                    fprintf(output,"error\n");
                }
            } else if (counter == 4) {
                enqueue(findFlight(headFlight, array[1]), array[3], array[2], 0,output);
            }

        } else if (strcmp(array[0], "sell") == 0) {
            if (counter != 2) {
                fprintf(output,"Error\n");
            } else if (findFlight(headFlight, array[1]) == NULL) {
                fprintf(output,"Error\n");
            } else {
                if (findFlight(headFlight, array[1])->Readable == 0) {
                    fprintf(output,"error\n");
                } else {
                    sellticket(findFlight(headFlight, array[1]),output);
                }
            }

        } else if (strcmp(array[0], "close") == 0) {
            if (counter != 2) {
                fprintf(output,"Error\n");
            } else if (findFlight(headFlight, array[1]) == NULL) {
               fprintf(output,"Error\n");
            } else {
                Flights *f = findFlight(headFlight, array[1]);
                if (f->Readable == 0) {
                    fprintf(output,"error\n");
                } else {
                    f->Readable = 0;
                    int satilan = 0;
                    int bekleyen = 0;
                    for (i = 0; i < 6; ++i) {
                        if (i < 3) {
                            bekleyen += f->siralar[i].size;
                        } else {
                            satilan += f->siralar[i].size;
                        }
                    }
                    int j;
                    fprintf(output,"closed %s %d %d\n", f->flight_name, satilan, bekleyen);
                    for (i = 0;i  < 3; ++i) {
                        for (j = 0; j < f->siralar[i].size; ++j) {
                            if (strcmp(f->yolcular[f->siralar[i].queue[j]].sold,"none")==0){
                                fprintf(output,"waiting %s\n",f->yolcular[f->siralar[i].queue[j]].name);
                            }
                        }
                    }
                }
            }

        } else if (strcmp(array[0], "report") == 0) {
            if (counter!=2){
                fprintf(output,"Error\n");
            }
            else if(findFlight(headFlight,array[1])==NULL){
                fprintf(output,"Error");
            }
            else if(findFlight(headFlight,array[1])->Readable==0){
                fprintf(output,"report %s\nbusiness 0\neconomy 0\nstandard 0\nend of %s\n",array[1],array[1]);
            }
            else{
                Flights *f=findFlight(headFlight,array[1]);
                fprintf(output,"report %s\nbusiness %d\n",array[1],f->siralar[3].size);
                for (i = 0;i <f->siralar[3].size ; ++i) {
                    fprintf(output,"%s\n",f->yolcular[f->siralar[3].queue[i]].name);
                }
                fprintf(output,"economy %d\n",f->siralar[4].size);
                for (i = 0;i <f->siralar[4].size ; ++i) {
                    fprintf(output,"%s\n",f->yolcular[f->siralar[4].queue[i]].name);
                }
                fprintf(output,"standard %d\n",f->siralar[5].size);
                for (i = 0;i <f->siralar[5].size ; ++i) {
                    fprintf(output,"%s\n",f->yolcular[f->siralar[5].queue[i]].name);
                }
                fprintf(output,"end of report %s\n",f->flight_name);
            }
        } else if (strcmp(array[0], "info") == 0) {
            if(counter!=2){
                fprintf(output,"Error\n");
            }
            else{
                Flights *f;
                f=headFlight;
                int elma=1;
                while (f!=NULL){
                    for (i = 0;i  < f->toplam_yolcu; ++i) {
                        if (strcmp(array[1],f->yolcular[i].name)==0){
                            fprintf(output,"info %s %s %s %s\n",array[1],f->flight_name,f->yolcular[i].wanted,f->yolcular[i].sold);
                            elma=0;
                            break;
                        }
                    }
                    f=f->next;
                }
                if (elma==1){
                    fprintf(output,"Error\n");
                }
            }

        } else {
            fprintf(output,"ERROR-COMMAND");
        }
        counter = 0;

    }

    free(array);

    fclose(fp);
    fclose(output);
    return 0;
}






