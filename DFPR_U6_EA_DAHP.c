/* ------------------------------------> LIBRERIAS Y DEFINICIONES DE CONSTANTES <--------------------------------------  */
#include <stdio.h>
#include <time.h> 
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define SEGUNDOS_POR_DIA ( 24 * 60 * 60 ) // para realizar operaciones de diferencia de dias
/* ------------------------------------> VARIABLES GLOBALES <--------------------------------------  */
char opcion1; 
int cp2; char letras;
int temp, status;
int lectura1, lectura2, resulta, seguir; 
char letras1, letras2;
time_t fecha_inicial, fecha_final; 
int dias, dias2, anio1, mes1, dia1, anio2, mes2, dia2, aniobms, seguir2 = 1;
int  z, numr, result2, nbimestre[6] = {59,61,61,62,61,61};
char ltr;
float CPB, CPB2; 
struct datos{
		char nombre[25]; 
		int cp;
		int predio;	
		int lecturaInicial;
		int lecturaFinal;
}cliente; 

/* ------------------------------------> PROTOTIPOS DE LAS FUNCIONES <--------------------------------------  */
int valida_nombres(char nombre[]);
int validaDatos(int numero, char caracteres);
int validaDatos2(int numr, char ltra);
time_t diferenciaFechas( int dia, int mes, int anio );

/* ------------------------------------> INICIA FUNCIÓN PRINCIPAL <--------------------------------------  */
main()
{
	do{
		printf("***********************************************\n");
		printf("*         Calculo del consumo promedio        *\n");
		printf("*          bimestral del agua (CPB)           *\n");
		printf("***********************************************\n\n");
		printf("         Presione una tecla para empezar       ");
    	getch();
    	fflush(stdin); 
		system("cls");
    	do{ 
    		printf("Captura tu nombre: ");        
     	}while(valida_nombres(cliente.nombre));		
		cp2 = validaDatos(cliente.cp, letras);
		system("cls");
		printf("Captura predio: ");
		status = scanf("%d", &cliente.predio); 
			while(status!=1){ 
				while((temp=getchar()) != EOF && temp != '\n'); 
					printf("\nFAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS");
					getch();
					system("cls");
					printf("Captura predio: ");
					status = scanf("%d", &cliente.predio);
			}
		system("cls");
		seguir = 1; 
			while(seguir == 1){	
				printf("Ingresa la lectura actual y despu%cs la lectura anterior\n\n", 130);
				lectura1 = validaDatos2(cliente.lecturaInicial, letras1);
				lectura2 = validaDatos2(cliente.lecturaFinal, letras2); 
				resulta = lectura1 - lectura2; 
					if(resulta <=0){ 
						printf("\nError en las lecturas, la lectura actual debe ser mayor que la lectura anterior");
						getch(); 
						seguir = 1; 
						system("cls"); 
					}else{
					seguir = 0;				
					}					
			}
		system("cls"); 
		/* Captura de fechas */
			while (seguir2 == 1){ 
				printf("Ingresa fecha actual (formato: dd mm aaaa): "); 
     			scanf("%d%d%d", &dia1,&mes1,&anio1); 
     			fecha_inicial = diferenciaFechas( dia1, mes1, anio1 ); 
     			printf("Ingresa fecha anterior (formato: dd mm aaaa): "); 
     			scanf("%d%d%d", &dia2,&mes2,&anio2); 
     			fecha_final = diferenciaFechas( dia2, mes2, anio2 ); 
     			dias = difftime(fecha_final, fecha_inicial) / SEGUNDOS_POR_DIA; 
     			aniobms = anio1%4; 
     			dias2 = abs(dias);
     				if(dias2 <7 || dias2 >120){ 
     					printf("\nES NECESARIO REVISAR DE NUEVO FECHAS DEL BIMESTRE"); 
     					getch();
     					limpia_entrada();
						seguir2 = 1; 
						system("cls"); 
     				}else{     		  
						seguir2 = 0; 		
     				}
			}
		system("cls"); 
		/* Captura de bimestre */	
			do{ 
				printf("Captura el bimestre (del 1 al 6):\n\nEne-Feb(1) / Mar-Abr(2) / May-Jun(3)\nJul-Ago(4) / Sep-Oct(5) / Nov-Dic(6) "); 	
				result2 = scanf("%d%c", &numr, &ltr); 		
					while (result2 != 2 || ltr != '\n'){ 
        				limpia_entrada(); 
						printf("\n\nSOLO DATOS NUM%cRICOS, PRESIONE CUALQUIER TECLA PARA CONTINUAR", 144); 
						getch(); 
						system("cls");  
						printf("Captura el bimestre (del 1 al 6):\n\nEne-Feb(1) / Mar-Abr(2) / May-Jun(3)\nJul-Ago(4) / Sep-Oct(5) / Nov-Dic(6) "); 
						result2 = scanf("%d%c", &numr, &ltr); 
        			}
        			if(numr<=0 || numr >6){ 
           				printf("\n\nNO DEFINI%c CORRECTAMENTE SU ENTRADA,\nEL SISTEMA TOMARA EL VALOR DE 60 D%cAS PARA EL BIMESTRE", 224, 214); 
           				getch(); 
           				numr = 60;
           				system("cls"); 
           				break;
        			}else{ 
           				numr = numr - 1; 
	    					for(z=0; z<=5; z++){
								if(numr == z){ 
									numr = nbimestre[z]; 
									break; 
								}
	    					}
        				break; 
        			}      
    		}while(1);  
		system("cls");
		if(aniobms == 0 && numr == 59){ 
			numr = numr+1;
		}
		CPB = ((double)resulta / dias2)*100.0/100; 
		CPB2 = CPB * numr;		
		printf(":::: CONSUMO PROMEDIO BIMESTRAL DEL AGUA ::::");
		printf("\n\n | DATOS CAPTURADOS |\n\n");
		printf("Cliente: %s", cliente.nombre);	
		printf("\nUbicaci%cn (C%cdigo Postal): %d", 162, 162, cp2);	
		printf("\nN%cmero de predio: %d", 163, cliente.predio); 
		printf("\nLectura en el periodo: %d", resulta); 
		printf("\nLos d%cas transcurridos del periodo fueron: %d", 161, dias2); 
		printf("\nLos d%cas del bimestre son: %d", 161, numr); 
		printf("\nEl Consumo Promedio Bimestral es de = %.2fm%c", CPB2, 252); 	
		printf("\n\n\nDESEA CAPTURAR OTRO PREDIO? SI (S / s) / NO (N / n): "); 
    	scanf("%s", &opcion1); 
    	system("cls");
	}while (opcion1 == 'S' || opcion1 == 's'); 
printf("GRACIAS POR USAR EL PROGRAMA, ADI%cS !\n", 224); 
getch(); 
return 0;
}
/* ------------------------------------> DEFINICIÓN DE FUNCIONES <--------------------------------------  */
// 1. Función para validar el nombre completo - solo acepta letras
int valida_nombres(char nombre[]){ 
int opcion; 
  do{         
        gets(&nombre[0]); 
  		if(nombre[0] == '\0' || nombre[0] == '\n'){ 
  			system("cls");
  			printf("FAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS"); 			   
  			getch();
			system("cls");
			printf("Captura tu nombre: "); 
		}else if(!isalpha(nombre[0])){ 
			printf("FAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS"); 
    		getch(); 
			system("cls");
			printf("Captura tu nombre: ");
		}else{
			system("cls");
			break; 
		}
  } while (opcion=1); 
    return nombre[25];
}
// 2. funcion que limpia las entradas (se requiere para el modulo validaDatos() y validaDatos2)
limpia_entrada(){
	while (getchar()!='\n'); 
	return; 
}
// 3. funcion para validar codigo postal (numeros positivos entre 01000 Y 99998)
int numero;
int resultado;
char caracteres;
int validaDatos(int numero, char caracteres){ 
	for(;;) { 
	system("cls");
    printf("Captura tu c%cdigo postal: ", 162);
    resultado = scanf("%d%c", &numero, &caracteres); 
    	if (resultado != 2 || caracteres != '\n'){
    		limpia_entrada(); 
    		printf("\n\nFAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS");
    		getch(); 
    		system("cls"); 
    	}else if(numero < 0 || numero > 99998){
			printf("\n\nFAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS"); 
        	getch();
        	system("cls"); 
		}else{
			system("cls");
			return numero; 
        	break;	
		}
    }
}
// 4. Función para validar lecturas (solo numeros enteros positivos)
int validaDatos2(int numr, char ltra){
int resultad2;
do{ 
	printf("Captura lectura :"); 
	resultad2 = scanf("%d%c", &numr, &ltra); 
		while (resultad2 != 2 || ltra != '\n'){ 
		    limpia_entrada(); 
			printf("\n\nSOLO DATOS NUM%cRICOS, PRESIONE CUALQUIER TECLA PARA CONTINUAR", 144); 
			getch(); 
			system("cls"); 
			printf("Ingresa la lectura actual y despu%cs la lectura anterior\n\n", 130);		 
			printf("Captura lectura :"); 
			resultad2 = scanf("%d%c", &numr, &ltra); 
        }
        if(numr<=0){ 
            printf("\n\nSOLO N%cMEROS POSITIVOS, PRESIONE CUALQUIER LETRA PARA CONTINUAR", 233); 
            getch();
            system("cls"); 
            printf("Ingresa la lectura actual y despu%cs la lectura anterior\n\n", 130);
        }else{
        	return numr; 
            break; 
        }     
    }while(1);      
}
// 5. funcion para obtener fecha
time_t diferenciaFechas( int dia, int mes, int anio ) {    
	 time_t fechaHoy; 
     struct tm * miTiempo;  
     time( &fechaHoy ); 
     miTiempo = localtime( &fechaHoy );    
     miTiempo->tm_mday = dia;
     miTiempo->tm_mon = mes - 1;   
     miTiempo->tm_year = anio - 1900;
     return( mktime( miTiempo ) );
 }
