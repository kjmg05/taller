//Proyecto
//Kenia Julissa Martinez Gutierrez
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h> //funcion getch
#include <math.h> //para validar la longitud del dato

/////////////////////////
#define userAdmin "kenia"
#define userSales "kjuli"
#define pAdmin "abcde"
#define pSales "12345"
#define lenght 5
#define taller 2 //El taller solo admite 10 carros por dia
/////////////////////////

FILE *facts; //archivo
int i = 0, lenghtId = 0, cont; //longitud de placa; //Contador para llevar el control de autos ingresados
char opc, opcS, resp; //Ingresar opciones de los distintos sistemas

struct automovil //Aqui se almacenan los datos propios del vehiculo y el nombre del cliente
{
	char id[3];
	int dato;
	char name[50];
	char lastName[50];
};

struct nodoCola
{
	struct automovil autom; //La parte de dato esta almacenada en la estructora automovil
	nodoCola *sigCola;
};

enum servicios //Servicios prestados
{
	filtro = 1, rueda, motor, manoObra
};
 
struct facturas //Datos de la ura
{
	char noFact[10];
	struct automovil autom;
	enum servicios ser;
	double filtroP; //= 250.00
	double ruedaP; //= 400.00
	double motorP; //= 1200.00
	double manoObraP; // = 45.00
	int cantF, cantM, cantR, tiempo;
	double subTotal;
	double isv;
	double totalPagar;
}fact;

char validaChar(char opcion, char opc_1, char opc_2, char opc_3) //Funcion para validar las entradas char
{
	while(opcion != opc_1 && opcion != opc_2 && opcion != opc_3){
		printf("\t\t***ERROR INGRESE [%c/%c/%c]***\n", opc_1, opc_2, opc_3);
		printf("\tIngrese el c%cdigo: ", 162);	
		scanf("%s", &opcion);
		opcion = toupper(opcion);
	}
	return opcion;
} //

void fecha() //Funcion para poner la fecha actual 
{
	time_t tiempo = time(0); //Variable tiempo de tipo time_t
	struct tm *tlocal = localtime(&tiempo); //saca la informacion de tiempo mediante localtime
	char output[128]; //variable para almacenar el tiempo
	strftime(output, 128, "%d-%b-%y", tlocal); //formatea la estructura a lenguaje natural entendible
	printf("\t\t\t\t\tFecha: %s", output);
}//

void tallerNombre() //Funcion para no estar escribiendo el nombre 
{
		system("cls");
		printf("\n\t\t -------------------------------");
		printf("\n\t\t| TALLER MIL RUEDAS AL CUADRADO |");
		printf("\n\t\t -------------------------------\n");
		fecha(); //Funcion para poner la fecha actual 
}//

bool colaVacia(nodoCola *frente) //Verifica si la cola esta vacia
{
		return (frente == NULL)? true : false;
} //

void consultarFact() //mostrar todas las facturas
{
	char c;
	
		facts = fopen("factura.txt", "r");
		if(facts == NULL){
			printf("\n\t**El almacenamiento para facturas NO existe.**");
		}
		else{
			system("cls");
			while((c = fgetc(facts)) != EOF){
				if(c == '\n')
					printf("\n");
				else
					putchar(c);
			}
		}
		fclose(facts);
		printf("\n\n");
		system("pause");
		system("cls");
} //

void salidaTaller(nodoCola *&frente, int &idAuto) //Realiza la dalida del vehiculo del taller
{
	nodoCola *temp = frente;
	idAuto = temp->autom.dato;
	frente = temp->sigCola;
	
		tallerNombre();
		printf("\n\n\t*****EL VEH%cCULO [%d] HA SIDO ENTREGADO A SU DUE%cO.*****\n\n", 214, idAuto, 165);
		delete temp;
		i--;
		system("pause");
} //

void mostraPlaca(nodoCola *&frente, int &idAuto)
{
	nodoCola *aux = frente;
	if(aux!=NULL){
		fprintf(facts, "%d]\n", aux->autom.dato);
		aux=aux->sigCola;
	}
}

void factura(nodoCola *&frente, nodoCola *&fin, int &idAuto, char name[50]) //Se pasan los parametros para llamar desde esta funcion la de salidaTaller
{
//	char empname[50];
//	empname[50] = name[50];
	
	do{
		fact.cantF = 0;
		fact.cantM = 0;
		fact.cantR = 0;			
		fact.subTotal = 0;
		fact.filtroP = 0;
		fact.ruedaP = 0;
		fact.motorP = 0;
		tallerNombre();
		printf("\n\n\t\tSISTEMA DE FACTURA\n");
		printf("\t\tCrear almacenamiento .... [C]\n");
		printf("\t\tIngresar factura ........ [I]\n");
		printf("\t\tRegresar................. [R]\n");
		printf("\tIngrese el c%cdigo: ", 162);	
		scanf("%s", &opcS);
		opcS = toupper(opcS);
		opcS = validaChar(opcS, 'C', 'I', 'R');
		switch(opcS){
			case 'C':
				facts = fopen("factura.txt", "r");
				if(facts == NULL){
					facts = fopen("factura.txt", "w");
					printf("\n\t**El almacenamiento para facturas ha sido creado.**\n\n");
				}
				else{
					printf("\n\t**El almacenamiento para facturas YA existe.**\n\n");
				}
				system("pause");
				break;
			case 'I':
				facts = fopen("factura.txt", "r");
				if(colaVacia(frente)){
					printf("\n\t\t***El taller est%c vac%co. No puede ingresar una factura nueva***\n\n", 160, 161);
					system("pause");
				}
				else if(facts == NULL){
					printf("\n\t**El almacenamiento para facturas NO existe.**\n\n");
					system("pause");
				}
				else{
					facts = fopen("factura.txt", "a");
					tallerNombre();
					printf("\n\n\t\tSISTEMA DE FACTURA\n");
					
					do{ //Numero de factura
						printf("\n Ingrese el n%cmero de factura [2020-1234]: ", 163);
						scanf("%s", &fact.noFact);
						lenghtId = strlen(fact.noFact);
						if(lenghtId < 9 || lenghtId > 9)
							printf("\t\t***Error la factura debe tener 9 elementos***\n\t\t\tEjemplo : [2020-1234]");
					}while(lenghtId < 9 || lenghtId > 9);

					do{ //Placa
						printf(" Los tres primeros elementos de la placa del veh%culo [*ABC*1234]: ", 161);
						scanf("%s", &fact.autom.id);
						lenghtId = strlen(fact.autom.id);
						if(lenghtId < 3 || lenghtId > 3)
							printf("\t\t***Deben ser 3 elementos***\n\t\t\tEjemplo: [ABC]\n");
					}while(lenghtId < 3 || lenghtId > 3);
					
					printf(" Nombre del cliente: ");
					scanf("%s", &fact.autom.name);
					printf(" Apellido del cliente: ");
					scanf("%s", &fact.autom.lastName);
					
					do{ //Servicios
						do{
							tallerNombre();
							printf("\n\t\t\t***SERVICIOS***\n");
							printf("\t\tFiltro .......... [1]\n\t\tRueda ........... [2]\n\t\tMotor ........... [3]\n");
							printf("\n\tC%cdigo de servicio [1-3]: ", 162);
							scanf("%d", &fact.ser);
							if(fact.ser < 1 || fact.ser > 3){
								printf("\t\t***Error... Ingrese [1-3]***\n\n");
								system("pause");
							}
						}while(fact.ser < 1 || fact.ser > 3); //ingresar servicios
						switch(fact.ser){
							case filtro:
								do{
									printf("\t\tCantidad de filtros: ");
									scanf("%d", &fact.cantF);
									fact.filtroP = fact.cantF*250;
									fact.subTotal += fact.filtroP;
									if(fact.cantF < 0)
										printf("\t\t***Error***\n");
								}while(fact.cantF < 0);
								break;
							case rueda:
								do{
									printf("\t\tCantidad de ruedas: ");
									scanf("%d", &fact.cantR);
									fact.ruedaP = fact.cantR*400;
									fact.subTotal += fact.ruedaP;
									if(fact.cantR < 0)
										printf("\t\t***Error***\n");
								}while(fact.cantR < 0);	
								break;
							default:
								do{
									printf("\t\tCantidad de motores: ");
									scanf("%d", &fact.cantM);
									fact.motorP = fact.cantM*1200;
									fact.subTotal += fact.motorP;
									if(fact.cantM < 0)
										printf("\t\t***Error***\n");
								}while(fact.cantM < 0);
								break;
						}
						do{
							printf("\n\tDesea ingresar otro servicio [S/N]: ");
							scanf("%s", &resp);
							resp = toupper(resp);
							if(resp != 'S' && resp != 'N')	
								printf("\t\t***ERROR... INGRESE [S/N]***");	
						}while(resp != 'S' && resp != 'N');
					}while(resp == 'S'); //fin while servicios
		//Archivo
		fprintf(facts, "\n\t\t -------------------------------");
		fprintf(facts, "\n\t\t| TALLER MIL RUEDAS AL CUADRADO |");
		fprintf(facts, "\n\t\t -------------------------------\n");
		fprintf(facts, "\n\tNo. Factura [%s]", fact.noFact);
		fprintf(facts, "\t\tEmpleado: [%s]", name);
		fprintf(facts, "\n\tCliente: [%s %s]", fact.autom.name, fact.autom.lastName);
		fprintf(facts, "\n\tPlaca del vehiculo: [%s ", fact.autom.id);
		mostraPlaca(frente, idAuto); //Parte entera de la placa
		fprintf(facts, "\n\t\t\t**DETALLE FACTURA**\n\n");
		fprintf(facts, "\t Concepto           Cantidad           Base\n");
		fprintf(facts, "\t Filtro ------------ [%d] ---------- [L. %.2lf]\n", fact.cantF, fact.filtroP);
		fprintf(facts, "\t Ruedas ------------ [%d] ---------- [L. %.2lf]\n", fact.cantR, fact.ruedaP);
		fprintf(facts, "\t Motor ------------- [%d] ---------- [L. %.2lf]\n", fact.cantM, fact.motorP);
			srand(time(NULL));
			fact.tiempo=rand()%4+1;
			fact.manoObraP = fact.tiempo*45;
			fact.subTotal += fact.manoObraP;
		fprintf(facts, "\t Mano de Obra ------ [%d] ---------- [L. %.2lf]\n", fact.tiempo, fact.manoObraP);
		fprintf(facts, "\t\tSubtotal [L. %.2lf]\n", fact.subTotal);
		fact.isv = fact.subTotal*0.15;
		fprintf(facts, "\t\tISV      [L. %.2lf]\n", fact.isv);
		fact.totalPagar = fact.subTotal + fact.isv;
		fprintf(facts, "\t\tTotal    [L. %.2lf]\n", fact.totalPagar);
		salidaTaller(frente, idAuto); //Entrega del vehiculo
				}//fin else de ingresar factura
				break;
		} //fin switch servicios factura
		}while(opcS != 'R');
	fclose(facts);
}

void mostrarTaller(nodoCola *&frente, nodoCola *&fin, int idAuto) //Muestra todos los vehiculos en el taller y los espacios disponibles
{
	nodoCola *aux = frente;
	
		tallerNombre();
		printf("\n\n\t\t***VEH%cCULOS EN REPARACI%cN***\n", 214, 224);
		
		while(aux != NULL){
			printf("\n\t\t   | [%d] |", aux->autom.dato);
			printf("\n\t\t      |**|");
			aux = aux->sigCola;
		}
		
		if(i == taller)
			printf("\n\t\t  TALLER LLENO\n\n\a");
		else
			printf("\n\t    ESPACIOS DISPONIBLES [%d]\n\n\a", taller-i);
				
		system("pause");
		system("cls");
} //

void agregarAuto(nodoCola *&frente, nodoCola *&fin, int idAuto) //Funcion para ingresar vehiculos al taller
{
	if(i == taller){
		printf("\n\t**TALLER LLENO.** NO SE PUEDEN AGREGAR VEH%cCULOS\a\n\n", 214);
		system("pause");
	}
	else{
		do{
			i++;
			tallerNombre();
			printf("\n\n\t\t**SISTEMA DE INGRESO DE VEH%cCULOS**\n", 214);
			do{
				printf("\n Ingrese los %cltimos cuatro d%cg%ctos de la placa del veh%cculo [ABC*1234*]: ", 163, 161, 161, 161);
				scanf("%d", &idAuto);
				cont=(log10(idAuto) + 1);
				if(cont > 4 || cont < 4)
					printf("\t\t***Error la placa debe tener 4 elementos***\n\t\t\tEjemplo: [1234]\n");
			}while(cont > 4 || cont < 4);
				
		nodoCola *nuevoNodo = new nodoCola ();
		nuevoNodo->autom.dato= idAuto; 
		nuevoNodo->sigCola = NULL;
			
		if(colaVacia(frente))
			frente = nuevoNodo;
		else
			fin->sigCola = nuevoNodo;
				
		fin = nuevoNodo;
		printf("\t*****EL VEH%cCULO [%d] INGRES%c AL TALLER.*****\n", 214, idAuto,  224);
						
		if(i!=taller+1){
			do{
				printf("\n\t\tDesea continuar [S/N]: ");
				scanf("%s", &resp);
				resp = toupper(resp);
				if(resp != 'S' && resp != 'N')	
					printf("\t\t***ERROR... INGRESE [S/N]***");
			}while(resp != 'S' && resp != 'N');
		}
		}while(resp == 'S' && i!=taller); //Fin while de ingresar vehiculo
				
		if(i == taller && resp == 'S'){ //Decision para que avise que esta lleno
			printf("\n\t**TALLER LLENO.** NO SE PUEDEN AGREGAR VEH%cCULOS\a\n\n", 214);
			system("pause");
		}
	}
	
} //

char pword(char name[50]) 
{
	char usuario[lenght+1];
	char clave[lenght+1];
	bool entry = false;
	int i=0;
	char c;
	
	do{
		tallerNombre();
		i=0;
		printf("\n\n\t\t\t  INICIO SESION");
		printf("\n Usuario: ");
		gets(usuario);
	
		printf(" Contrase%ca: ", 164);
		while(c = getch()){
			if(c == 13){ //ascii enter 
				clave[i] = '\0';
				break;
			}
			else if(c == 8){ //ascii backspace
				if(i>0){
					i--;
					printf("\b \b");
				}
			}
			else{
				if(i<lenght){
				printf("*");
				clave[i] = c;
				i++;
				}
			}
		}
	
		if (strcmp(usuario, userAdmin) == 0 && strcmp(clave, pAdmin) == 0){ //usuario admin
			entry = true;
			strcpy (name, "KJMG");
			return name[50];
		}
			else if (strcmp(usuario, userSales) == 0 && strcmp(clave, pSales) == 0){ //usuario vendedor
			entry = true;
			strcpy (name, "KWPK");
			return name[50];
			}
				else{
				printf("\n\t----USUARIO O CONTRASE%cA INCORRECTO.----", 165);
				entry = false;
				}
	printf("\n\n");
	system("pause");
	system("cls");
	}while(entry == false);
}

main ()
{
	char name[50];
	int idAuto;
	nodoCola *frente = NULL;
	nodoCola *fin = NULL;
	
		name[50] = pword(name); //contraseña
			
		do{
			tallerNombre();
			printf("\n\t\t\tSISTEMAS\n");
			printf("\t\tTaller .............. [T]\n");
			printf("\t\tFactura ............. [F]\n");
			printf("\t\tSalir ............... [S]\n");
			printf("\tIngrese el c%cdigo del sistema: ", 162);	
			scanf("%s", &opc);
			opc = toupper(opc);
			opc = validaChar(opc, 'T', 'F', 'S');
			switch(opc){
				case 'T':
					do{
						tallerNombre();
						printf("\n\n\t\t\tSISTEMA TALLER MEC%cNICO\n", 181);
						printf("\t\tIngresar Veh%cculo .............. [V]\n", 161);
						printf("\t\tVer Taller ..................... [T]\n");
						printf("\t\tRegresar ....................... [R]\n");
						printf("\tIngrese el c%cdigo: ", 162);	
						scanf("%s", &opcS);
						opcS = toupper(opcS);
						opcS = validaChar(opcS, 'V', 'T', 'R');
						switch(opcS){
							case 'V':
								agregarAuto(frente, fin, idAuto);
								break;
							case 'T':
								if(colaVacia(frente)){
									printf("\n\t\t***El taller est%c vac%co.***\n\n", 160, 161);
									system("pause");
								}
								else
									mostrarTaller(frente, fin, idAuto);
								break;
						} //switch de sistema taller
					}while(opcS != 'R'); //while de sistema taller
				break; //Taller
				case 'F':
					do{	
						tallerNombre();
						printf("\n\n\t\t\tSISTEMA DE FACTURA\n");
						printf("\t\tFactura Nueva .............. [N]\n");
						printf("\t\tConsultar Factura .......... [C]\n");
						printf("\t\tRegresar ................... [R]\n");
						printf("\tIngrese el c%cdigo: ", 162);	
						scanf("%s", &opcS);							
						opcS = toupper(opcS);
						opcS = validaChar(opcS, 'N', 'C', 'R');
						switch(opcS){
							case 'N':
								if(colaVacia(frente)){
									printf("\n\t\t***No puede crear una nueva factura. El taller est%c vac%co.***\n\n", 160, 161);
									system("pause");
								}
								else{
									factura(frente, fin, idAuto, name); //Crear Factura antes de que el auto salga del taller
								}
								break;
							case 'C':
								consultarFact();
								break;
						} //switch de sistema factura
					}while(opcS != 'R'); //while de sistema factura
				break; //Factura
				default:
					if(!colaVacia(frente)){
						printf("\n\t\t***No puede no puede salir del sistema si el taller no est%c vac%co.***\n\n", 160, 161);
						system("pause");
					}
					else{
						tallerNombre();
						printf("\n\n\t***GRACIAS POR USAR EL SISTEMA***\n\a");
						exit(0);
					}
					break;
			} //switch de sistema principal
		}while(opc != 'S' || !colaVacia(frente)); //while de sistema principal
	return 0;
}
