#include <iostream>
#include <cassert>
#include <vector>
using namespace std;


struct TDec{
	int fil;
	int col;
	int d;
};
const int N=7;


//funciones auxiliares
bool invalida (int i, int j){
	return ((i<2 and j<2) or (i>4 and j>4) or (i<2 and j>4) or (i>4 and j<2));
}

void inicializarTablero(vector<vector<int> > &tablero){
tablero.clear();
	for (int i=0; i<N; i++){
		vector<int> aux;
		for (int j=0; j<N; j++){
			if (invalida(i, j))
				aux.push_back(2);
			else if (!(i==3 && j==3))
				aux.push_back(1);
			else
				aux.push_back(0);
		}
		tablero.push_back(aux);
	}
}

void inicializarTablerores(vector<vector<int> > &tablero){
tablero.clear();
	for (int i=0; i<N; i++){
		vector<int> aux;
		for (int j=0; j<N; j++){
			if (invalida(i, j))
				aux.push_back(2);
			else if (!(i==3 && j==3))
				aux.push_back(0);
			else
				aux.push_back(1);
		}
		tablero.push_back(aux);
	}
}

void mostrarTablero(vector<vector<int> > &tablero){
	cout << "    ";	
	for (int i=0; i<N; i++)
		cout <<"  "<< i;
	cout << endl << endl;
	for (int i=0; i<N; i++){
		cout <<"  " << i << "  ";
		for (int j=0; j<N; j++){
			int casilla = tablero[i][j];
			char a_imprimir;
			switch (casilla){
				case 1:
					a_imprimir = 'o';
				break;
				case 2:
					a_imprimir = 'x';
				break;
				case 0:
					a_imprimir = ' ';
				break;		
			}
			cout << "[" << a_imprimir << "]";	
		}
		cout<<endl;
	}
}




//TDA Solución
		
class Solucion{
	private:
		vector<TDec> solucion;

		bool iguales(const vector<vector<int> > &tablero,vector<vector<int> > &tablerores){
			for(int i = 0;i<N; ++i){
				for(int j = 0;j <N;++j){
					if(tablero[i][j]!=tablerores[i][j])
						return false;
				}
			}
			return true;
		}	
 
	public:
		bool esSolucion(vector<vector<int> > &tablero,	vector<vector<int> >& tablerores);
		void registrarMovimiento(TDec dec, vector<vector<int> > &tablero);
		void vueltaAtras(TDec dec, vector<vector<int> > &tablero);
		bool factible(TDec dec, vector<vector<int> > &tablero);
		vector<TDec> posibles(vector<vector<int> > &tablero);
		bool encontrarSol(vector<vector<int> > &tablero,	vector<vector<int> >& tablerores );
		TDec get(int posicion);
		int tamanio();
};

bool Solucion::encontrarSol(vector<vector<int> > &tablero,	vector<vector<int> >& tablerores ){
	vector<TDec> posib = posibles(tablero);

	for(int i=0; i<posib.size();++i){

		solucion.push_back(posib[i]);
		
		registrarMovimiento(posib[i],tablero);

		if(esSolucion(tablero,tablerores)){
			
			return true;
		}

		bool res = encontrarSol(tablero,tablerores);

		if(res){
			return true;
		}else{
			vueltaAtras(posib[i],tablero);
			solucion.pop_back();
		}
	}

	return false;
}

vector<TDec> Solucion::posibles(vector<vector<int> > &tablero){

	vector<TDec> aux;
	TDec ahora;
	for (int i=0; i<N; i++){
		ahora.fil=i;
		for (int j=0; j<N; j++){
			ahora.col=j;
			for(int t=1; t<5 ; ++t){
				ahora.d=t;
				if(factible(ahora,tablero)){
					aux.push_back(ahora);
				}	
				
			}
		}
	}

	return aux;
}



bool Solucion::factible(TDec dec, vector<vector<int> > &tablero){
	
	
	if (tablero[dec.fil][dec.col]==1){
		if(dec.d==1){
				if(dec.fil-2 >= 0)
				if (tablero[dec.fil-1][dec.col]==1 and tablero[dec.fil-2][dec.col]==0)
					return true;
		}else if(dec.d==2){
				if(dec.col+2 <= 6)
				if (tablero[dec.fil][dec.col+1]==1  and tablero[dec.fil][dec.col+2]==0)
					return true;
		}else if(dec.d==3){
				if(dec.fil+2 <= 6)
				if (tablero[dec.fil+1][dec.col]==1 and tablero[dec.fil+2][dec.col]==0)
					return true;
		}else if(dec.d==4){
				if(dec.col-2 >= 0)
				if (tablero[dec.fil][dec.col-1]==1 and tablero[dec.fil][dec.col-2]==0)
					return true;
		}
	}
	return false;
}
			
void Solucion::registrarMovimiento(TDec dec, vector<vector<int> > &tablero){
	tablero[dec.fil][dec.col]=0;
	if(dec.d==1){
			tablero[dec.fil-1][dec.col]=0;
			tablero[dec.fil-2][dec.col]=1;
	}else if(dec.d==2){
			tablero[dec.fil][dec.col+1]=0;
			tablero[dec.fil][dec.col+2]=1;
	}else if(dec.d==3){
			tablero[dec.fil+1][dec.col]=0;
			tablero[dec.fil+2][dec.col]=1;
	}else if(dec.d==4){
			tablero[dec.fil][dec.col-1]=0;
			tablero[dec.fil][dec.col-2]=1;
	}
}

void Solucion::vueltaAtras(TDec dec, vector<vector<int> > &tablero){
		tablero[dec.fil][dec.col]=1;
	if(dec.d==1){
			tablero[dec.fil-1][dec.col]=1;
			tablero[dec.fil-2][dec.col]=0;
	}else if(dec.d==2){
			tablero[dec.fil][dec.col+1]=1;
			tablero[dec.fil][dec.col+2]=0;
	}else if(dec.d==3){
			tablero[dec.fil+1][dec.col]=1;
			tablero[dec.fil+2][dec.col]=0;
	}else if(dec.d==4){
			tablero[dec.fil][dec.col-1]=1;
			tablero[dec.fil][dec.col-2]=0;
	}
}

TDec Solucion::get(int posicion){
	assert(posicion>=0 && posicion<solucion.size());
	return solucion[posicion];
}

int Solucion::tamanio(){
	return solucion.size();	
}

bool Solucion::esSolucion(vector<vector<int> > &tablero,	vector<vector<int> >& tablerores){

	return (tamanio()==31 && iguales(tablero,tablerores));
}

int main(){
	Solucion solucion;
	vector<vector<int> > tablero;
	vector<vector<int> > tablerores;
	//Inicializar el tablero
	inicializarTablero(tablero);
	inicializarTablerores(tablerores);
	//Llamar a la función backtracking
	 bool encontrado =solucion.encontrarSol(tablero,tablerores);
	//mostrar tablero

	if(!encontrado){
		cout << "No se ha podido encontrar solucion" << endl;
	}
	else{
		inicializarTablero(tablero);
		mostrarTablero(tablero);
		cout << endl;
		for (int i=0;i<solucion.tamanio();++i){
			TDec accion = solucion.get(i);
			string direccion;
			switch(accion.d){
				case 1:
					direccion="arriba";
				break;
				case 2:
					direccion="derecha";
				break;
				case 3:
					direccion="abajo";
				break;
				case 4:
					direccion="izquierda";
				break;			
			}
			cout << "Mover ficha en la posicion Fila: " << accion.fil << " Columna: " << accion.col << " Direccion: " << direccion << endl;
			solucion.registrarMovimiento (accion,tablero);
			mostrarTablero(tablero); 
			cout << endl;
		}	
	}

	
	
	return 0;
	
}
	
	
