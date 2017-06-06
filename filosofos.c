#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define TRUE 1
#define FALSE 0


int state[N];
sem_t mutex;
sem_t s[N]; 


void *filosofo_thread(void *arg);


void print_name(int i){
switch(i){
case 0: printf("Aristoteles"); break;
case 1: printf("Socrates"); break;
case 2: printf("Platao"); break;
case 3: printf("Descartes"); break;
case 4: printf("Pitagoras"); break;
}
}

void think(int i){
print_name(i);
printf(" esta pensando...\n");
}

void eat(int i){
print_name(i);
printf(" esta comendo...\n");
}

void hungry(int i){
print_name(i);
printf(" esta com fome...\n");
}


void test(i){
if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
state[i] = EATING;
sem_post(&s[i]);
}
}


void take_forks(int i){
sem_wait(&mutex);
state[i] = HUNGRY;
hungry(i);
test(i);
sem_post(&mutex);
sem_wait(&s[i]);
} 


void put_forks(i){
sem_wait(&mutex);
state[i] = THINKING;
test(LEFT);
test(RIGHT);
sem_post(&mutex);
} 


void philosopher(int i){
while (TRUE) {
think(i);
take_forks(i);
eat(i);
put_forks(i);
}
} 


void *filosofo_thread(void *arg){
philosopher((int)arg);
}


int main(){
int count=0;
pthread_t f_thread[N];

for(count=0;count<N;count++) state[count]=THINKING;
for(count=0;count<N;count++) sem_init(&s[count],0,0);
sem_init(&mutex,0,1);

for(count=0;count<N;count++)(&f_thread[count],NULL,filosofo_thread,( pthread_createvoid *)count);
for(count=0;count<N;count++) pthread_join(f_thread[count],NULL);

return 0;
}
