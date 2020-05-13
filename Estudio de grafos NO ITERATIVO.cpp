#include <iostream>
#include <stack>
#include <queue>
#include <climits>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stdio.h>  
#include <windows.h> 

#define ANCHO 90
#define ALTO 150

using namespace std;

int infinito=INT_MAX;
int INFINITO=INT_MAX;

struct NodoListaAdyacencia
{
	int destino;
	int dist;
	NodoListaAdyacencia *siguiente;
};

struct Lista
{
	NodoListaAdyacencia *inicio;
};


class Grafo_Matriz
{
	private:
		int v;
		int **a;
	
	public:
		Grafo_Matriz(int);
		void AgregarArista(int, int, int);
		int Mindistanciaprim(int[], bool[]);
		void mostrarPrim(int[], int[],int);
		void Prim(int);
		int Mindistanciadijkstra(int[], bool[]);
		void Dijkstra(int);
		void MostrarDijkstra(int[], int[],int);
		~Grafo_Matriz();
};

Grafo_Matriz::~Grafo_Matriz()
{
	for (int i = 0; i < v; i++)
	{
		delete[] a[i];
	}
}

int Grafo_Matriz::Mindistanciadijkstra(int d[], bool spt[])
{
	int min = INT_MAX;
	int indice = -1;
	for (int i = 0; i < v; i++)
	{
		if (spt[i] == false && d[i] <= min)
		{
			min = d[i];
			indice = i;
		}
	}
	return indice;
}

void Grafo_Matriz::Dijkstra(int origen)
{
	cout<<endl<<"CAMINOS MINIMOS DE DIJKSTRA DE ORIGEN: "<<origen<<endl<<endl;
	bool *spt = new bool[v];
	int *padre = new int[v];
	int *d = new int[v];

	for (int i = 0; i < v; i++)
	{
		spt[i] = false;
		d[i] = INT_MAX;
		padre[i] = -1;
	}
	d[origen] = 0;
	//seleccionamos menor distancia e incorporamos al spt
	for (int i = 0; i < v; i++)
	{
		int m = Mindistanciadijkstra(d, spt);
		spt[m] = true; // ponemos en true array spt
		for (int j = 0; j < v; j++)
		{
			if (!spt[j] && a[m][j] && d[m] != INT_MAX && d[m] + a[m][j] < d[j])
			{
				d[j] = d[m] + a[m][j];
				padre[j] = m;
			}
		}
	}
	MostrarDijkstra(d, padre,origen);
}

void Grafo_Matriz::MostrarDijkstra(int d[], int padre[],int origen)
{
	
	for (int i = 0; i < v; i++)
	{
		if(d[i]!=INFINITO )
		{
			
			if(i==origen)
			{
				cout << "[" << i << "]--> Distancia =  " << d[i] << " || Padre = NULL" << endl;
			}
			else
			{
				cout << "[" << i << "]--> Distancia =  " << d[i] << " || Padre = " << padre[i] << endl;
			}
		}

		if(d[i]==INFINITO)
		{
			cout << "[" << i << "]--> Distancia =  INFINITO" << " || Padre = NO HAY ADYACENCIA"  << endl;
		}
		    
	}
}

struct Arista
{
	int padre;
	int peso;
	bool mst;
};

Grafo_Matriz::Grafo_Matriz(int v)
{
	this->v = v;
	this->a = new int *[v];
	for (int i = 0; i < v; i++)
	{
		a[i] = new int[v];
		for (int j = 0; j < v; j++)
		{
			a[i][j] = 0;
		}
	}
}

void Grafo_Matriz::AgregarArista(int origen, int destino, int dist)
{
	a[origen][destino] = dist;
	a[destino][origen] = dist;
}

int Grafo_Matriz::Mindistanciaprim(int dist[], bool mst[])
{
	int min = INFINITO;
	int indice = -1;
	for (int i = 0; i < v; i++)
	{
		if (mst[i] == false && dist[i] <= min)
		{
			min = dist[i];
			indice = i;
		}
	}
	return indice;
}

void Grafo_Matriz::Prim(int origen)
{
	cout<<endl<<"ARBOL RECUBRIDOR DE PRIM DE ORIGEN: "<<origen<<endl<<endl;
	bool *mst = new bool[v];
	int *padre = new int[v];
	int *dist = new int[v];
	for (int i = 0; i < v; i++)
	{
		dist[i] = INFINITO;
		mst[i] = false;
	}
	padre[origen] = -1;
	dist[origen] = 0;
	for (int i = 0; i < v - 1; i++)
	{
		int m = Mindistanciaprim(dist, mst);
		mst[m] = true;
		for (int j = 0; j < v; j++)
		{
			if (a[m][j] && mst[j] == false && a[m][j] < dist[j])
			{
				padre[j] = m;
				dist[j] = a[m][j];
			}
		}
	}
	mostrarPrim(padre, dist,origen);
}

void Grafo_Matriz::mostrarPrim(int padre[], int dist[],int origen)
{
	bool recubridor=true;
	int total=0;
	for (int i = 0; i < v; i++)
	{
		if(dist[i]==INFINITO)
		{
			recubridor=false;
		}
	}
	if (recubridor==true)
	{
		for(int i=0;i<v;i++)
		{
			if(i==origen)
			{
				cout << "[" << i << "]--> Distancia =  " << dist[i] << " || Padre = NULL" << endl;
			}
			else
			{
				cout << "[" << i << "]--> Distancia =  " << dist[i] << " || Padre = " << padre[i] << endl;
				total=total+dist[i];
			}
			
		}
		cout<<endl<<"Peso total de Arbol Recubridor de Prim = "<<total;
		
	}
	if (recubridor==false)
	{
		cout<<"NO EXISTE ARBOL RECUBRIDOR"<<endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Aristak
{
    int origen;
    int destino;
    int peso;
    bool operator < (const Aristak& a1) const 
	{
        return (peso < a1.peso);
    }
};

class Grafok
{
    private:
        int v;
        vector<Aristak> ari;
        int* subConjunto; //Subconjunto es nuestro vector "padre
        int cont;
        int find(int);

    public:
        Grafok(int);
        ~Grafok();
        void agregarAristak(int, int, int);
        void Kruskal();
        void _union(int, int);
};

//Constructor, pide la cantidad de vértices
Grafok::Grafok(int v)
{
    this->v = v;
    cont = 0;
    subConjunto = new int [v];
    for(int i=0; i<v; i++)
	{
        subConjunto[i] = -1;
    }
};

Grafok::~Grafok()
{
    delete[] subConjunto;
};


//Cambiar el valor de una intersección de fila y columna para indicar la existencia de una arista
void Grafok::agregarAristak(int n, int m, int peso)
{
    Aristak nueva;
    nueva.origen=n;
    nueva.destino=m;
    nueva.peso=peso;
    ari.push_back(nueva);
    cont ++;
};

//Metodo Kruskal
void Grafok::Kruskal()
{
	cout<<endl<<"ARBOL RECUBRIDOR DE KRUSKAL"<<endl<<endl;
    bool conexo=true;
    int pesoMST = 0;
    
    int max=0;
    for (int i=0;i<cont;i++)
    {
    	if(ari[i].peso>max)
    	{
    		max=ari[i].peso;
		}
	}
    
    Aristak* mst = new Aristak [v-1];
    int contMST = 0;
    sort(ari.begin(), ari.begin()+cont);
    if(cont==0 && v>0)
    {
    	conexo=false;	
	}
    
    
    for(int i=0; i<cont; i++)
	{
	
		if(ari[i].origen!=INFINITO && ari[i].destino!=INFINITO && ari[i].peso!=INFINITO)
		{
			int x = find(ari[i].origen);
	        int y = find(ari[i].destino);
	        if(x!=y)
			{
	            mst[contMST] = ari[i];
	            contMST++;
	            _union(x, y);
	        }
		}   
    }
  
	for(int i=0; i<v-1; i++)
	{
		if(mst[i].origen==INFINITO || mst[i].destino==INFINITO || mst[i].peso==0 || mst[i].peso>=INFINITO ||mst[i].peso>max)
		{
			conexo=false;
			cout<<"NO EXISTE ARBOL RECUBRIDOR"<<endl<<endl;
			break;
		}
	}
	
	
	if(conexo!=false)
	{
		for(int i=0;i<v-1;i++)
		{
			cout << "[" << mst[i].origen << "] || Destino ------>" << mst[i].destino << " || Peso ------> " << mst[i].peso  << endl;
	       	pesoMST += mst[i].peso;
		}
		cout << endl << "El peso Total del Grafo recubridor es: " << pesoMST << endl;
	}

    delete [] mst;
    for(int i=0; i<v; i++)
	{
        subConjunto[i] = -1;
    }
}

int Grafok::find(int vertice)
{
    if(subConjunto[vertice] == -1)
	{
        return vertice;
    }
    return find(subConjunto[vertice]);
}

void Grafok::_union(int sub1, int sub2)
{
    subConjunto[sub2] = sub1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Grafo
{
	private:
		int v;
		Lista *l;
		void recorridoProfundidadPr(bool* visitados, int v_actual, stack <int> pila);
	
	public:
		Grafo(int);
		~Grafo();
		void agregarArista(int,int,int,int);
		void Mostrar();
		void recorridoProfundidad();
		void recorridoAmplitud();
};

Grafo::Grafo(int v)
{
	this->v = v;
	l = new Lista[v];
	for (int i = 0; i < v; i++)
	{
		l[i].inicio = NULL;
	}
}

Grafo::~Grafo()
{
	for (int i = 0; i < v; i++)
	{
		NodoListaAdyacencia *n = l[i].inicio;
		while (n != NULL)
		{
			NodoListaAdyacencia *aux = n;
			n = aux->siguiente;
			delete aux;
		}
	}
}

void Grafo::agregarArista(int t,int o, int d, int dist)
{
	NodoListaAdyacencia* aux = new NodoListaAdyacencia;
    aux->destino=d;
    aux->dist=dist;
    aux->siguiente=l[o].inicio;
    l[o].inicio = aux;
	if(t!=1)
	{
		NodoListaAdyacencia* aux2 = new NodoListaAdyacencia;
	    aux2->destino=o;
	    aux2->dist=dist;
	    aux2->siguiente=l[d].inicio;
	    l[d].inicio = aux2;
	}
};
	

void Grafo::Mostrar()
{
	cout<<"Lista de adyacencia de  x: [Vertice, Peso de arista]"<<endl<<endl;
	for (int i = 0; i < v; i++)
	{
		int grado = 0;
		cout<<"Lista de adyacencia de "<<i<<": ";
		NodoListaAdyacencia *n = l[i].inicio;
		
		if(l[i].inicio==NULL)
		{
			cout<<" -  ";
		}
		
		while (n != NULL)
		{
			if(n->siguiente!=NULL)
			{
				grado++;
				cout << "["<<n->destino << ","<<n->dist<<"]"<<"->";
				n = n->siguiente;
			}
			if(n->siguiente==NULL)
			{
				grado++;
				cout << "["<<n->destino << ","<<n->dist<<"]"<<" ";
				n = n->siguiente;	
			}
		}
		cout << "Grado: " << grado <<endl;
	}
	cout<<endl;
}

void Grafo::recorridoProfundidad()
{
    stack <int> pila;
    bool* visitados = new bool [v];
    for(int i=0; i<v; i++)
	{
        visitados[i] = false;
    }
    for(int i=0; i<v; i++)
	{
        int v_actual = i;
        recorridoProfundidadPr(visitados, v_actual, pila);
    }
    delete [] visitados;
}

void Grafo::recorridoProfundidadPr(bool* visitados, int v_actual, stack <int> pila)
{
    if(!visitados[v_actual]) 
	{
        pila.push(v_actual);
        visitados[v_actual] = true;
        if(!pila.empty())
		{
            cout << v_actual << " ";
            NodoListaAdyacencia* nodoActual = l[v_actual].inicio;
            while(nodoActual) 
			{
                if(!visitados[nodoActual->destino]) 
				{
                    recorridoProfundidadPr(visitados, nodoActual->destino, pila);
                }
                nodoActual = nodoActual->siguiente;
            }
            pila.pop();
        }
    }
}

void Grafo::recorridoAmplitud()
{
    queue <int> cola;
    bool* visitado = new bool[v];
    for(int i=0; i<v; i++)
	{
        visitado[i] = false;
    }
    
    for(int i=0; i<v; i++)
	{
        int v_actual = i;
        if(!visitado[v_actual])
		{
            cola.push(v_actual);
            visitado[i] = true;

            while(!cola.empty())
			{
                v_actual = cola.front();
                cout << v_actual << " ";
                cola.pop();

                NodoListaAdyacencia* nodoActual = l[v_actual].inicio;
                while(nodoActual)
				{
                    if(!visitado[nodoActual->destino])
					{
                        cola.push(nodoActual->destino);
                        visitado[nodoActual->destino] = true;
                    }
                    nodoActual = nodoActual->siguiente;
                }
            }
        }
    }
    delete [] visitado;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void saludof();
void sello();

void menu(int c,Grafo g1,Grafo_Matriz g2,Grafok g3)
{
	system ("cls");
	float var_x;
	int n;

	bool a=true;
	while (a)
    {
    	
    	sello();
		cout << "  _______________________________________________________ " <<endl;
		cout << "  |                                                     | " <<endl;
		cout << "  |                  MENU PRINCIPAL                     | " <<endl;
		cout << "  |_____________________________________________________| " <<endl;
		cout << "  |                                                     | " <<endl;
		cout << "  |   1) Agregar arista (Vertices: 0 - "<<c-1<<")               |"<<endl;
		cout << "  |   2) Mostrar adyacencia y peso                      | " <<endl;
		cout << "  |   3) Recorrido en Profundidad                       | " <<endl;
		cout << "  |   4) Recorrido en Amplitud                          |"  <<endl;
		cout << "  |   5) Arbol recubridor minimo (Prim)                 | " <<endl;
		cout << "  |   6) Arbol recubridor minimo (Kruskal)              | " <<endl;
		cout << "  |   7) Camino mas corto desde...                      | " <<endl;
		cout << "  |   8) Terminar Programa                              | " <<endl;
		cout << "  |_____________________________________________________| " <<endl;
		cout <<" "<<endl;
		
		cout << "Ingrese su respuesta: ";
        a=false;
        cin>>var_x;
    	n = static_cast<int>(var_x);
    
    
        if (cin.fail())
        {
          	cout<<""<<endl;
          	cout<<""<<endl;
            cout<<"Por favor, ingrese un numero valido"<<endl;
            cin.clear();
            cin.ignore(10,'\n');
            a=true;
            cout<<""<<endl;
            system("pause");
            system("cls");
        }
    }
    switch( n )
	{
		case 1:
			{
				system("cls");
				sello();
				float m;
				float z;
				
				int n;
		
				int t;
				cout<<"Aristas dirigidas?"<<endl;
				cout<<"1) Si"<<endl;
				cout<<"2) NO"<<endl<<endl;
				cout<<"Respuesta: ";
				cin>>m;
				t=static_cast<int>(m);
				cout<<"Ingrese cantidad de aristas a agregar: ";
				cin>>z;
				n=static_cast<int>(z);
				system("cls");
				sello();
				for(int i=0;i<n;i++)
				{
				
					float r;
					float s;
					float k;
					int o;
					int d;
					int p;

					cout<<"Arista nueva "<<i+1<<" de "<<n<<endl;
					cout<<"   Vertice 1: ";
					cin>>r;
					o=static_cast<int>(r);
					cout<<"   Vertice 2: ";
					cin>>s;
					d=static_cast<int>(s);
					cout<<"   Peso: ";
					cin>>k;
					p=static_cast<int>(k);
			
					if(o<0 || o>c-1|| d>c-1 || d<0)
					{
						cout<<"Por favor, ingrese un numero valido (0 < X < "<<c<<")"<<endl;
				        cin.clear();
				        cin.ignore(10,'\n');
				        i=i-1;
					}
					
					
					if( cin.fail() || p<1)
					{
						cout<<endl<<"Por favor, ingrese un vertice valido (0 < X < "<<c<<")"<<endl;
						cout<<"Por favor, ingrese un peso valido (X<0)"<<endl;
				        cin.clear();
				        cin.ignore(10,'\n');
				        i=i-1;
					}
				
				
					if(o>=0 && d<c && o<c &&d>0 && p>0)
					{
						g1.agregarArista(t,o,d,p);
						g2.AgregarArista(o,d,p);
						g3.agregarAristak(o,d,p);
						continue;
					}
					cout<<endl;
				}	
				menu(c,g1,g2,g3);
				break;
				}	
				
		case 2:
			{
				g1.Mostrar();
				system("pause");
				menu(c,g1,g2,g3);
				break;
			}
		case 3:
			{
				cout<<"Recorido en Profundidad: ";
				g1.recorridoProfundidad();
				cout<<endl<<endl;
				system("pause");
				menu(c,g1,g2,g3);
				break;
			}
		case 4:
			{
				cout<<"Recorido en Amplitud: ";
				g1.recorridoAmplitud();
				cout<<endl<<endl;
				system("pause");
				menu(c,g1,g2,g3);
				break;
			}
		case 5:
			{
				float j;
				int i;
				cout<<"Vertice inicial de recorrido (X>-1 && X<"<<c<<"): ";
				cin>>j;
				i=static_cast<int>(j);
				if(i<0 || i>c-1 || cin.fail())
				{
					cout<<"Error: indice no aceptado"<<endl<<endl;
					system("pause");
					menu(c,g1,g2,g3);
				}
				else
				{
					g2.Prim(i);
					cout<<endl<<endl;
					system("pause");
					menu(c,g1,g2,g3);
					break;
				}
			}
			
		case 6:
			{
				g3.Kruskal();
				cout<<endl<<endl;
				system("pause");
				menu(c,g1,g2,g3);
				break;
			}
			
		case 7:
			{
				int i;
				float j;
				cout<<"Vertice inicial de recorrido (X>-1 && X<"<<c<<"): ";
				cin>>j;
				i=static_cast<int>(j);
				if(i<0 || i>c-1 || cin.fail())
				{
					cout<<"Error: indice no aceptado"<<endl<<endl;;
					system("pause");
					menu(c,g1,g2,g3);
				}
				else
				{
					g2.Dijkstra(i);
					cout<<endl<<endl;
					system("pause");
					menu(c,g1,g2,g3);
					break;
				}
			}		
		
		case 8:
			{
				saludof();
				break;
			}
		
		default:
			{
			   	cout<<""<<endl;
				cout<<"Por favor, ingrese un numero valido."<<endl;
				cout<<""<<endl;
				system ("pause");
				menu(c,g1,g2,g3);
			}	
	}
}

int main()
{
	
	Grafo g1(10);
	Grafo_Matriz g2(10);
	Grafok g3(10);
	

	g1.agregarArista(1,3,4,9);
    g1.agregarArista(1,4,5,10);
    g1.agregarArista(1,1,7,11);
    g1.agregarArista(1,3,5,14);
    g1.agregarArista(1,7,6,1);
    g1.agregarArista(1,6,5,2);
    g1.agregarArista(2,8,2,2);
    g1.agregarArista(2,2,5,4);
    g1.agregarArista(1,0,1,4);
    g1.agregarArista(1,8,6,6);
    g1.agregarArista(2,2,3,7);
    g1.agregarArista(1,7,8,7);
    g1.agregarArista(1,0,7,8);
    g1.agregarArista(2,1,2,8);
    
    g2.AgregarArista(3,4,9);
    g2.AgregarArista(4,5,10);
    g2.AgregarArista(1,7,11);
    g2.AgregarArista(3,5,14);
    g2.AgregarArista(7,6,1);
    g2.AgregarArista(6,5,2);
    g2.AgregarArista(8,2,2);
    g2.AgregarArista(2,5,4);
    g2.AgregarArista(0,1,4);
    g2.AgregarArista(8,6,6);
    g2.AgregarArista(2,3,7);
    g2.AgregarArista(7,8,7);
    g2.AgregarArista(0,7,8);
    g2.AgregarArista(1,2,8);
    
	
	
	g3.agregarAristak(3,4,9);
    g3.agregarAristak(4,5,10);
    g3.agregarAristak(1,7,11);
    g3.agregarAristak(3,5,14);
    g3.agregarAristak(7,6,1);
    g3.agregarAristak(6,5,2);
    g3.agregarAristak(8,2,2);
    g3.agregarAristak(2,5,4);
    g3.agregarAristak(0,1,4);
    g3.agregarAristak(8,6,6);
    g3.agregarAristak(2,3,7);
    g3.agregarAristak(7,8,7);
    g3.agregarAristak(0,7,8);
    g3.agregarAristak(1,2,8);
	

	menu(10,g1,g2,g3);
	return 0;

}


void gotoxy(int x,int y)
{  
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
 }

void sello()
{
	gotoxy(90,1);
 	cout<<"  UUUUUU     UUUUUU "<<endl;
 	gotoxy(90,2);
 	cout<<"  UUUUUU     UUUUUU "<<endl;
 	gotoxy(90,3);
 	cout<<"  UUUUUU     UUUUUU "<<endl;
 	gotoxy(90,4);
 	cout<<"  UUUUUU     UUUUUU "<<endl;
 	gotoxy(90,5);
 	cout<<"  UUUUUU     UUUUUU "<<endl;
 	gotoxy(90,6);
 	cout<<"    UUUUUUUUUUUUU "<<endl;
 	gotoxy(90,7);
 	cout<<"     UUUUUUUUUUU "<<endl;

 

 	gotoxy(90,9);
 	cout<<"  BBBBBBBBBBBBBBB "<<endl;
 	gotoxy(90,10);
 	cout<<"  BBBBB    BBBBBB "<<endl;
 	gotoxy(90,11);
 	cout<<"  BBBBB   BBBBBB    "<<endl;
 	gotoxy(90,12);
 	cout<<"  BBBBB  BBBBBB    "<<endl;
 	gotoxy(90,13);
 	cout<<"  BBBBB BBBBBB  "<<endl;
 	gotoxy(90,14);
 	cout<<"  BBBBB  BBBBBB "<<endl;
 	gotoxy(90,15);
 	cout<<"  BBBBB   BBBBBB "<<endl;
 	gotoxy(90,16);

 	cout<<"  BBBBBBBBBBBBBB "<<endl;


 	gotoxy(90,18);
 	cout<<"  PPPPPPPPPPPPPPPP "<<endl;
 	gotoxy(90,19);
 	cout<<"  PPPPPP    PPPPPP"<<endl;
 	gotoxy(90,20);
 	cout<<"  PPPPPP    PPPPPP"<<endl;
 	gotoxy(90,21);
 	cout<<"  PPPPPP    PPPPPP"<<endl;
 	gotoxy(90,22);
 	cout<<"  PPPPPPPPPPPPPPP"<<endl;
 	gotoxy(90,23);
 	cout<<"  PPPPPP "<<endl;
 	gotoxy(90,24);
 	cout<<"  PPPPPP "<<endl;
 	
 	gotoxy(60,26);
 	cout<<"�NUMEROS FLOTANTES INGRESADOS, SERAN TOMADOS COMO ENTEROS!"<<endl;
 	gotoxy(0,0);
}

void saludof()
{
	system("cls");
    cout<<" "<<endl;
	cout<<"		GGGGGGGG   RRRRRRRR   AAAAAAAA     CCCCCC   II   AAAAAAAA   SSSSSSSSS"<<endl;
	cout<<"		GGGGGGGG   RRRRRRRR   AAAAAAAA    CCCCCC    II   AAAAAAAA   SS       "<<endl;
	cout<<"		GG         RR   RR    AA    AA   CC         II   AA    AA   SS       "<<endl;
	cout<<"		GGGGGGGG   RR  RR     AA    AA   CC         II   AA    AA   SSSSSSSS "<<endl;
	cout<<"		GG    GG   RRRRR      AAAAAAAA   CC         II   AAAAAAAA         SS "<<endl;
	cout<<"		GG    GG   RRRRR      AAAAAAAA   CC         II   AAAAAAAA         SS "<<endl;      
	cout<<"		GGGGGGGG   RR  RR     AA    AA    CCCCCC    II   AA    AA         SS "<<endl;
	cout<<"		GGGGGGGG   RR   RR    AA    AA     CCCCCC   II   AA    AA   SSSSSSSS "<<endl;
	cout<<" "<<endl;
	cout<<" "<<endl;
	cout<<"                                 PPPPPPPP    OOOOOOO     RRRRRRR"<<endl;
	cout<<"                                 PP    PP   OOOOOOOOO   RRRRRRRRR"<<endl;
	cout<<"                                 PP    PP   OO     OO   RR    RR"<<endl;
	cout<<"                                 PP    PP   OO     OO   RR   RR"<<endl;
	cout<<"                                 PPPPPPPP   OO     OO   RRRRR"<<endl;
	cout<<"                                 PP         OO     OO   RRRRR"<<endl;
	cout<<"                                 PP         OOOOOOOOO   RR  RR"<<endl;
	cout<<"                                 PP          OOOOOOO    RR   RR"<<endl;
	cout<<" "<<endl;
	cout<<" "<<endl;
	cout<<"   EEEEEEEE   LL          EEEEEEEE   GGGGGGGG   II    RRRRRRR     NNNN   NN    OOOOOOO    SSSSSSSSS"<<endl;
	cout<<"   EEEEEEE    LL          EEEEEEE    GGGGGG     II   RRRRRRRRR   NN  NN  NN   OOOOOOOOO   SS"<<endl;
	cout<<"   EE         LL          EE         GG         II   RR    RR    NN  NN  NN   OO     OO   SS"<<endl;
	cout<<"   EEEEEE     LL          EEEEEE     GGGGGGGG   II   RR   RR     NN  NN  NN   OO     OO   SSSSSSSSS"<<endl;
	cout<<"   EEEEEE     LL          EEEEEE     GG    GG   II   RRRRR       NN  NN  NN   OO     OO          SS"<<endl;
	cout<<"   EE         LL          EE         GG    GG   II   RRRRR       NN  NN  NN   OO     OO          SS"<<endl;
	cout<<"   EEEEEEE    LL          EEEEEEE    GGGGGGGG   II   RR  RR      NN  NN  NN   OOOOOOOOO          SS"<<endl;
	cout<<"   EEEEEEEE   LLLLLLLLL   EEEEEEEE   GGGGGGGG   II   RR   RR     NN   NNNN     OOOOOOO    SSSSSSSSS"<<endl;
	
    system("pause");
}
