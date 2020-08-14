/* ------------------------------------> LIBRERIAS Y DEFINICIONES DE CONSTANTES <--------------------------------------  */
#include <stdio.h>
#include <time.h> 
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define SEGUNDOS_POR_DIA ( 24 * 60 * 60 ) // para realizar operaciones de diferencia de dias
/* ------------------------------------> VARIABLES GLOBALES <--------------------------------------  */
// Variable para reiniciar el programa o salir del mismo
char opcion1; 
// Variables para codigo postal
int cp2; char letras;
// Variables para predio
int temp, status;
// Variables a ocupar en captura de lecturas (seguir es para el bucle) 
int lectura1, lectura2, resulta, seguir; 
char letras1, letras2;
// Variables para guardar la fecha que devuelve la funcion de validacion
time_t fecha_inicial, fecha_final; 
int dias, dias2, anio1, mes1, dia1, anio2, mes2, dia2, aniobms, seguir2 = 1;
// Variables para seleccion de bimestre
int  z, numr, result2, nbimestre[6] = {59,61,61,62,61,61};
char ltr;
// Variables para operacions y/o resultados del calculo CPB
float CPB, CPB2; 
// Estructura de datos para clientes
struct datos{
		char nombre[25]; 
		int cp;
		int predio;	
		int lecturaInicial;
		int lecturaFinal;
}cliente; 

/* ------------------------------------> PROTOTIPOS DE LAS FUNCIONES <--------------------------------------  */
// Función que valida la entrada del usuario - variable nombre: solo acepta letras
int valida_nombres(char nombre[]);
// Función para validar Codigo Postal
int validaDatos(int numero, char caracteres);
// Función para validar las lecturas 
int validaDatos2(int numr, char ltra);
// Función para obtener las fechas
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
    	fflush(stdin); // este sirve para limpiar (vaciar) el buffer del teclado (standard input - stdin). se ocupara si se reinicia el programa 
		system("cls");
		// Pedir datos del cliente (nombre completo)
    	do{ 
    		printf("Captura tu nombre: ");        
     	}while(valida_nombres(cliente.nombre));		
		// Captura codigo postal, la funcion, no devolvera nada hasta que sea validado
		cp2 = validaDatos(cliente.cp, letras);
		system("cls");
		/* Captura de predio */	
		printf("Captura predio: ");
		status = scanf("%d", &cliente.predio); // scanf regresa un entero que corresponde al numero de datos obtenido
			while(status!=1){ // mientras no me halla regresado el dato que quiero
				while((temp=getchar()) != EOF && temp != '\n'); // validacion de caracteres
					printf("\nFAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS");
					getch();
					system("cls");
					printf("Captura predio: ");
					status = scanf("%d", &cliente.predio);
			}
		system("cls");
		/* Captura de lecturas */
		seguir = 1; 
			while(seguir == 1){	// ciclo que se repetira mientras variable seguir sea igual a 1		
				printf("Ingresa la lectura actual y despu%cs la lectura anterior\n\n", 130);
				lectura1 = validaDatos2(cliente.lecturaInicial, letras1); // valido las capturas y el resultado se lo asigno a variable
				lectura2 = validaDatos2(cliente.lecturaFinal, letras2); // valido las capturas y el resultado se lo asigno a variable
				resulta = lectura1 - lectura2; // operaciones con variables y el resultado asigno a nueva variable
					if(resulta <=0){ // valido las lecturas, la actual debe ser mayor que la anterior
						printf("\nError en las lecturas, la lectura actual debe ser mayor que la lectura anterior"); // mensaje de error
						getch(); // espero que el usuario teclee (solo para pausar el mensaje anterior=
						seguir = 1; // no modifico la variable para que se repita el bucle
						system("cls"); // limpio pantalla
					}else{
					//si los datos son correctos (condicion if falsa) entonces asigno 0 a variable para salir del bucle
					seguir = 0;				
					}					
			}
		system("cls"); // limpio pantalla
		/* Captura de fechas */
			while (seguir2 == 1){ // bucle que se repetira hasta que la condicion deje de cumplirse
				printf("Ingresa fecha actual (formato: dd mm aaaa): "); // mensaje requiriendo datos
     			scanf("%d%d%d", &dia1,&mes1,&anio1); // guardo datos
     			fecha_inicial = diferenciaFechas( dia1, mes1, anio1 ); // obtengo las fechas segun la funcion anteriormente definida
     			printf("Ingresa fecha anterior (formato: dd mm aaaa): "); // mensaje requiriendo datos
     			scanf("%d%d%d", &dia2,&mes2,&anio2); // guardo datos
     			fecha_final = diferenciaFechas( dia2, mes2, anio2 ); // obtengo fechas segun la funcion anteriormente definida   
     			dias = difftime(fecha_final, fecha_inicial) / SEGUNDOS_POR_DIA; // realizo operaciones para obtener la diferencia de dias
     			aniobms = anio1%4; // año bisiesto o no (0 = es bisiesto, !=0 no es bisiesto
     			dias2 = abs(dias); // formateo los dias
     				if(dias2 <7 || dias2 >120){ // si la diferencia de dias es menor que 7 y mayor que 120
     					printf("\nES NECESARIO REVISAR DE NUEVO FECHAS DEL BIMESTRE"); // mensaje de error
     					getch();
     					limpia_entrada();
						seguir2 = 1; // el valor de seguir sera 1 y se repite el bucle
						system("cls"); // limpio pantalla
     				}else{     		  
						seguir2 = 0; // le asigno otro valor a variable que condiciona el bucle para salir			
     				}
			}
		system("cls"); // limpio pantalla
		/* Captura de bimestre */	
			do{ 
				printf("Captura el bimestre (del 1 al 6):\n\nEne-Feb(1) / Mar-Abr(2) / May-Jun(3)\nJul-Ago(4) / Sep-Oct(5) / Nov-Dic(6) "); // mensaje 	
				result2 = scanf("%d%c", &numr, &ltr); // scanf regresa el numero de elementos escaneados o leidos		
					while (result2 != 2 || ltr != '\n'){ // mientras que el numero de elementos escaneados sea diferente de 2 y de \n (salto de linea/espacio)
        				limpia_entrada(); // funcion vaciar - descrita lineas arriba
						printf("\n\nSOLO DATOS NUM%cRICOS, PRESIONE CUALQUIER TECLA PARA CONTINUAR", 144); 
						getch(); 
						system("cls");  
						printf("Captura el bimestre (del 1 al 6):\n\nEne-Feb(1) / Mar-Abr(2) / May-Jun(3)\nJul-Ago(4) / Sep-Oct(5) / Nov-Dic(6) "); 
						result2 = scanf("%d%c", &numr, &ltr); // vuelvo a escanear para vollver a verificar
        			}
        			if(numr<=0 || numr >6){ // si paso la validacion superior, es hora de verificar que sean numeros del 1 al 6
           				printf("\n\nNO DEFINI%c CORRECTAMENTE SU ENTRADA,\nEL SISTEMA TOMARA EL VALOR DE 60 D%cAS PARA EL BIMESTRE", 224, 214); 
           				getch(); 
           				numr = 60;
           				system("cls"); 
           				break;
        			}else{ // si es numero positivo, y si esta dentro del rango (1-6)
           				numr = numr - 1; // resto una unidad, pues lo comparare con el arreglo, y en los arreglos empiezan de cero
	    					for(z=0; z<=5; z++){
								if(numr == z){ // si el valor obtenido del usuario es igual a z
									numr = nbimestre[z]; // asigno el valor del bimestre a variable numr
									break; // salgo
								}
	    					}
        				break; 
        			}      
    		}while(1);  
		system("cls");
		/* operaciones */
		// esta condicion es solo para verificar el valor del bimestre.
		// si su valor es de 59 y el año es bisiesto, se le suma un dia	
		if(aniobms == 0 && numr == 59){ 
			numr = numr+1;
		}
		CPB = ((double)resulta / dias2)*100.0/100; 
		CPB2 = CPB * numr;		
		printf(":::: CONSUMO PROMEDIO BIMESTRAL DEL AGUA ::::");
		printf("\n\n | DATOS CAPTURADOS |\n\n");
		printf("Cliente: %s", cliente.nombre);	// muestro nombre
		printf("\nUbicaci%cn (C%cdigo Postal): %d", 162, 162, cp2);	// muestro codigo postal
		printf("\nN%cmero de predio: %d", 163, cliente.predio); // muestro predio
		printf("\nLectura en el periodo: %d", resulta); // muestro resultado de lecturas
		printf("\nLos d%cas transcurridos del periodo fueron: %d", 161, dias2); // muestro dias transcurridos
		printf("\nLos d%cas del bimestre son: %d", 161, numr); // muestro dias del bimestre	
		printf("\nEl Consumo Promedio Bimestral es de = %.2fm%c", CPB2, 252); // muestro CPB	
		printf("\n\n\nDESEA CAPTURAR OTRO PREDIO? SI (S / s) / NO (N / n): "); // pregunto si se desea obtener otro calculo nuevo
    	scanf("%s", &opcion1); // capturo respuesta
    	system("cls");
	}while (opcion1 == 'S' || opcion1 == 's'); // ssi es S, se reinicia, si no, termina
printf("GRACIAS POR USAR EL PROGRAMA, ADI%cS !\n", 224); 
getch(); 
return 0;
}
/* ------------------------------------> DEFINICIÓN DE FUNCIONES <--------------------------------------  */
// 1. Función para validar el nombre completo - solo acepta letras
int valida_nombres(char nombre[]){ // parametro a validar
int opcion; // variable para condicion while
  do{         
        gets(&nombre[0]); // obtengo la entrada del teclado
  		if(nombre[0] == '\0' || nombre[0] == '\n'){ // evaluo la condicion: si se presiono enter o el nombre no tiene ningun valor
  			system("cls");
  			printf("FAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS"); // mensaje de error				   
  			getch();
			system("cls");
			printf("Captura tu nombre: "); // mensaje requiriendo datos de entrada
		}else if(!isalpha(nombre[0])){ // si lo que se capturo no es una palabra (si es numero o simbolos
			printf("FAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS"); // mensaje de error
    		getch(); // espero entrada del teclado
			system("cls");
			printf("Captura tu nombre: ");
		}else{
			system("cls");
			break; // salgo de la validacion, significa que la entrada fue valida
		}
  } while (opcion=1); // bucle que se repite indefinidamente, pues la variable de condicion no la cambio dentro del ciclo 
    return nombre[25];
}
// 2. funcion que limpia las entradas (se requiere para el modulo validaDatos() y validaDatos2)
limpia_entrada(){
	while (getchar()!='\n'); // condicion: mientras getchar (lo que se tecleo) no haya sido la tecla enter (vacio o salto de linea
	return; // no regreses nada, no guardes nada en variable (limpia variables)
}
// 3. funcion para validar codigo postal (numeros positivos entre 01000 Y 99998)
int numero;
int resultado;
char caracteres;
int validaDatos(int numero, char caracteres){ // parametros a validar
	for(;;) { // bucle infinito, yo saldre (con un break) hasta que la captura sea valida
	system("cls"); // limpiar pantalla
    printf("Captura tu c%cdigo postal: ", 162); // mensaje
    resultado = scanf("%d%c", &numero, &caracteres); //scanf retorna siempre el valor leido, si se le pasan dos variables,regresa un entero (2)
    	if (resultado != 2 || caracteres != '\n'){ // si resultado es diferente de 2 y caracteres diferente de vacio
    		limpia_entrada(); // limpiamos variables, pues las volveremos a ocupar
    		printf("\n\nFAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS"); // mensaje de error
    		getch(); // en espera de que se ingrese una tecla (hago pausa)
    		system("cls"); // limpio pantalla
    	}else if(numero < 0 || numero > 99998){ // si fue un numero pero no dentro del rango, mando mensaje de error
			printf("\n\nFAVOR DE INTRODUCIR CORRECTAMENTE LOS DATOS"); // mensaje de error
        	getch(); // en espera de que se ingrese una tecla (hago pausa)
        	system("cls"); // limpio pantalla
		}else{ // si pasa la validacion
			system("cls");
			return numero; // retorno el numero validado
        	break;	// salgo del ciclo, significa que la entrada fue la correcta
		}
    }
}
// 4. Función para validar lecturas (solo numeros enteros positivos)
int validaDatos2(int numr, char ltra){
int resultad2;
do{ 
	printf("Captura lectura :"); // mensaje indicando lo que se debe hacer
	resultad2 = scanf("%d%c", &numr, &ltra); //scanf devuelve el numero de datos guardados
		while (resultad2 != 2 || ltra != '\n'){ //si el resultado es diferente de 2 y term diferente de \n (salto de linea, pero tambien puede representar espacio en blanco)
		    limpia_entrada(); // uso la funcion limpia_entrada (funcion creada mas abajo), esta me permite limpiar mis variables
			printf("\n\nSOLO DATOS NUM%cRICOS, PRESIONE CUALQUIER TECLA PARA CONTINUAR", 144); //mensaje de error
			getch(); // espero entrada (tecleo) del usuario
			system("cls"); // limpio pantalla para volver a pedir datos	
			printf("Ingresa la lectura actual y despu%cs la lectura anterior\n\n", 130);		 
			printf("Captura lectura :"); // mensaje indicando lo que se debe hacer
			resultad2 = scanf("%d%c", &numr, &ltra); // vuelvo a asignar el valor de retorno de scanf a variable
        }
        if(numr<=0){ // cuando el ciclo while ya de verdadero, es tiempo ahora de evaluar si el usuario puso un valor menor a 0 (ejemplo -23)
            printf("\n\nSOLO N%cMEROS POSITIVOS, PRESIONE CUALQUIER LETRA PARA CONTINUAR", 233); // mensaje de error 
            getch(); // espero entrada (tecleo) del usuario
            system("cls"); // limpio pantalla para volver a pedir datos
            //inserto titulos
            printf("Ingresa la lectura actual y despu%cs la lectura anterior\n\n", 130);
        }else{
        	return numr; // despues de la validacion y que ya capturo solo numeros positivos, entonces regreso unicamente la variable numerica
            break; // salgo de mi bucle while
        }  
	// bucle que se define como infinito, por que yo salgo hasta que le de break, y esto se cumple cuando ya paso la validacion    
    }while(1);      
}
// 5. funcion para obtener fecha
time_t diferenciaFechas( int dia, int mes, int anio ) { // parametros a evaluar     
	 time_t fechaHoy; // tipo de variable (time_t) adecuada para guardar fecha (llamada fechaHoy)         
     // estructura (struct tm) usada para contener fecha y hora (apuntador a estructura tm que se llame miTiempo)
     // las estructuras pueden contener varios valores, y en este caso contendran anio mes y dia para hacer los calculos deseados
     struct tm * miTiempo;  
     // la funcion time calcula la fecha - la guardaremos en variable creada (fechaHoy) y la reornaremos al puntero tm creada (miTiempo)
     time( &fechaHoy ); 
     miTiempo = localtime( &fechaHoy );       
     // reasigno fecha
     miTiempo->tm_mday = dia; // aqui guardare el dia
     miTiempo->tm_mon = mes - 1;    // guardar el mes 
     miTiempo->tm_year = anio - 1900; // guardar el año
     return( mktime( miTiempo ) ); // regreso fecha obtenida
 }
