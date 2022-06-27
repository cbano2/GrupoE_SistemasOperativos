#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int clientes[100];
int productos[50];

clock_t ti, tf;
double tiempoTotalTodosLosCajeros = 0;

size_t c = sizeof(clientes) / sizeof(clientes[0]);
size_t p = sizeof(productos) / sizeof(productos[0]);

sem_t s;

void *siendoAtentidoPorElCajero(void *arg){
	double promedio = 0;
	
	for(int y = 1; y <= c; y++){
		printf("Soy el cliente numero %d \n", y);
		ti = clock();
		printf("\tEl tiempo de incio (en segundos) es: %lf\n", (double) ti / CLOCKS_PER_SEC);
		for (int i = 1; i <= p; i++){
			//printf("El producto %d del cliente %d ha sido cobrado \n", i, y);
			sleep(0.99);
		}
		tf = clock();
		printf("\tEl tiempo final (en segundos) es %lf\n", (double) tf / CLOCKS_PER_SEC);
		
		promedio += (double) (tf - ti) / CLOCKS_PER_SEC;	
	}
	printf("\nEl tiempo total que un cajero atendió a 100 clientes, es: %f\n", promedio);
	printf("-------------------------------------------------------------------------------------------------------------");
	sem_wait(&s);
	tiempoTotalTodosLosCajeros += promedio;
	sem_post(&s);
}

int main (){

	sem_init(&s, 0, 1);
	pthread_t h1, h2, h3, h4, h5, h6, h7, h8, h9, h10;
	
	printf("\n==> Soy el cajero 1\n");
	pthread_create(&h1, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h1, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 2\n");
	pthread_create(&h2, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h2, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 3\n");
	pthread_create(&h3, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h3, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 4\n");
	pthread_create(&h4, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h4, NULL);
	printf("\n");
    	
    	printf("\n==> Soy el cajero 5\n");
    	pthread_create(&h5, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h5, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 6\n");
	pthread_create(&h6, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h6, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 7\n");
	pthread_create(&h7, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h7, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 8\n");
	pthread_create(&h8, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h8, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 9\n");
	pthread_create(&h9, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h9, NULL);
	printf("\n");
	
	printf("\n==> Soy el cajero 10\n");
	pthread_create(&h10, NULL, siendoAtentidoPorElCajero, NULL);
	pthread_join(h10, NULL);
	printf("\n");	
	
	printf("\nEl tiempo total de todos los cajeros atendiendo, es: %f \n", tiempoTotalTodosLosCajeros);	
}
