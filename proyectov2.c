#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int cajeros[10];
int clientes[100];
int productos[50];

void clienteComprando(int producto, int numCliente);
double siendoAtentidoPorElCajero(int numero, int numero2);

clock_t ti, tf;
double tiempoTotalPersonasCadaCajero = 0;
double tiempoTotalTodosLosCajeros = 0;

int main (){
	size_t n = sizeof(cajeros) / sizeof(cajeros[0]);
	size_t c = sizeof(clientes) / sizeof(clientes[0]);
	size_t p = sizeof(productos) / sizeof(productos[0]);
    	
   	for (int x=1; x<=n; x++){
   		int pid = fork();
   		switch(pid){
        		case -1: 
        			printf("Error \n");
           	   		sleep(1);
            	  		break;
            	  		           	    
        		case 0:
        			tiempoTotalPersonasCadaCajero = siendoAtentidoPorElCajero(c, p); 
        			tiempoTotalTodosLosCajeros += tiempoTotalPersonasCadaCajero; 
        			printf("\n=> El tiempo total que un cajero atendió a 100 clientes, es %lf \n", tiempoTotalPersonasCadaCajero);    
        			   	
                		break;
               
        		default: 
        			printf("-------------------------------------------------------------------------------------------------------------");
                		printf("\n==> Este es el proceso padre. Soy el cajero numero %d: %d \n", x, getpid());
                		wait(0);
                		exit(0);
				break;
        	}
        }
        printf("-------------------------------------------------------------------------------------------------------------");
        printf("\n=> El tiempo total de todos los cajeros atendiendo, es %lf \n", tiempoTotalTodosLosCajeros); 
}

double siendoAtentidoPorElCajero(int numero, int numero2){
	double promedio = 0;
	
	for(int y = 1; y <= numero; y++){
		printf("\tEste es el proceso hijo. Soy el cliente numero %d, y mi padre con PPID: %d me está atendiendo. \n", y, getppid());
		ti = clock();
		printf("\t\tEl tiempo de incio (en segundos) es: %lf\n", (double) ti / CLOCKS_PER_SEC);
		for (int i = 1; i <= numero2; i++){
			//printf("El producto %d del cliente %d ha sido cobrado \n", i, y);
			sleep(0.99);
		}
		tf = clock();
		printf("\t\tEl tiempo final (en segundos) es %lf\n", (double) tf / CLOCKS_PER_SEC);
		
		promedio += (double) (tf - ti) / CLOCKS_PER_SEC;	
	}
	return promedio;
}
