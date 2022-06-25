// Tecnologico de Costa Rica - Proyecto 1A - Katerine Guzman Flores (2019390523) - Jose Pablo Aguero Mora (2021126372) - Prof: Victor Garro Abarca
// Main.cpp

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cctype> 
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sstream>
#include <random>
#include <cstdlib>

#include <string>
using namespace std;


double tiempo1, tiempo2, tiempo3, tiempo4, tiempo5, tiempo6, tiempo7, tiempo8, tiempo9, tiempo10, tiempo11, tiempo12, tiempo13, tiempo14, tiempo15, tiempo16;
bool borradoT = false;

// ***************************************************************** Funciones Lista Enlazada *******************************************************************
// **************************************************************************************************************************************************************


typedef struct T_Votante { //Se define la estructura para los votantes
	// Se establecen las variables char que almacenarán los datos separados del archivo txt y sus respectivos rangos de caracteres
	int codelec;
	char sexo;
	int fecha;;
	int numjun;
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	int cedula; // Se establecen las variables char que almacenarán los datos separados del archivo txt y sus respectivos rangos de caracteres
	T_Votante* PtrSiguiente; // Se indica un puntero que se dirige al siguiente nodo de la lista (a su dirección en memoria)
}*PtrT_Votante; // Puntero que apunta el primero de la lista de tipo T_Votante


//Funcion para liberar los votantes en estructuras de memoria dinamica de la lista enlazada hasta dejar la lista en NULL

void LiberarVotantes(PtrT_Votante& ListaV) {
	PtrT_Votante Aux = ListaV;
	ListaV = ListaV->PtrSiguiente;

	while (Aux != NULL) {
		ListaV = ListaV->PtrSiguiente;
		printf("\nBorro votante con cedula %i", Aux->cedula);
		delete(Aux);
		Aux = ListaV;
	}
}


PtrT_Votante BuscarVotante(PtrT_Votante& Lista, int cual)
{
	bool encontro = false; // Se establece un flag booleano en false
	PtrT_Votante Aux; // Se inicializa un puntero
	Aux = Lista; // Se le asigna la dirección del primer elemento en la lista

	while ((!encontro == true) && (Aux != NULL)) // Ciclo que recorre toda la lista hasta que encuentre el elemento o termine la lista
	{
		if (Aux->cedula == cual) // Condición en donde se encuentra el elemento
			encontro = true; // Cambia la variable flag a true
		else
			Aux = Aux->PtrSiguiente; // El otro caso donde no lo encuentra en el nodo actual entonces pasa a buscar al siguiente
	}
	return Aux; // Retorna la dirección del último nodo analizado, es decir, donde se encontró el elemento buscado
}

void ListarInventario(PtrT_Votante& ListaV)
{
	int Contador = 1;
	PtrT_Votante Aux; // variable local que servira para ir saltando de nodo en nodo
	Aux = ListaV; // Apunta donde apunta lista(primer elemento)
	if (Aux != NULL) {
		Aux = Aux->PtrSiguiente;
		while (Aux != NULL) // pregunta si se salio de la lista o esta vacia
		{
			// se imprime la informacion de cada pieza
			printf("\nCedula %i", Aux->cedula);
			printf("\nNombre %s", Aux->nombre);
			printf("\nPrimer Apellidoe %s", Aux->papellido);
			printf("\nSegundo Apellido %s", Aux->sapellido);
			printf("\nSexo");
			printf("\nCodigo elector %i", Aux->codelec);
			printf("\nFecha %i", Aux->fecha);
			printf("\nNumero de Junta %i", Aux->numjun);
			printf("\n");
			Aux = Aux->PtrSiguiente; // se pasa al siguiente nodo
			Contador++;
		}
	}

	else
	{
		printf("La lista se ha liberado");
		exit(0);
	}
}

// ***************************************************************** Funciones Arbol AVL *******************************************************************
// *********************************************************************************************************************************************************

struct Nodo
{
	int llave;
	Nodo* izq;
	Nodo* derecha;
	int codelec;
	char sexo;
	int fecha;
	int numjun;
	char* nombre;
	char* papellido;
	char* sapellido;
	int altura;
};

void agregarvotante(PtrT_Votante& ListaV, char agregado[118]) {
	PtrT_Votante Aux = new (T_Votante); // Se usa el puntero como un auxiliar que apunta a una nueva variable anónima de tipo T_Votante
	Aux->PtrSiguiente = ListaV; // Se le asigna a siguiente el primer elemento al que apunta en la lista
	ListaV = Aux; // Al primer nodo apuntado de la lista se le asigna la dirección del nuevo nodo

	// SACAR CEDULA Y PASARLA A ENTERO
	char cedula2[10];
	char codigoElect[7];
	char sexo2[17];
	char fecha2[9];
	char numjun2[6];
	char nombre2[31];

	for (int ce = 0; ce < 9; ce++) { // Ciclo que toma desde el caracter 0 hasta el caracter 9. Lo almacena en cedula
		cedula2[ce] = agregado[ce]; // Se agrega caracter por caracter
	}
	cedula2[9] = '\0'; // String terminator

	// pasa a entero la cedula para meterla a funcion insertar arbol binario
	int numeroA;
	sscanf_s(cedula2, "%d", &numeroA);
	// Se asigna numero a cedula
	ListaV->cedula = numeroA;


	// ****************************************************//
	for (int co = 10; co < 16; co++) { // Ciclo que toma desde el caracter 10 hasta el caracter 16. Lo almacena en codelec
		codigoElect[co - 10] = agregado[co];
	}
	codigoElect[6] = '\0';

	int numeroElect;
	sscanf_s(codigoElect, "%d", &numeroElect);
	// Se asigna numero a cedula
	ListaV->codelec = numeroElect;

	ListaV->sexo = agregado[17]; // Se agrega únicamente el caracter 17 al valor de sexo. Lo almacena en sexo

	// FECHA
	for (int fe = 19; fe < 27; fe++) { // Ciclo que toma desde el caracter 19 hasta el caracter 27. Lo almacena en fecha
		fecha2[fe - 19] = agregado[fe];
	}
	fecha2[8] = '\0'; // String terminator

	int numFecha;
	sscanf_s(fecha2, "%d", &numFecha);
	// Se asigna numero a cedula
	ListaV->fecha = numFecha;

	// NUMERO JUNTA
	for (int nu = 28; nu < 33; nu++) { // Ciclo que toma desde el caracter 28 hasta el caracter 33. Lo almacena numjun
		numjun2[nu - 28] = agregado[nu];
	}
	numjun2[5] = '\0'; // String terminator

	int junta;
	sscanf_s(numjun2, "%d", &junta);
	// Se asigna numero a cedula
	ListaV->numjun = junta;

	// nombre
	for (int nom = 34; nom < 64; nom++) { // Ciclo que toma desde el caracter 34 hasta el caracter 64. Lo almacena en nombre
		ListaV->nombre[nom - 34] = agregado[nom];
	}
	ListaV->nombre[30] = '\0'; // String terminator

	for (int pa = 65; pa < 91; pa++) { // Ciclo que toma desde el caracter 65 hasta el caracter 91. Lo almacena en papellido
		ListaV->papellido[pa - 65] = agregado[pa];
	}
	ListaV->papellido[26] = '\0'; // String terminator

	for (int sa = 92; sa < 118; sa++) { // Ciclo que toma desde el caracter 92 hasta el caracter 118. Lo almacena en sapellido
		ListaV->sapellido[sa - 92] = agregado[sa];
	}
	ListaV->sapellido[26] = '\0'; // String terminator


}

void CargarVotantes(PtrT_Votante& ListaV) {
	int cont = 1;

	FILE* archivo; // Se declara un puntero para manejar los datos del archivo
	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r"); // Se abre el txt con la función de leer ("r")
	if (NULL == archivo) { // Condición en caso de que no exista el archivo o no se pueda abrir
		printf("No se pudo abrir el archivo");
	}
	else { // Caso en el que sí existe el archivo txt
		char agregado[119]; // Se crea una variable de tipo char que contendrá cada línea del archivo txt (una por una)
		while (fgets(agregado, 119, archivo) != NULL) { // Ciclo para recorrer todas las líneas del txt y cargar datos en variable agregado
			if (cont % 2 != 0) { // Esta instrucción existe por una ineficiencia del código que leía de forma duplicada a los votantes / Esto evita que se repitan
				agregarvotante(ListaV, agregado); // Utiliza los datos cargador en agregado para pasarlos como parámetro a agregarvotante()
			}
			cont++; // Aumenta el contador
		}
		fclose(archivo); // Cierra el uso de la variable archivo al txt
	}
}

//obtiene el maximo de dos numeros
int max(int a, int b);

//obtiene la altura del arbol
int altura(struct Nodo* N)
{
	if (N == NULL)
		return 0;
	return N->altura;
}


int max(int a, int b)
{
	return (a > b) ? a : b;
}


struct Nodo* nuevoNodo(int llave, int codelec, int fecha, int numjun, char* nombreX, char* papellidoX, char* sapellidoX, char sexo)
{
	struct Nodo* Nodo = (struct Nodo*)
		malloc(sizeof(struct Nodo));
	Nodo->llave = llave;
	Nodo->izq = NULL;
	Nodo->derecha = NULL;
	Nodo->altura = 1;  //nuevonodo es agregado como hoja
	Nodo->codelec = codelec;
	Nodo->fecha = fecha;
	Nodo->numjun = numjun;
	Nodo->nombre = nombreX;
	Nodo->sexo = sexo;
	Nodo->papellido = papellidoX;
	Nodo->sapellido = sapellidoX;
	return(Nodo);
}


struct Nodo* RotarDerecha(struct Nodo* y)
{
	struct Nodo* x = y->izq;
	struct Nodo* T2 = x->derecha;

	// hace rotacion
	x->derecha = y;
	y->izq = T2;

	// actualiza alturas
	y->altura = max(altura(y->izq), altura(y->derecha)) + 1;
	x->altura = max(altura(x->izq), altura(x->derecha)) + 1;

	// retorna nueva raiz
	return x;
}


struct Nodo* RotarIzquierda(struct Nodo* x)
{
	struct Nodo* y = x->derecha;
	struct Nodo* T2 = y->izq;

	// hace rotacion
	y->izq = x;
	x->derecha = T2;

	//  actualiza alturas
	x->altura = max(altura(x->izq), altura(x->derecha)) + 1;
	y->altura = max(altura(y->izq), altura(y->derecha)) + 1;

	// retorna nueva raiz
	return y;
}

// obtiene balance
int obtenerbalance(struct Nodo* N)
{
	if (N == NULL)
		return 0;
	return altura(N->izq) - altura(N->derecha);
}


struct Nodo* insertarAVL(struct Nodo* Nodo, int llave, int codelec, int fecha, int numjun, char* nombre, char* papellido, char* sapellido, char sexo)
{
	if (Nodo == NULL)
		return(nuevoNodo(llave, codelec, fecha, numjun, nombre, papellido, sapellido, sexo));

	if (llave < Nodo->llave)
		Nodo->izq = insertarAVL(Nodo->izq, llave, codelec, fecha, numjun, nombre, papellido, sapellido, sexo);
	else if (llave > Nodo->llave)
		Nodo->derecha = insertarAVL(Nodo->derecha, llave, codelec, fecha, numjun, nombre, papellido, sapellido, sexo);
	else // no se permiten llaves iguales
		return Nodo;

	/* 2. actualiza altura */
	Nodo->altura = 1 + max(altura(Nodo->izq),
		altura(Nodo->derecha));

	/* 3. verifica si el arbol se desbalancea */
	int balance = obtenerbalance(Nodo);

	// 4 casos para un arbol desbalanceado

	// izq izq 
	if (balance > 1 && llave < Nodo->izq->llave)
		return RotarDerecha(Nodo);

	// derecha derecha 
	if (balance < -1 && llave > Nodo->derecha->llave)
		return RotarIzquierda(Nodo);

	// izq derecha 
	if (balance > 1 && llave > Nodo->izq->llave)
	{
		Nodo->izq = RotarIzquierda(Nodo->izq);
		return RotarDerecha(Nodo);
	}

	// derecha izq 
	if (balance < -1 && llave < Nodo->derecha->llave)
	{
		Nodo->derecha = RotarDerecha(Nodo->derecha);
		return RotarIzquierda(Nodo);
	}

	return Nodo;
}

//recorido
void preOrder(struct Nodo* Raiz)
{
	if (Raiz != NULL)
	{
		cout << "Cedula: " << Raiz->llave << endl; // Imprime los valores de los nodos
		cout << "Nombre: " << Raiz->nombre << endl;
		cout << "Primer apellido: " << Raiz->papellido << endl;
		cout << "Segundo apellido: " << Raiz->sapellido << endl;
		cout << "Sexo: " << endl;
		cout << "Fecha: " << Raiz->fecha << endl;
		cout << "Codigo electorial: " << Raiz->codelec << endl;
		cout << "Numero junta: " << Raiz->numjun << endl;
		printf("\n ");
		preOrder(Raiz->izq);
		preOrder(Raiz->derecha);
	}

}


//returna la informacion del votante si existe en el arbol buscado 

Nodo* BuscaCedulaAVL(Nodo* Raiz, int llave)
{
	time_t inicio, fin; // Se declaran variables de tipo tiempo para medir la duración del proceso
	inicio = time(NULL); // Declaración de variable para medir el tiempo inicial
	if (Raiz == NULL)
	{
		cout << "No se ha encontrado al votante " << endl;
		return NULL;
	}
	else
	{
		if (llave == Raiz->llave) {
			cout << "Cedula: " << Raiz->llave << endl; // Imprime los valores de los nodos
			cout << "Nombre: " << Raiz->nombre << endl;
			cout << "Primer apellido: " << Raiz->papellido << endl;
			cout << "Segundo apellido: " << Raiz->sapellido << endl;
			cout << "Sexo: " << Raiz->sexo << endl;
			cout << "Fecha: " << Raiz->fecha << endl;
			cout << "Codigo electorial: " << Raiz->codelec << endl;
			cout << "Numero junta: " << Raiz->numjun << endl;
			return Raiz;
		}
		else
			if (llave < Raiz->llave)
				return BuscaCedulaAVL(Raiz->izq, llave);
			else
				return BuscaCedulaAVL(Raiz->derecha, llave);
	}
	cout << "------------------------------------------------------Votante Encontrado en Arbol AVL-------------------------------------------------" << endl;
	printf("\nSe ha tardado : %f segundos.\n", difftime(fin, inicio));
}

void AVLPodarHojas(Nodo*& Raiz) // mata los de la izquierda, derecha y raiz
{
	if (Raiz != NULL) // caso continuidad
	{
		AVLPodarHojas(Raiz->izq); // I poda los menores
		AVLPodarHojas(Raiz->derecha); // D poda los mayores
		printf("Borro votante con cedula : %i\n", Raiz->llave); // 
		delete(Raiz);
		Raiz = NULL; // R borra la raiz y dejo puntero apuntando a null para que arbol se mantenga consistente
	}
}

// *************************************************************** ABB ****************************************************************

typedef struct NodoBB
{
	int llave; // valor o codigo unico
	int codelec;
	int sexo;
	int fecha;
	int numjun;
	char* nombre;
	char* papellido;
	char* sapellido;
	NodoBB* HijoIzquierdo; // puntero al subarbol de la izquierda
	NodoBB* HijoDerecho; // puntero al subarbol de la derecha
}X;

// ced, num elector, sexo, fecha, num junta, nombre, ape1, apelli2
bool Insertar(NodoBB*& Raiz, int cualllave, int codElector, int fechaV, int juntaN, char* nombre, char* papellido, char* sapellido, char sexo)
{
	if (Raiz == NULL) // si no esta apuntando a nadie es porque no se ha inicializado
	{
		Raiz = new(NodoBB); // raiz que apuntaba a nuill ahora adopta el valor de una variable anonima con estructura nodobb
		// una vez creada se inicializan los datos
		Raiz->llave = cualllave;
		Raiz->codelec = codElector;
		Raiz->fecha = fechaV;
		Raiz->numjun = juntaN;
		Raiz->nombre = nombre;
		Raiz->sexo = sexo;
		Raiz->papellido = papellido;
		Raiz->sapellido = sapellido;
		Raiz->HijoIzquierdo = NULL; // asigna hijos en null para inicializarlos
		Raiz->HijoDerecho = NULL;
		return true;
	}
	else // caso continuidad
	{
		if (cualllave == Raiz->llave) return false; // si ya existe la llave y retorna false
		else
			if (cualllave < Raiz->llave) return Insertar(Raiz->HijoIzquierdo, cualllave, codElector, fechaV, juntaN, nombre, papellido, sapellido, sexo);
			else return Insertar(Raiz->HijoDerecho, cualllave, codElector, fechaV, juntaN, nombre, papellido, sapellido, sexo);
	}
}


void InsertarTodos(PtrT_Votante& ListaV, NodoBB*& Arbol) {
	PtrT_Votante Aux = ListaV; // Se crea una variable auxiliar para recorrer la lista enlazada
	//Aux = Aux->PtrSiguiente;
	while (Aux != NULL) { // Ciclo que se repite hasta que la lista enlazada no tenga más nodos
		Insertar(Arbol, Aux->cedula, Aux->codelec, Aux->fecha, Aux->numjun, Aux->nombre, Aux->papellido, Aux->sapellido, Aux->sexo);
		Aux = Aux->PtrSiguiente; // Apunta al siguiente nodo en la lista
	}
}


NodoBB* ABBBuscar(NodoBB* Raiz, int cualllave)
{
	if (Raiz == NULL) // caso base, puede ser la raiz principal o cualquiera de las otras raices porque la raiz va adoptando diferentes valores
	{
		return NULL; // null cuando se sale del rango
	}
	else
	{
		if (cualllave == Raiz->llave) return Raiz; // caso base 2: retorna la direccion donde se da la igualdad
		else
			if (cualllave < Raiz->llave) return ABBBuscar(Raiz->HijoIzquierdo, cualllave); //cualllave < Raiz-> entonces inserta en izquierda
			else return ABBBuscar(Raiz->HijoDerecho, cualllave);
	}
}

void PodarHojas(NodoBB*& Raiz) // mata los de la izquierda, derecha y raiz
{
	if (Raiz != NULL) // caso continuidad
	{
		PodarHojas(Raiz->HijoIzquierdo); // I poda los menores
		PodarHojas(Raiz->HijoDerecho); // D poda los mayores
		printf("Borro votante con cedula: %i \n", Raiz->llave); // 
		delete(Raiz);
		Raiz = NULL; // R borra la raiz y dejo puntero apuntando a null para que arbol se mantenga consistente
	}
}

void EnOrdenIRD(NodoBB* Raiz) // I R D
{ // si sale del rango ya empieza a retornar

	if (Raiz != NULL) // caso continuidad
	{
		EnOrdenIRD(Raiz->HijoIzquierdo);
		cout << "Cedula: " << Raiz->llave << endl; // Imprime los valores de los nodos
		cout << "Nombre: " << Raiz->nombre << endl;
		cout << "Primer apellido: " << Raiz->papellido << endl;
		cout << "Segundo apellido: " << Raiz->sapellido << endl;
		cout << "Sexo: " << endl;
		cout << "Fecha: " << Raiz->fecha << endl;
		cout << "Codigo electorial: " << Raiz->codelec << endl;
		cout << "Numero junta: " << Raiz->numjun << endl;
		printf("\n ");
		EnOrdenIRD(Raiz->HijoDerecho);
	}
}


void ABBEncontrarVotante(NodoBB* Raiz, int val) {

	NodoBB* Aux;
	// if ((Aux = BuscarVotante(ListaV, val)) != NULL) printf("\nBusco %i y encontro %i, nombre %s, papellido %s, sapellido %s ", val, Aux->cedula, Aux->nombre, Aux->papellido, Aux->sapellido);
	if ((Aux = ABBBuscar(Raiz, val)) != NULL)
	{
		printf("\nBusco %i y encontro %i", val, Aux->llave);
		printf("\nNombre %s", Aux->nombre);
		printf("\nPrimer Apellidoe %s", Aux->papellido);
		printf("\nSegundo Apellido %s", Aux->sapellido);
		printf("\nCodigo elector %i", Aux->codelec);
		printf("\nFecha %i", Aux->fecha);
		printf("\nNumero de Junta %i", Aux->numjun);
		printf("\n");
	}
	else {
		printf("\nNo se ha encontrado al votante ");
		printf("\n");
	}

}


// ************************************************************************** BTree ***************************************************************************

#define MAX 4
#define MIN 2

struct NodoBtree {
	int val[MAX + 1], count;
	NodoBtree* link[MAX + 1];

};

NodoBtree* BTree;


//Crear nodo 
NodoBtree* crearnodo(int val, NodoBtree* hijo) {
	NodoBtree* NuevoNodo = new NodoBtree;
	NuevoNodo->val[1] = val;
	NuevoNodo->count = 1;
	NuevoNodo->link[0] = BTree;
	NuevoNodo->link[1] = hijo;
	return NuevoNodo;
}

//coloca el nodo en la posicion adecuada, de acuerdo a su valor
void Colocarnodo(int val, int pos, NodoBtree* node, NodoBtree* hijo) {
	int j = node->count;
	while (j > pos) {
		node->val[j + 1] = node->val[j];
		node->link[j + 1] = node->link[j];
		j--;
	}
	node->val[j + 1] = val;
	node->link[j + 1] = hijo;
	node->count++;
}


void PartirNodo(int val, int* pval, int pos, NodoBtree* node, NodoBtree* hijo, NodoBtree** NuevoNodo) {
	int median, j;

	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*NuevoNodo = new NodoBtree;
	j = median + 1;
	while (j <= MAX) {
		(*NuevoNodo)->val[j - median] = node->val[j];
		(*NuevoNodo)->link[j - median] = node->link[j];
		j++;
	}
	node->count = median;
	(*NuevoNodo)->count = MAX - median;

	if (pos <= MIN) {
		Colocarnodo(val, pos, node, hijo);
	}
	else {
		Colocarnodo(val, pos - median, *NuevoNodo, hijo);
	}
	*pval = node->val[node->count];
	(*NuevoNodo)->link[0] = node->link[node->count];
	node->count--;
}

//colocar valor
int SetValorNodo(int val, int* pval, NodoBtree* node, NodoBtree** hijo) {

	int pos;
	if (!node) {
		*pval = val;
		*hijo = NULL;
		return 1;
	}

	if (val < node->val[1]) {
		pos = 0;
	}
	else {
		for (pos = node->count;
			(val < node->val[pos] && pos > 1); pos--);
		if (val == node->val[pos]) {
			cout << "No está permitido nodos duplicados\n";
			return 0;
		}
	}
	if (SetValorNodo(val, pval, node->link[pos], hijo)) {
		if (node->count < MAX) {
			Colocarnodo(*pval, pos, node, *hijo);
		}
		else {
			PartirNodo(*pval, pval, pos, node, *hijo, hijo);
			return 1;
		}
	}
	return 0;
}

//inserta valores en el btree
void BTreeinsertar(PtrT_Votante& ListaV, int val) {
	int flag, i;
	NodoBtree* hijo;

	flag = SetValorNodo(val, &i, BTree, &hijo);
	if (flag)
		BTree = crearnodo(i, hijo);
}

void BTreeInsertarTodos(PtrT_Votante& ListaV, NodoBtree*& Arbol) {
	PtrT_Votante Aux = ListaV; // Se crea una variable auxiliar para recorrer la lista enlazada

	Aux = Aux->PtrSiguiente;
	while (Aux != NULL) { // Ciclo que se repite hasta que la lista enlazada no tenga más nodos
		BTreeinsertar(ListaV, Aux->cedula);
		Aux = Aux->PtrSiguiente; // Apunta al siguiente nodo en la lista
	}
}

//copia el sucesor del nodo que será borrado
void copySuccessor(NodoBtree* minodo, int pos) {
	NodoBtree* dummy;
	dummy = minodo->link[pos];

	for (; dummy->link[0] != NULL;)
		dummy = dummy->link[0];
	minodo->val[pos] = dummy->val[1];

}

//remueve un valor de un nodo y reacomoda el arbol
void removeVal(NodoBtree* minodo, int pos) {
	int i = pos + 1;
	while (i <= minodo->count) {
		minodo->val[i - 1] = minodo->val[i];
		minodo->link[i - 1] = minodo->link[i];
		i++;
	}
	minodo->count--;
}

//shift a la derecha
void doRightShift(NodoBtree* minodo, int pos) {
	NodoBtree* x = minodo->link[pos];
	int j = x->count;

	while (j > 0) {
		x->val[j + 1] = x->val[j];
		x->link[j + 1] = x->link[j];
	}
	x->val[1] = minodo->val[pos];
	x->link[1] = x->link[0];
	x->count++;

	x = minodo->link[pos - 1];
	minodo->val[pos] = x->val[x->count];
	minodo->link[pos] = x->link[x->count];
	x->count--;
	return;
}

//shift a la izquierda
void doLeftShift(NodoBtree* minodo, int pos) {
	int j = 1;
	NodoBtree* x = minodo->link[pos - 1];

	x->count++;
	x->val[x->count] = minodo->val[pos];
	x->link[x->count] = minodo->link[pos]->link[0];

	x = minodo->link[pos];
	minodo->val[pos] = x->val[1];
	x->link[0] = x->link[1];
	x->count--;

	while (j <= x->count) {
		x->val[j] = x->val[j + 1];
		x->link[j] = x->link[j + 1];
		j++;
	}
	return;
}

//Fusionar nodos
void UnirNodos(NodoBtree* minodo, int pos) {
	int j = 1;
	NodoBtree* x1 = minodo->link[pos], * x2 = minodo->link[pos - 1];

	x2->count++;
	x2->val[x2->count] = minodo->val[pos];
	x2->link[x2->count] = minodo->link[0];

	while (j <= x1->count) {
		x2->count++;
		x2->val[x2->count] = x1->val[j];
		x2->link[x2->count] = x1->link[j];
		j++;
	}

	j = pos;
	while (j < minodo->count) {
		minodo->val[j] = minodo->val[j + 1];
		minodo->link[j] = minodo->link[j + 1];
		j++;
	}
	minodo->count--;
	free(x1);
}

//Ajusta el nodo dado
void AjustarNodo(NodoBtree* minodo, int pos) {
	if (!pos) {
		if (minodo->link[1]->count > MIN) {
			doLeftShift(minodo, 1);
		}
		else {
			UnirNodos(minodo, 1);
		}
	}
	else {
		if (minodo->count != pos) {
			if (minodo->link[pos - 1]->count > MIN) {
				doRightShift(minodo, pos);
			}
			else {
				if (minodo->link[pos + 1]->count > MIN) {
					doLeftShift(minodo, pos + 1);
				}
				else {
					UnirNodos(minodo, pos);
				}
			}
		}
		else {
			if (minodo->link[pos - 1]->count > MIN)
				doRightShift(minodo, pos);
			else
				UnirNodos(minodo, pos);
		}
	}
}

//borrar un valor del nodo
int BorrarDeNodo(int val, NodoBtree* minodo) {
	int pos, flag = 0;
	if (minodo) {
		if (val < minodo->val[1]) {
			pos = 0;
			flag = 0;
		}
		else {
			for (pos = minodo->count;
				(val < minodo->val[pos] && pos > 1); pos--);
			if (val == minodo->val[pos]) {
				flag = 1;
			}
			else {
				flag = 0;
			}
		}
		if (flag) {
			if (minodo->link[pos - 1]) {
				copySuccessor(minodo, pos);
				flag = BorrarDeNodo(minodo->val[pos], minodo->link[pos]);
				if (flag == 0) {
					cout << "No existe en el B-Tree\n";
				}
			}
			else {
				removeVal(minodo, pos);
			}
		}
		else {
			flag = BorrarDeNodo(val, minodo->link[pos]);
		}
		if (minodo->link[pos]) {
			if (minodo->link[pos]->count < MIN)
				AjustarNodo(minodo, pos);
		}
	}
	return flag;
}

/* delete val from B-tree */
void borrado(int val, NodoBtree* minodo) {
	NodoBtree* tmp;
	if (!BorrarDeNodo(val, minodo)) {
		cout << "No existe ese valor en el B-Tree\n";
		system("pause");
		return;
	}
	else {
		if (minodo->count == 0) {
			tmp = minodo;
			minodo = minodo->link[0];
			free(tmp);
		}
	}
	BTree = minodo;
	cout << "Se ha borrado el votante" << endl;
	system("pause");
	return;
}

/* search val in B-Tree */
void busqueda(int val, int* pos, NodoBtree* minodo) {
	if (minodo == NULL) {
		cout << "No se ha encontrado el Nodo\n";
	}

	if (!minodo) {
		return;
	}

	if (val < minodo->val[1]) {
		*pos = 0; // *pos
	}
	else {
		for (*pos = minodo->count;
			(val < minodo->val[*pos] && *pos > 1); (*pos)--);
		if (val == minodo->val[*pos]) {

			cout << "Se ha encontrado la cedula: ";
			cout << minodo->val[*pos] << ' ';
			cout << "\n";
			return;
		}
	}
	busqueda(val, pos, minodo->link[*pos]);
	cout << "No se ha encontrado el Nodo\n";
	return;
}

/* search val in B-Tree /
void busqueda(int val, int *pos, NodoBtree *minodo) {
	if (!minodo) {
		return;
	}

	if (val < minodo->val[1]) {
		pos = 0;
	}
	else {
		for (pos = minodo->count;
			(val < minodo->val[pos] &&pos > 1); (pos)--);
		if (val == minodo->val[pos]) {
			cout << "Se ha encontrado el Nodo\n";
			system("pause");
			return;
		}
	}
	busqueda(val, pos, minodo->link[*pos]);
	cout << "No se ha encontrado el Nodo\n";
	system("pause");
	return;
} */

// B-Tree desplegar
void desplegar(NodoBtree* minodo) {
	int i;
	if (minodo) {
		for (i = 0; i < minodo->count; i++) {
			desplegar(minodo->link[i]);
			cout << minodo->val[i + 1] << ' ';
			cout << "\n";
		}
		desplegar(minodo->link[i]);
	}
}


// B-Tree desplegar
void borrarBTree(NodoBtree* minodo) {
	int i;
	if (minodo) {
		for (i = 0; i < minodo->count; i++) {
			borrarBTree(minodo->link[i]);
			cout << "Borro votante con cedula: " << minodo->val[i + 1] << ' ';
			//borrado(minodo->val[i + 1], minodo);
			delete(minodo->link[i]);
			cout << "\n";
		}
		borrarBTree(minodo->link[i]);
	}
}

//******************************************************************** MAIN *************************************************************************
//***************************************************************************************************************************************************

int main()
{// Inicializacion de los arboles
	PtrT_Votante ListaV = NULL;
	PtrT_Votante Encontrado = NULL;
	NodoBB* ArbolBinario = NULL;

	// ******************************************************** Cargar Padron de Votantes ********************************************************
	cout << "Por favor espere mientras se carga el Padron" << endl;
	time_t inicioC, finC; // Se declaran variables de tipo tiempo para medir la duración del proceso
	inicioC = time(NULL); // Declaración de variable para medir el tiempo inicial
	CargarVotantes(ListaV);
	finC = time(NULL);
	cout << "---------------------------------------------------------Padron Cargado--------------------------------------------------------" << endl;
	printf("\nCargar el padron ha tardado : %f segundos.\n", difftime(finC, inicioC));
	tiempo1 = difftime(finC, inicioC);
	printf("\n ");
	printf("\n ");

	// ***************************** Insertar ABB **********************************
	PtrT_Votante Aux1 = ListaV;
	time_t ABIinicio, ABIfin;
	ABIinicio = time(NULL);
	InsertarTodos(Aux1, ArbolBinario);
	ABIfin = time(NULL);
	cout << "-------------------------------------------------Padron Insertado en Arbol ABB-----------------------------------------------" << endl;
	printf("\nLa insercion del padron en Arbol ABB ha tardado : %f segundos.\n", difftime(ABIfin, ABIinicio));
	tiempo2 = difftime(ABIfin, ABIinicio);
	printf("\n ");
	printf("\n ");


	// ******************************** Insertar BTree ***************************
	PtrT_Votante Aux2 = ListaV;
	time_t inicioBBT, finBBT;
	inicioBBT = time(NULL);
	BTreeInsertarTodos(Aux2, BTree);
	finBBT = time(NULL);
	cout << "----------------------------------------------Padron Insertado en Arbol BTree-------------------------------------------------" << endl;
	printf("\nLa insercion del padron en Arbol BTree ha tardado : %f segundos.\n", difftime(finBBT, inicioBBT));
	tiempo3 = difftime(finBBT, inicioBBT);
	printf("\n ");
	printf("\n ");

	// ***************************** Insertar en Arbol AVL *************************

	time_t inicio, fin;
	inicio = time(NULL);
	struct Nodo* root = NULL;
	PtrT_Votante Aux3 = ListaV;
	Aux3 = Aux3->PtrSiguiente;


	while (Aux3 != NULL) {
		root = insertarAVL(root, Aux3->cedula, Aux3->codelec, Aux3->fecha, Aux3->numjun, Aux3->nombre, Aux3->papellido, Aux3->sapellido, Aux3->sexo);
		Aux3 = Aux3->PtrSiguiente;

	}
	fin = time(NULL);

	cout << "------------------------------------------------Padron Insertado en Arbol AVL-------------------------------------------------" << endl;
	printf("\nLa insercion del padron en Arbol AVL ha tardado : %f segundos.\n", difftime(fin, inicio));
	tiempo4 = difftime(fin, inicio);
	system("pause");


	int val, opt, codi;
	char cedula[10];

	while (true) {
		system("CLS");

		printf(" Padron Electoral ");
		printf("\n");

		cout << " 1. Buscar\n";
		cout << " 2. Listar\n";
		cout << " 3. Liberar\n";
		cout << " 4. Reporte de Tiempos \n";
		cout << " 5. Salir \n\n";
		cout << " Ingrese una opcion: ";

		cin >> opt;
		cout << endl;
		switch (opt) {

		case 1: // Buscar

			cout << "Cual cedula desea buscar:";
			cin >> val;
			printf("\n ");

			// Busqueda en Lista Enlazada
			cout << "--------------------------------------------------Busqueda en Lista Enlazada-------------------------------------------------" << endl;
			time_t inicio, fin;
			inicio = time(NULL);
			printf("\n ");
			Encontrado = BuscarVotante(ListaV, val);
			if (Encontrado != NULL) {
				cout << endl << "Encontre al Votante!! " << endl << endl;

				cout << "Cedula: " << Encontrado->cedula << endl;
				cout << "Nombre: " << Encontrado->nombre << endl;
				cout << "Primer Apellido: " << Encontrado->papellido << endl;
				cout << "Segundo Apellido: " << Encontrado->sapellido << endl;
				cout << "Sexo: " << Encontrado->sexo << endl;
				cout << "Fecha: " << Encontrado->fecha << endl;
				cout << "Codigo Electoral:  " << Encontrado->codelec << endl;
				cout << "Numero Junta: " << Encontrado->numjun << endl;
			}
			else
				cout << " No se encontro al votante !!! " << endl;
			printf("\n ");
			fin = time(NULL);
			printf("\Buscar el votante en Lista Enlazada ha tardado: %f segundos.\n", difftime(fin, inicio));
			tiempo5 = difftime(fin, inicio);
			printf("\n ");
			printf("\n");
			printf("\n ");

			// Busqueda Arbol AVL
			cout << "------------------------------------------------Busqueda en Arbol AVL-------------------------------------------------------" << endl;
			time_t inicioA, finA;
			inicioA = time(NULL);
			printf("\n ");
			BuscaCedulaAVL(root, val);
			printf("\n ");
			finA = time(NULL);
			printf("\Buscar el votante en Arbol AVL ha tardado: %f segundos.\n", difftime(finA, inicioA));
			tiempo6 = difftime(finA, inicioA);
			printf("\n ");
			printf("\n");
			printf("\n ");

			// Busqueda en ABB
			cout << "------------------------------------------------Busqueda en ABB-------------------------------------------------------" << endl;
			time_t LEinicio, LEfin;
			LEinicio = time(NULL);
			ABBEncontrarVotante(ArbolBinario, val);
			printf("\n ");
			LEfin = time(NULL);
			printf("\Buscar el votante en ABB ha tardado: %f segundos.\n", difftime(LEfin, LEinicio));
			tiempo7 = difftime(LEfin, LEinicio);
			printf("\n ");
			printf("\n");
			printf("\n ");

			cout << "------------------------------------------------Busqueda en Arbol BTree-------------------------------------------------------" << endl;
			time_t BTinicio, BTfin;
			BTinicio = time(NULL);
			printf("\n ");
			busqueda(val, &opt, BTree);
			printf("\n ");
			BTfin = time(NULL);
			printf("\Buscar el votante en BTree ha tardado: %f segundos.\n", difftime(BTfin, BTinicio));
			tiempo8 = difftime(BTfin, BTinicio);
			printf("\n ");
			system("pause");

			break;

		case 2:
			if (borradoT == false) {
				// Lista Enlazada
				cout << "---------------------------------------------Padron Listado en Lista Enlazada--------------------------------------------------" << endl;
				time_t inicioLi, finLi;
				inicioLi = time(NULL);
				ListarInventario(ListaV);
				printf("\n ");
				finLi = time(NULL);
				printf("\nPadron Listado en Lista Enlazada ha tardado: %f segundos.\n", difftime(finLi, inicioLi));
				tiempo9 = difftime(finLi, inicioLi);
				printf("\n ");
				printf("\n ");
				printf("\n ");

				// Listar Arbol AVL
				cout << "-------------------------------------------------Padron Listado en Arbol AVL-------------------------------------------------" << endl;
				time_t inicioL, finL;
				inicioL = time(NULL);
				preOrder(root);
				printf("\n ");
				finL = time(NULL);
				printf("\nPadron Listado en Arbol AVL tardado: %f segundos.\n", difftime(finL, inicioL));
				tiempo10 = difftime(finL, inicioL);
				printf("\n ");
				printf("\n ");
				printf("\n ");

				// Listar Arbol ABB
				cout << "-------------------------------------------------Padron Listado en Arbol ABB-------------------------------------------------" << endl;
				time_t inicioABB, finABB;
				inicioABB = time(NULL);
				EnOrdenIRD(ArbolBinario);
				printf("\n ");
				finABB = time(NULL);
				printf("\nPadron Listado en Arbol ABB ha tardado: %f segundos.\n", difftime(finL, inicioL));
				tiempo11 = difftime(finL, inicioL);
				printf("\n ");
				printf("\n ");
				printf("\n ");

				// Listar BTree
				cout << "-------------------------------------------------Padron Listado en Arbol BTree-----------------------------------------------" << endl;
				time_t inicioBTT, finBTT;
				inicioBTT = time(NULL);
				desplegar(BTree);
				printf("\n ");
				finBTT = time(NULL);
				printf("\nPadron Listado en Arbol BTree: %f segundos.\n", difftime(finBTT, inicioBTT));
				tiempo12 = difftime(finBTT, inicioBTT);
				printf("\n ");
			}
			else
				printf("Se han liberado todas las estructuras");
			printf("\n ");
			system("pause");
			break;

		case 3:
			borradoT = true;
			cout << "---------------------------------------------------Liberar lista en Lista Enlazada--------------------------------------------" << endl;
			time_t inicioLiE, finLiE; // Se declaran variables de tipo tiempo para medir la duración del proceso
			inicioLiE = time(NULL); // Declaración de variable para medir el tiempo inicial
			LiberarVotantes(ListaV);
			finLiE = time(NULL);
			printf("\n ");
			//cout << "-----------------------------------------------------Lista Liberada en Lista Enlazada-----------------------------------------------" << endl;
			printf("\nLiberar lista en Lista Enlazada ha tardado: %f segundos.\n", difftime(finLiE, inicioLiE));
			tiempo13 = difftime(finLiE, inicioLiE);
			printf("\n ");
			printf("\n ");
			printf("\n ");


			cout << "-----------------------------------------------------Liberar lista en Arbol AVL-----------------------------------------------" << endl;
			time_t inicioP, finP; // Se declaran variables de tipo tiempo para medir la duración del proceso
			inicioP = time(NULL); // Declaración de variable para medir el tiempo inicial
			printf("\n ");
			AVLPodarHojas(root);
			finP = time(NULL);
			//cout << "-----------------------------------------------------Lista Liberada en Arbol AVL-----------------------------------------------" << endl;
			printf("\nLiberar lista en Arbol AVL: %f segundos.\n", difftime(finP, inicioP));
			tiempo14 = difftime(finP, inicioP);
			printf("\n ");
			printf("\n ");
			printf("\n ");


			cout << "-----------------------------------------------------Liberar lista en Arbol ABB-----------------------------------------------" << endl;
			time_t inicioABBB, finABBB; // Se declaran variables de tipo tiempo para medir la duración del proceso
			inicioABBB = time(NULL); // Declaración de variable para medir el tiempo inicial
			printf("\n ");
			PodarHojas(ArbolBinario);
			finABBB = time(NULL);
			//cout << "-----------------------------------------------------Lista Liberada en Arbol ABB-----------------------------------------------" << endl;
			printf("\nLiberar lista en Arbol ABB ha tardado: %f segundos.\n", difftime(finABBB, inicioABBB));
			tiempo15 = difftime(finABBB, inicioABBB);
			printf("\n ");
			printf("\n ");
			printf("\n ");

			cout << "-----------------------------------------------------Liberar lista en Arbol BTree-------------------------------------------" << endl;
			time_t inicioBTR, finBTR; // Se declaran variables de tipo tiempo para medir la duración del proceso
			inicioBTR = time(NULL); // Declaración de variable para medir el tiempo inicial
			printf("\n ");
			borrarBTree(BTree);
			BTree = NULL;
			finBTR = time(NULL);
			//cout << "-----------------------------------------------------Lista Liberada en Arbol BTree-------------------------------------------" << endl;
			printf("\nLiberar lista en Arbol BTree ha tardado: %f segundos.\n", difftime(finBTR, inicioBTR));
			tiempo16 = difftime(finBTR, inicioBTR);
			printf("\n ");
			system("pause");
			break;

		case 4: // Reporte tiempos
			printf("\n       TIEMPO DE CARGA: %f segundos. \n", tiempo1);
			printf("\n       -----------------------------------------------Tiempos de Insercion----------------------------------------------- \n");
			printf("\n       Se ha tardado en insertar en Arbol Binario de Busqueda: %f segundos.", tiempo2);
			printf("\n       Se ha tardado en insertar en Arbol BTree: %f segundos.", tiempo3);
			printf("\n       Se ha tardado en insertar en Arbol AVL: %f segundos. \n", tiempo4);

			printf("\n       -----------------------------------------------Tiempos de Busqueda------------------------------------------------ \n");
			printf("\n       Se ha tardado en buscar en Lista Enlazada: %f segundos.", tiempo5);
			printf("\n       Se ha tardado en buscar en Arbol AVL: %f segundos.", tiempo6);
			printf("\n       Se ha tardado en buscar en Arbol Binario de Busqueda: %f segundos. ", tiempo7);
			printf("\n       Se ha tardado en buscar en Arbol BTree: %f segundos. \n", tiempo8);

			printf("\n       -----------------------------------------------Tiempos de Listar-------------------------------------------------- \n");
			printf("\n       Se ha tardado en listar en Lista Enlazada: %f segundos.", tiempo9);
			printf("\n       Se ha tardado en listar en Arbol AVL: %f segundos.", tiempo10);
			printf("\n       Se ha tardado en listar en Arbol Binario de Busqueda: %f segundos. ", tiempo11);
			printf("\n       Se ha tardado en listar en Arbol BTree: %f segundos. \n", tiempo12);

			printf("\n       -----------------------------------------------Tiempos de Liberar-------------------------------------------------- \n");
			printf("\n       Se ha tardado en liberar en Lista Enlazada: %f segundos.", tiempo13);
			printf("\n       Se ha tardado en liberar en Arbol AVL: %f segundos.", tiempo14);
			printf("\n       Se ha tardado en liberar en Arbol Binario de Busqueda: %f segundos. ", tiempo15);
			printf("\n       Se ha tardado en liberar en Arbol BTree: %f segundos. \n\n", tiempo16);

			system("pause");
			break;

		case 5: // Salir
			exit(0);
		}
		cout << endl;

	}

}