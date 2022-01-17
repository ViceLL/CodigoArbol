/*
Grupo #4:

Victor Matos 1093812
Vicente Vargas 1097813
Darlene Sanz 1097870

Construir un algoritmo para manejar arboles binarios, donde se permita insertar y eliminar un nodo
*/

#include <iostream>
#include<stdlib.h>
using namespace std;

struct Nodo
{
    int dato;
    Nodo* der;  //Nodo de la izquierda
    Nodo* izq;  //Nodo de la derecha
    Nodo* raiz; //Referencia quien es el padre de cada Nodo
};

//prototipos
void menu();
Nodo* crearNodo(int, Nodo*);
void insertarNodo(Nodo*&, int, Nodo*);
void mostrarArbol(Nodo*, int);
void mostrarEnOrden(Nodo*);
void eliminar(Nodo*, int);
void eliminarNodo(Nodo*);
Nodo* minimo(Nodo*); //Funcion para hayar el nodo mas izquierdo posible
void reemplazar(Nodo*, Nodo*); //Funcion para reemplazar padres e hijos
void destruirNodo(Nodo*);

Nodo* arbol = NULL;   //Creamos el arbol

//main
int main()
{
    menu();
    return 0;
}

//Funcion del menu
void menu()
{
    int dato, opcion, contador = 0; //el contador=0 para que el espacio antes de copiar el arbol no sea ninguno
    do                            //Que empieze a contar desde el inicio
    {
        cout << "Menu: " << endl;
        cout << "1. Insertar un nuevo nodo" << endl;
        cout << "2. Mostrar arbol completo" << endl;
        cout << "3. Mostrar InOrder" << endl;
        cout << "4. Eliminar nodo" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1: cout << "\nDigite un numero: ";
            cin >> dato;
            insertarNodo(arbol, dato, NULL); //insertamos un nuevo nodo
            cout << "\n";
            system("pause");
            //system("cls");
            break;

        case 2: cout << "\nMostrar arbol completo: \n\n";
            mostrarArbol(arbol, contador);  //mostramos el arbol
            cout << "\n";
            system("pause");
            //system("cls");
            break;

        case 3: cout << "\nMostrar en recorrido InOrder: \n";
            mostrarEnOrden(arbol); //mostramos los nodos del arbol en forma de lista ordenada
            cout << "\n\n";
            system("pause");
            //system("cls");
            break;

        case 4: cout << "\nDigite el nodo que quiere eliminar: ";
            cin >> dato;
            eliminar(arbol, dato);        //Eliminamos Nodo
            cout << "\n";
            system("pause");
            //system("cls");
            break;
        }

    } while (opcion != 5);

}

Nodo* crearNodo(int n, Nodo* raiz)   //creamos el nodo
{
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    nuevoNodo->raiz = raiz;

    return nuevoNodo;
}

//Funcion para insertar elementos al arbol

void insertarNodo(Nodo*& arbol, int n, Nodo* raiz) //Hay 2 partes para insertar, la 1ra cuando el arbol esta vacio y en la 2da cuando el arbol tenga un nodo
{
    if (arbol == NULL) //Si el arbol esta vacio se crea un nuevo nodo, llamamos a la funcion CrearNodo y con el parametro n
    {
        Nodo* nuevoNodo = crearNodo(n, raiz);
        arbol = nuevoNodo;  //Cuando se crea lo almacenamos en la raiz del arbol
    }
    else //Si tiene un nodo o mas de un nodo, necesitamos obtener el valor de la raiz
    {
        int valorRaiz = arbol->dato; //obtenemos el valor de la raiz
        if (n < valorRaiz)
        {
            insertarNodo(arbol->izq, n, arbol);  //Si el arbol es menor que la raiz la insertamos en la izquierda
        }
        else //Si el arbol es mayor que la raiz la insertamos en el lado derecho
        {
            insertarNodo(arbol->der, n, arbol);
        }
    }

}
//Funcion para mostrar arbol
void mostrarArbol(Nodo* arbol, int cont)
{
    if (arbol == NULL) //Si el arbol esta vacio (si no tiene nodos)
    {
        return; //Solo retorna, no va a mostrar nada
    }
    else
    {
        mostrarArbol(arbol->der, cont + 1);
        //Mostrara todos los nodos empezando del lado derecho, el cont+1 es para que se valla mostrando un espacio correspondiente entre c/u de ellos
        for (int i = 0; i < cont; i++)
        {
            cout << "   ";  //esto deja el espacio entre un nodo y otro
        }
        cout << arbol->dato << endl; //se imprimen todos los nodos del lado derecho hasta la raiz

        mostrarArbol(arbol->izq, cont + 1);

        //Se imprimen todos los del lado derecho, luego la raiz, y luego los del lado izquierdo
    }

}

// Funcion para mostrar los nodos del arbol en orden (de menor a mayor)
void mostrarEnOrden(Nodo* arbol)
{
    if (arbol == NULL) return;

    else
    {
        //Se atravieza el sub-arbol izquierdo
        mostrarEnOrden(arbol->izq);

        //Muestra el valor del nodo
        cout << arbol->dato << " ";

        //Se atraviesa el sub-arbol derecho
        mostrarEnOrden(arbol->der);
    }
}

//Funcion para eliminar el nodo encontrado

/*
A la hora de eliminar hay que tener en cuenta de que si el nodo es hoja (no tiene hijos)
si tiene un hijo izquierdo o derecho
o si tiene ambos hijos
*/

void eliminar(Nodo* arbol, int n)
{
    if (arbol == NULL)
    {
        return; //si el arbol esta vacio no hace nada
    }
    else if (n < arbol->dato)
    {
        eliminar(arbol->izq, n);  //Si el valor es menor busca por la izquierda

    }
    else if (n > arbol->dato)
    {
        eliminar(arbol->der, n);  //Si el valor es mayor busca por la derecha
    }
    else
    {
        eliminarNodo(arbol);  //Si se encontro el valor

    }

}
//Funcion para determinar el nodo mas izquierdo posible
Nodo* minimo(Nodo* arbol)
{
    if (arbol == NULL)
    {
        return NULL;
    }  //Si el arbol esta vacio, retornar nada
    if (arbol->izq) //Si tiene hijo izquierdo
    {
        return minimo(arbol->izq); //buscamos la parte izquierda mas posible
    }
    else
    {
        return arbol;  //si no tiene hijo izquierdo retornamos el mismo nodo
    }
}

void reemplazar(Nodo* arbol, Nodo* nuevoNodo)
{
    if (arbol->raiz) //si el arbol tiene raiz
    {
        //arbol ->raiz hay que asignarle nuevo hijo
        if (arbol->dato == arbol->raiz->izq->dato)
        {
            arbol->raiz->izq = nuevoNodo;  //se asigna caundo el nodo tenga un hijo izq
        }
        else if (arbol->dato == arbol->raiz->der->dato)
        {
            arbol->raiz->der = nuevoNodo;    //se asigna cuando el nodo tenga un hijo der
        }

    }
    if (nuevoNodo)
    {
        //asignamos su nueva raiz
        nuevoNodo->raiz = arbol->raiz; //le decimos al nuevo nodo quien es su nuevo raiz

    }
}

//Funcion para destruir un nodo
void destruirNodo(Nodo* nodo)
{
    nodo->izq = NULL; //Tecnicamente si tenias un hijo izquierdo o derecho ya no lo tiene y se borra el nodo
    nodo->der = NULL;

    delete nodo;
}

//Funcion para eliminar nodo encontrado
void eliminarNodo(Nodo* nodoEliminar)
{
    if (nodoEliminar->izq && nodoEliminar->der) //si el nodo tiene hijo izquierdo y derecho
    {
        Nodo* menor = minimo(nodoEliminar->der);// se crea un puntero menor para encontrar la parte izquierda del nodo
        nodoEliminar->dato = menor->dato; //El elemento que vamos a borrar se remplaza con el izquierdo posible
        eliminarNodo(menor); //luego se elimina el nodo

    }
    else if (nodoEliminar->izq) //Si tiene hijo izquierdo
    {
        reemplazar(nodoEliminar, nodoEliminar->izq);  //se reemplazan padres e hijos y se elimina el nodo siempre y cuando tenga un hijo izquierdo
        destruirNodo(nodoEliminar);
    }
    else if (nodoEliminar->der) //Si tiene hijo derecho
    {
        reemplazar(nodoEliminar, nodoEliminar->der); //Si tiene hijo derecho
        destruirNodo(nodoEliminar); //se reemplazan padres e hijos y se elimina el nodo siempre y cuando tenga un hijo derecho
    }
    else //Si un nodo no tiene hijos (Nodo hoja)
    {
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);

    }
}
