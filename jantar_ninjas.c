#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

 pthread_mutex_t mutex_garfo[5];
 pthread_t ninja[5];
 int id[5];
 
 void pegar_garfos(int *filo){
 	pthread_mutex_lock(&(mutex_garfo[*filo]));//ninja tenta pegar garfo
 	if(*filo < 4){
 		pthread_mutex_lock(&(mutex_garfo[*filo + 1]));// bloqueia o outro garfo
	}else{
		pthread_mutex_lock(&(mutex_garfo[0]));// se for o nono ninja ele bloqueia o garfo da posição 0 e não uma posição a mais que ele 
	}
 }
 
 void largar_garfos(int *filo){
 	pthread_mutex_unlock(&mutex_garfo[*filo]);//ninja larga um garfo
 	if(*filo < 4){
 		pthread_mutex_unlock(&mutex_garfo[*filo+1]);//ninja larga o outro
	 }else{
	 	pthread_mutex_unlock(&(mutex_garfo[0]));//se for o nono ninja
	 }
	 printf("ninja %d terminou de comer \n",*filo);
 }
 void *vida_ninja(void * var){//representa toda atividade
 	int *filo = (int*)(var);//identificação ninja
 	while(1){
 		//pensar
 		int pensar = (rand()% 10 + 2);// tempo para pensar 
 		printf("ninja %d pensado %d segundos:\n\n",*filo,pensar);
 		pegar_garfos(filo); //tenta pegar garfos
 		int comer = rand()%5 + 1;//tempo para comer
 		printf("ninja %d comendo\n",*filo);
 		sleep(comer);//estar comendo
 		largar_garfos(filo);//larga os garfos pois já terminou de comer
    }
    pthread_exit(NULL);
}

int main(){
	int i,j;
	system("cls");
	for(i = 0 ; i <= 4; i++){
		pthread_mutex_init(&(mutex_garfo[i]),NULL); // cria as areas criticas
	}
	for(j = 0;j <= 4; j++){
		id[j] =  j;
		pthread_create(&ninja[j],NULL,&vida_ninja,(void*)&id[j]);//cria a treads da primeira mesa
	}
	while(1){
    	
	}
	return 0;
}
