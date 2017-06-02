#include <iostream>
#include <stdlib.h>
#include <stdio.h>          //Bibliotecas necesarias para llamar a las funciones que se van a usar
#include <conio.h>
#include<windows.h>

struct nodo
{ // definicion de la estructura que se utilizara para manejar las 3 torres en pilas
int valor; //valor con el que se conoce el disco
struct nodo *siguiente; // conexion de un disco
};

COORD coord={0,0};  //definicion de las cordenadas
struct nodo *origen, *torre1, *torre2; //definicion de los 3 punteros que señalaran a cada una de las 3 torres
FILE *estado; // definicion del puntero donde se guardaran las movidas del juego

void push1(int); //definicion de la funcion push para insertar discos en la torres origen
void push2(int);//definicion de la funcion push para insertar discos en la torre 1
void push3(int);//definicion de la funcion push para insertar discos en la torre 2
int pop1(); // definicion de la funcion pop para sacara discos de la torre origen
int pop2(); // definicion de la funcion pop para sacara discos de la torre 1
int pop3();// definicion de la funcion pop para sacara discos de la torre 2
void hanoi(int); //definicion de la funcion hanoi que llevara a cargo el llamado de las funciones necesarias para realizar el algoritmo
void movimientopar(); // definicion de la funcion a cargo de mover el disco 1 en caso de que la cantidad total de discos sea par
void movimientoimpar(); // definicion de la funcion a cargo de mover el disco 1 en caso de que la cantidad total de discos sea impar
void impresion(int); // definicion de la funcion que imprimira en pantalla el estado actual de las torres
int general(); //definicion de la funcion a cargo del movimiento general que ralizan los discos que noson el disco 1 en cualquier ccaso

void goxy(int x,int y){//inicio de la funcion gotoxy para posicionar el cursor en una coordenada de la pantalla resiviendo 2 datos
 coord.X=x; //igualacion de el dato obtenido con la coordenada para el eje x
 coord.Y=y; //igualacion de el dato obtenido con la coordenada para el eje y
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); //llamado a la funcion para posicionar el cursor en pantalla en base a las coordenadas obtenidas
 }

using namespace std;
int main(){ // inicio del programa
int d=0,x=0; // definicion de 2 variables enteras

system("cls;"); // limpieza de pantalla
estado= fopen("Estado.txt", "w");//el apuntador jugadas se iguala a la creacion de un archivo de escritura llamado jugadas.txt si el archivo ya existe es destruido y recreado

origen=NULL;//igualacion de la torre origen a 0
torre1=NULL;//igualacion de la torre 1 a 0
torre2=NULL;//igualacion de la torre 2 a 0

    printf("        TORRES DE HANOI ");
    printf("\n\n¿Cuantos discos quiere usar?\n\nR:");
    scanf("%i",&d); //guardando el dato introducido por el usuario en variable d
    fprintf(estado,"\t\t\tTORRES DE HANOI SOLUCION\n\nSe van a mover %i discos de la torre 1 a la torre 2\n\n",d); //impresion del encabezado del archivo estado.txt que indica cuantos discos hay en uso

for(int i=d; i>0; i--){//inicio de un ciclo for empezando desde el numero de discos que se desea hasta llegar a 0
push1(i);}// introduccion de los discos deseados por el usuario del mayor a menor en la torre origen
hanoi(d); //llamado a la funcion que resuelve el algoritmo de la torres de hanoi
fclose(estado);//se cierra el archivo para imprimir los datos

getch();
system("cls");
printf("\t\tFin del Programa\n\n");
}

void push1(int v){ //inicio de la funcion push para ingresar datos en la torre origen recibiendo  como parametro el valor del disco
nodo *nuevo;   //creacion de un nuevo puntero a disco
nuevo = (nodo*)malloc(sizeof(nodo*)); //creacion de un nuevo disco
nuevo->valor = v; //asignacion del numero de disco al nuevo disco con el dato v recibido como parametro
nuevo->siguiente = origen; //el nuevo disco se enlaza arriba de el disco que anteriormente era el superior
origen = nuevo; //el nuevo disco se vuelve el disco superior
}

int pop1(){//inicio de la funcion para sacar un disco de la torre origen
nodo *aux; //creacion de un apuntador auxiliar
int v; //creacion de una nueva variable entera
aux = origen; //el puntero auxiliar recibe los datos del disco superior de la torre origen
    if(aux == NULL) //si en la linea anterior no se recibio ningun dato entonces
    return '\0'; //la funcion devuelve 0 y termina
    origen = aux->siguiente;//si no se cumple la condicion anterior se iguala la posicion del disco superior al siguiente disco
    v = aux->valor; //se guarda el valor del que anteriormente era el disco superior en la variable v
    free(aux);//se libera el que anteriormente era el disco superior
    return v;//envia el valor del que anteriormente era el disco superior afuera de la funcion hacia donde fue llamada
}

void push2(int v){ //inicio de la funcion push para ingresar datos en la torre1, funciona de manera similar que la funcion push1
nodo *nuevo;
nuevo = (nodo*)malloc(sizeof(nodo*));
nuevo->valor = v;
nuevo->siguiente = torre1;
torre1 = nuevo;
}

int pop2(){//inicio de la funcion para sacar un disco de la torre1, funciona similar que la funcion pop1
nodo *aux;
int v;
aux = torre1;
    if(aux == NULL)
    return '\0';
    torre1 = aux->siguiente;
    v = aux->valor;
    free(aux);
    return v;
}

void push3(int v){ //inicio de la funcion push para ingresar datos en la torre2, funciona de manera similar que la funcion push1
nodo *nuevo;
nuevo = (nodo*)malloc(sizeof(nodo*));
nuevo->valor = v;
nuevo->siguiente = torre2;
torre2 = nuevo;
}

int pop3(){//inicio de la funcion para sacar un disco de la torre2, funciona similar que la funcion pop1
nodo *aux;
int v;
aux = torre2;
    if(aux == NULL)
    return '\0';
    torre2 = aux->siguiente;
    v = aux->valor;
    free(aux);
    return v;
}

void hanoi(int d){ //inicio de la funcion que resuelve el algoritmo de las torres de hanoi recibiendo como parametro la cantidad de discos
    if(d==1){// si la cantidad de desciso es 1
    impresion(d);//llama a la funcion de impresion en pantalla
    fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 2",origen->valor);//imprime la jugada que esta por hacerse en el archivo estado.txt
    push3(pop3());//extrae el primer disco de origen y lo inserta en torre2
    impresion(d);//llama a la funcionde impresion en pantalla
    }//si se cumple esta condicion aqui termina la funcion de lo contrario:

else if(d==0){//si la cantidad de discos es 0
    printf("\n\nTORRES VACIAS");//imprime indicando que todas las torres estan vacias
    }//si se cumple esta condicion aqui termina la funcion de lo contrario:

else if(d%2==0){//si la cantidad de discos total es un numero par el algoritmo de resolucion es el siguiente:
impresion(d);//llama a la funcion de impresion en pantalla
fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 1",origen->valor);//imprime la jugada que esta por hacerse en el archivo estado.txt
push2(pop1());//extrae el disco mayor de origen y lo inserta en torre1
impresion(d);//llama a la funcion de impresion en pantalla
fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 2",origen->valor);//imprime la jugada que esta por hacerse en el archivo estado.txt
push3(pop1());//extrae el disco mayor de origen y lo inserta en torre2
impresion(d);//llama a la funcion de impresion en pantalla

do{//empieza el siguiente ciclo
movimientopar();//llama a la funcion movimiento par
impresion(d);//llama a la funcion de impresion en pantalla
general();//llama a la funcion de movimientos generales del algoritmo
impresion(d);//llama a la funcion de impresion en pantalla
}while(origen!=NULL || torre1!=NULL);//continua mietras las torres de origen y torre1 no esten vacias
}//si se cumple esta condicion aqui termina la funcion de lo contrario:

else if(d%2==1){//si la cantidad de discos total es un numero par el algoritmo de resolucion es el siguiente:
impresion(d);//llama a la funcion de impresion en pantalla
fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 2",origen->valor);//imprime la jugada que esta por hacerse en el archivo estado.txt
push3(pop1());
impresion(d);//llama a la funcion de impresion en pantalla
fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 1",origen->valor);//imprime la jugada que esta por hacerse en el archivo estado.txt
push2(pop1());
impresion(d);//llama a la funcion de impresion en pantalla

do{//empieza el siguiente ciclo
movimientoimpar();//llama a la funcion movimiento impar
impresion(d);//llama a la funcion de impresion en pantalla
general();//llama a la funcion de movimientos generales del algoritmo
impresion(d);//llama a la funcion de impresion en pantalla
}while(origen!=NULL || torre1!=NULL);//continua mietras las torres de origen y torre1 no esten vacias
}//esta es la ultima condicion posible
}//termina la funcion

void movimientopar(){//inicio de la funcion movimiento par
    if(origen!=NULL && origen->valor==1){//si la torre origen no esta vacia y suprimer disco es el disco 1 entonces
    fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 1",origen->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
    push2(pop1());//extrae el disco superior de origen y lo envia a torre1
    }//si se cumple esta condicion termina la funcion de lo contrario:

else  if(torre1!=NULL && torre1->valor==1){//si la torre auxiliar no esta vacia y suprimer disco es el disco 1 entonces

fprintf(estado, "\nMoviendo disco %i de la columna de torre 1 a columna de torre 2",torre1->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push3(pop2());//extrae el disco superior de torre1 y lo envia a torre2
}//si se cumple esta condicion termina la funcion de lo contrario:

else if(torre2!=NULL && torre2->valor==1){//si la torre destino no esta vacia y suprimer disco es el disco 1 entonces

fprintf(estado, "\nMoviendo disco %i de la columna de torre 2 a columna origen",torre2->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push1(pop3());//extrae el disco superior de torre2 y lo envia a origen
}//esta es la ultima condicion posible
}//fin de la funcion

void movimientoimpar(){//inicio de la funcion movimiento impar

if(origen!=NULL && origen->valor==1){//si la torre origen no esta vacia y su primer disco es el disco 1 entonces

fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 2",origen->valor);//imprime en el archivo jugada el movimiento que esta por realizase
push3(pop1());//extrae el disco superior de origen y lo envia a torre2
}//si se cumple esta condicion termina la funcion de lo contrario:

else  if(torre1!=NULL && torre1->valor==1){//si la torre auxiliar no esta vacia y su primer disco es el disco 1 entonces

fprintf(estado, "\nMoviendo disco %i de la columna de torre 1 a columna origen",torre1->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push1(pop2());//extrae el disco superior de torre1 y lo envia a origen
}//si se cumple esta condicion termina la funcion de lo contrario:

else if(torre2!=NULL && torre2->valor==1){//si la torre destino no esta vacia y su primer disco es el disco 1 entonces

fprintf(estado, "\nMoviendo disco %i de la columna de torre 2 a columna de torre 2",torre2->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push2(pop3());//extrae el disco superior de torre2 y lo envia a torre1
}//esta es la ultima condicion posible
}//fin de la funcion

int general(){//inicio de la funcion general
int a=0,b=0,c=0; //creacion de 3 variables enteras
    if(origen!=NULL)//si la torre origen no esta vacia entonces
    a=origen->valor;//se le asigna el valor del disco superior de origen a la variable a
    if(torre1!=NULL)//si la torre1 no esta vacia entonces
    b=torre1->valor;//se le asigna el valor del disco superior de torre1 a la variable b
    if(torre2!=NULL)//si la torre2 no esta vacia entonces
    c=torre2->valor;//se le asigna el valor del disco superior de torre2 a la variable c

    if(origen!=NULL && a>1){ //si la torre origen no esta vacia y su disco superior es mayor a 1

    if(torre1==NULL || a < b){//si la torre auxiliar esta vacia o su disco superior es menor al disco superior de origen
    fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 1",origen->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
    push2(pop1());//mueve el disco superior de origen a torre1
    return 0;//termina la funcion
    }//si no se cumple esta condicion:

else if(torre2==NULL || a < c){//si la torre destino esta vacia o su disco superior es menor al disco superior de origen

fprintf(estado, "\nMoviendo disco %i de la columna origen a columna de torre 2",origen->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push3(pop1());//mueve el disco superior de origen a torre2
return 0;//termina la funcion
}//esta es la ultima condicion posible dentro de la primera condicion
}//si esta primera condicion no se cumple entonces:

if(torre1!=NULL && b>1){//si la torre auxiliar no esta vacia y su disco superior es mayor a 1

if(origen==NULL || b < a){//si la torre origen esta vacia o su disco superior es menor al disco superior de torre1
fprintf(estado, "\nMoviendo disco %i de la columna de torre 1 a columna origen",torre1->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push1(pop2());//mueve el disco superior de torre1 a origen
return 0;//termina la funcion
}//si no se cumple esta condicion:

else if(torre2==NULL || b < c){//si la torre destino esta vacia o su disco superior es menor al disco superior de torre1
fprintf(estado, "\nMoviendo disco %i de la columna de torre 1 a columna de torre 2",torre1->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push3(pop2());//mueve el disco superior de torre1 a torre2
return 0;//termina la funcion
}//esta es la ultima condicion posible dentro de la segunda condicion
}

    if(torre2!=NULL && c>1){

    if(origen==NULL || c < a){//si la torre origen esta vacia o su disco superior es menor al disco superior de torre2
    fprintf(estado, "\nMoviendo disco %i de la columna de torre 2 a columna origen",torre2->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
    push1(pop3());//mueve el disco superior de torre2 a origen
    return 0;//termina la funcion
    }//si no se cumple esta condicion:

else  if(torre1==NULL || c < b){//si la torre auxiliar esta vacia o su disco superior es menor al disco superior de torre2
fprintf(estado, "\nMoviendo disco %i de la columna de torre 2 a columna de torre 1",torre2->valor);//imprime en el archivo jugada el movimiento que esta por realizarse
push2(pop3());//mueve el disco superior de torre2 a torre1
return 0;//termina la funcion
}//esta es la ultima condicion posible dentro de la tercera condicion
}//esta es la ultima condicion posible en la funcion
}//termina la funcion

void impresion(int d){//inicio de la funcion de impresion para imprimir las 3 torres en pantalla
system("cls");// limpieza de pantalla

int x=d,q=0,i=0,t=0,p=d;//creacion de varias variables tipo entero inicializando x y p con la cantidad total de discos y 1,i y t en 0
nodo *a,*b,*c,*y,*aux; //creacion de 5 apuntadores de tipo nodo

a=origen;//apuntador nodo a igualado a la torre origen
b=torre1;//apuntador nodo  b igualado a la torre 1
c=torre2;//apuntador nodo c igualado a la torre 2
y=NULL;//apuntador nodo y igualado a nulo

if(x==1 || x==2 || x==3){//en el caso de que la cantidad de discos sea 1,2 o 3
d=4; //d tendra un total de 4
x=d; //x tendra el mismo valor de d que es 4
p=d; //p tendra el mismo valor de d que es 4
}//si no se cumple esta condicion la funcion continua | esta condicion sirve para que si hay menos de 4 discos las torres no se impriman demasiado juntas

goxy(0,(x+1));//el apuntador se posicion en la posicion 0 en x y deciende la cantidad de espacios que de discos totales para poder imprimir cada disco en una posicion superior
printf("Origen");//imprime la posicion indicada

goxy(((2*x)+2),(x+1));//el apuntador se posicion en la posicion 2veces el total de discos en x para quedar junto a origen y deciende la cantidad de espacios que de discos totales para poder imprimir cada disco en una posicion superior
printf("Torre1");//imprime la posicion indicada

goxy((5*x),(x+1));//el apuntador se posicion en la posicion 2veces el total de discos en x para quedar junto a torre1 y deciende la cantidad de espacios que de discos totales para poder imprimir cada disco en una posicion superior
printf("Torre2");//imprime la posicion indicada

do{//inicia ciclo
if(a!=NULL){//si a no esta vacio
a=a->siguiente;//avanzara un disco
q++;}//y aumenta en 1 el valor de q para saber cuantos discos hay en esta pila
}while(a!=NULL);//termina cuando a sea nulo y ya no pueda avanzar

if(origen!=NULL){//en el caso de que origen no este vacio
a=origen;//a vuelve a apuntar al disco superior de origen
do{//inicia ciclo
nodo *nuevo;//se crea un apuntador nuevo de tipo nodo
nuevo = (nodo*)malloc(sizeof(nodo*));//se crea un nuevo nodo
nuevo->valor = a->valor;//el valor del nuevo nodo es el valor del disco superior de origen
nuevo->siguiente = y;//el siguiente enlace de nuevo apunta a y
y = nuevo;//y pasa a volverse nuevo
a=a->siguiente;//la copia de la torre origen avanza al siguiente disco
}while(a!=NULL);//hasta que se acabe la torre origen | esto sirve para vaciar la pila origen en otra pila pero en orden inverso para posteriormente poder leer de fin a principio

do{//inicia ciclo
goxy(t,x);//mueve el apuntador hacia t en x y x en y
x--;//le reduce uno a x para que enel siguiente ciclo apunte una fila arriba
t++;//le aumenta uno a t para que en el siguiente ciclo apunte a la siguiente columna

if(y!=NULL){//si y es diferente de nulo
i=y->valor;//i se toma el valor del disco superior de origen inverso
y=y->siguiente;//y apunta al siguiente disco

do{//inicia ciclo
printf("**");//imprime dos asteriscos por espacio
i--;//reduce en uno a la variable i que tiene el valor del disco que se esta imprimiendo
}while(i>0);//mientras i es mayor a 0 para imprimir la misma cantidad de asteriscos que el valor del disco en impresion
}//se cierra la condicional de si la torre inversa esta vacia
}while(x!=0);}//realizara todo este ciclo mientras el numero total de discos no decienda a 0

y=NULL;//el apuntador y se iguala a nada
t=0;//entero t vuelve a ser 0
x=d;//entero x vuelve a tener el valor total de discos
i=0;//entero i vuelve a ser 0
q=0;//entero q vuelve a ser 0

do{//inicia ciclo
if(b!=NULL){//si b no esta vacio
b=b->siguiente;//b apunta al siguiente disco
q++;}//q aumenta 1 | para saber cuantos discos tiene torre1
}while(b!=NULL);//hasta que b sea nulo

if(torre1!=NULL){//si auxiliar no esta vacio
b=torre1;//b vuelve a aumentar al disco superior de torre1

do{//inicio ciclo
nodo *nuevo;//se crea un nuevo apuntador tipo nodo
nuevo = (nodo*)malloc(sizeof(nodo*));//se crea un nuevo nodo al cual apunta el apuntador nuevo
nuevo->valor = b->valor;//el valor del nuevo nodo toma el valor del disco de b
nuevo->siguiente = y;//el siguiente disco al que apunta nuevo es el superior de y
y = nuevo;//y es igual al nuevo nodo
b=b->siguiente;//b ahora apunta al siguiente disco
}while(b!=NULL);//hasta que b ya esta nulo

do{//inicial ciclo
goxy(((2*p)+t+3),x);//mueve el apuntador en la fila al doble del espacio de donde sen ecncuentra la impresion de la torre origen mas 3 espacio para pocicionarse sobre la palabra torre1 mas t para moverse acorde al disco que corresponde y se mueve a x en y
x--;//x disminuye uno
t++;//t aumenta uno
if(y!=NULL){//si y es no esta vacio
i=y->valor;//i apunta al valor del disco superior de torre1
y=y->siguiente;//y apunta al siguiente disco

do{//inicia ciclo
printf("**");//imprime dos asteriscos por espacio
i--;//reduce uno a i
}while(i>0);//hasta que i sea 0 para imprimir la misma cantidad de asteriscos que el valor del disco en impresion
}
}while(x!=0);}//hasta que x sea igual a 0 y ya no queden discos para impresion

y=NULL;//y vuelve a ser nulo
t=0;//t vuelve a ser 0
x=d;//x vuelve a tener el valor total de discos
i=0;//i vuelve a ser 0
q=0;//q vuelve a ser 0

do{//inicia ciclo
if(c!=NULL){//si c no es nulo
c=c->siguiente;//c apunta al siguiente disco
q++;}//q aumenta uno para saber cuantos discos hay
}while(c!=NULL);//hasta que c sea nulo

if(torre2!=NULL){//si la torre destino es diferente de nulo entonces
c=torre2;//c apunta al disco superior de la torre2

do{//inicia ciclo
nodo *nuevo;//crea un apuntador de tipo nodo
nuevo = (nodo*)malloc(sizeof(nodo*));//el nuevo apuntador apunta a un nuevo nodo que es creado
nuevo->valor = c->valor;//el valor del nuevo nodo se iguala al valor del disco superior de torre2
nuevo->siguiente = y;//el nuevo nodo ahora apunta al disco superior de y
y = nuevo;//y ahora es igual al nuevo nodo
c=c->siguiente;//c apunta al siguiente disco
}while(c!=NULL);//hasta que c sea nulo para cambiar toda la pila de torre2 a una nueva pila pero posicionando los discos en orden inverso para poder imprimirla

t=1;//t ahora vale 1
do{//inicia el ciclo
goxy(((5*p)+t),x);//mueve el apuntador en la fila al quintuple del espacio de donde sen ecncuentra la impresion de la torre origen para posicionarse sobre la palabra torre1 mas t para moverse acorde al disco que corresponde y se mueve a x en y
x--;//x disminuye uno
t++;//t aumenta uno
if(y!=NULL){//si y no es nulo
i=y->valor;//i toma el valor del disco superior en y que es el disco inferior en torre2
y=y->siguiente;//y ahora apunta a su siguiente disco

do{//inicia ciclo
printf("**");//imprime dos asteriscos por espacio
i--;//i disminuye uno
}while(i>0);//hasta que i sea 0 para imprimir la misma cantidad de asteriscos que el valor del disco en impresion
}
}while(x!=0);}//hasta que x valga 0 y ya no allan mas discos para imprimir

Sleep(100);//el programa se detiene por 100 mili segundos
}//fin de la funcion
