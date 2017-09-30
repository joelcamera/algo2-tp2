#include<iostream>
#include<cassert>

using namespace std;


/*
 *	Arbol binario de busqueda.
 */

template <typename T>
class ABB{

	public:

		ABB();
		ABB(const ABB<T>& otro);
		~ABB();

		void Definir(int clave, T& sign);
		bool Definido(int clave);
		T& Obtener(int clave);
		void Borrar(int clave);
		int CantClaves();
		bool EsVacio();

		// requiere !EsVacio()
		int Raiz();

		int Altura();
		int Niveles();
		bool EsCompleto();
		void Inorder();
		void Preorder();
		void Postorder();

		bool operator==(const ABB<T>& otro);
		bool operator!=(const ABB<T>& otro);
		ABB<T>& operator=(const ABB<T>& otro);

		template <typename TT>
		friend ostream& operator<<(ostream& os, const ABB<TT>& tree);

		typename ABB<T>::Iterador CrearIt();
		typename ABB<T>::const_Iterador CrearItConst();



		/*************************************************************
		*                  ITERADOR MODIFICABLE                      *
		**************************************************************/

		class Iterador{

			/* No hago funciones de agregar o eliminar para no romper el
			 * invariante del arbol.
			 */
			
			public:
			
				Iterador() : arboliter(NULL), paiter(NULL), pbiter(NULL) {};

				Iterador(const typename ABB<T>::Iterador& otro) : arboliter(otro.arboliter), paiter(otro.paiter), pbiter(otro.pbiter) {};

				bool HaySiguiente();
				int SiguienteClave();
				T& SiguienteSignificado();

				bool HayAnterior();
				int AnteriorClave();
				T& AnteriorSignificado();

				void Avanzar();
				void Retroceder();

				bool operator==(const typename ABB<T>::Iterador& otro);
				bool operator!=(const typename ABB<T>::Iterador& otro);

			private:

				Iterador(ABB<T>* _arboliter, typename ABB<T>::Nodo* _paiter){
					arboliter = _arboliter;
					paiter = _paiter;
					pbiter = NULL;
				};

				friend typename ABB<T>::Iterador ABB<T>::CrearIt();

				//ESTRUCTURA
				ABB<T>* arboliter;
				typename ABB<T>::Nodo* paiter;
				typename ABB<T>::Nodo* pbiter;

				// FUNCIONES AUXILIARES
				typename ABB<T>::Nodo* BuscoNodoSiguiente(typename ABB<T>::Nodo* pa);
				typename ABB<T>::Nodo* BuscoNodoAnterior(typename ABB<T>::Nodo* pb);
				bool EsHijoIzquierdo(typename ABB<T>::Nodo* pa);

		};



		/*************************************************************
		*                  ITERADOR NO MODIFICABLE                   *
		**************************************************************/

		class const_Iterador{
				
			public:
				
				const_Iterador() {};

				const_Iterador(const typename ABB<T>::const_Iterador& otro) : itconst(otro.itconst) {};

				bool HaySiguiente();
				int SiguienteClave();
				const T& SiguienteSignificado();

				bool HayAnterior();
				int AnteriorClave();
				const T& AnteriorSignificado();

				void Avanzar();
				void Retroceder();

				bool operator==(const typename ABB<T>::const_Iterador& otro);
				bool operator!=(const typename ABB<T>::const_Iterador& otro);

			private:

				friend typename ABB<T>::const_Iterador ABB<T>::CrearItConst();
				
				const_Iterador(const typename ABB<T>::Iterador& _itconst){
					itconst = _itconst;
				};

				typename ABB<T>::Iterador itconst;
		};



	private:

		struct Nodo{
			
			Nodo(){
				padre = NULL;
				hizq = NULL;
				hder = NULL;
			}

			Nodo(int _clave, const T& _sign) : clave(_clave), sign(_sign) {
				padre = NULL;
				hizq = NULL;
				hder = NULL;
			}

			int clave;
			T sign;
			Nodo* padre;
			Nodo* hizq;
			Nodo* hder;
		};

		
		//ESTRUCTURA

		Nodo* raiz;
		Nodo* masChico;
		int cantnodos;


		/*************************************************************
		*                  FUNCIONES AUXILIARES                      *
		**************************************************************/

		typename ABB<T>::Nodo* BuscaNodoParaInsertar(int clave);
		typename ABB<T>::Nodo* BuscaNodo(int clave);
		void BorrarArbol(typename ABB<T>::Nodo* a);
		int NivelesDyC(typename ABB<T>::Nodo* a);
		int Max(int a, int b);
		int CantidadNodosAlturaMax();
		int CNAMDyC(typename ABB<T>::Nodo* a, int n);
		int DosALaAltura();
		int DALAaux(int n);
		void InorderDyC(ostream& os, typename ABB<T>::Nodo* a);
		void PreorderDyC(ostream& os, typename ABB<T>::Nodo* a);
		void PostorderDyC(ostream& os, typename ABB<T>::Nodo* a);
		bool OperAsignacionDyC(typename ABB<T>::Nodo* a, typename ABB<T>::Nodo* b);
		bool TieneDosHijos(typename ABB<T>::Nodo* a);
		bool TieneHijoIzquierdo(typename ABB<T>::Nodo* a);
		void AgregarNodos(typename ABB<T>::Nodo* b);
		typename ABB<T>::Nodo* BuscoNodoMasDerecha(typename ABB<T>::Nodo* a);

		// Auxiliares en Borrar
		bool NoTieneHijos(typename ABB<T>::Nodo* pb);
		void BorrarCasoNoTieneHijos(typename ABB<T>::Nodo* pb);
		bool TieneUnHijo(typename ABB<T>::Nodo* pb);
		void BorrarCasoTieneUnHijo(typename ABB<T>::Nodo* pb);
		void BorrarCasoTieneDosHijos(typename ABB<T>::Nodo* pb);
		bool EsHijoDerecho(typename ABB<T>::Nodo* pbpadre, int pbclave);
		bool TieneHijoDerecho(typename ABB<T>::Nodo* pb);
		typename ABB<T>::Nodo* BuscarNodoMasIzq(typename ABB<T>::Nodo* der);
		void AcomodoNodoMasIzq(typename ABB<T>::Nodo* pb, typename ABB<T>::Nodo* masizq);

};



/*************************************************************
*                    IMPLEMENTACION ABB                      *
**************************************************************/

template <typename T>
ABB<T>::ABB(){
	this->raiz = NULL;
	this->masChico = NULL;
	this->cantnodos = 0;
}

template <typename T>
ABB<T>::ABB(const ABB<T>& otro){
	this->raiz = NULL;
	this->masChico = NULL;
	this->cantnodos = 0;

	if (otro.cantnodos > 0){
		Nodo* b = otro.raiz;
		AgregarNodos(b);
	}
}

template <typename T>
ABB<T>::~ABB(){
	if (this->raiz != NULL){
		BorrarArbol(this->raiz);
		this->cantnodos = 0;
	}
}

template <typename T>
void ABB<T>::Definir(int clave, T& sign){
	typename ABB<T>::Nodo* nuevonodo = new Nodo(clave, sign);

	if (!Definido(clave)){ //no esta definido, lo agrego
		
		if (this->raiz == NULL){
			this->raiz = nuevonodo;
			this->masChico = nuevonodo;

		} else {
			typename ABB<T>::Nodo* npapa = BuscaNodoParaInsertar(clave);
			if (clave < npapa->clave && npapa->hizq == NULL) {
				npapa->hizq = nuevonodo;
				nuevonodo->padre = npapa;
			} else if (clave > npapa->clave && npapa->hder == NULL){
				npapa->hder = nuevonodo;
				nuevonodo->padre = npapa;
			}

			//tengo que ver la clave, si es mas chica que la de this->masChico
			//entonces tengo que apuntar al nuevo
			if(clave < this->masChico->clave){
				this->masChico = nuevonodo;
			}
		}

		this->cantnodos++;

	} else { //esta definido, lo piso

		typename ABB<T>::Nodo* npapa = BuscaNodoParaInsertar(clave);
		if (clave < npapa->clave && npapa->hizq == NULL) {
			npapa->hizq = nuevonodo;
		} else if (clave > npapa->clave && npapa->hder == NULL){
			npapa->hder = nuevonodo;
		}

		if(clave < this->masChico->clave){
			this->masChico = nuevonodo;
		}
	}
}

template <typename T>
bool ABB<T>::Definido(int clave){
	return BuscaNodo(clave) != NULL;
}

template <typename T>
T& ABB<T>::Obtener(int clave){
	assert(Definido(clave));
	return BuscaNodo(clave)->sign;
}

template <typename T>
void ABB<T>::Borrar(int clave){

	if (Definido(clave)){
		Nodo* paraborrar = BuscaNodo(clave);

		//reviso si borro la clave mas chica.
		if(this->masChico->clave == clave){
			//voy a borrar el mas chico
			if(TieneHijoDerecho(this->masChico)){
				this->masChico = BuscarNodoMasIzq(this->masChico->hder);
			
			} else if(this->masChico->padre != NULL){ //no tiene hijo derecho, tiene padre??
				this->masChico = this->masChico->padre;
			
			} else { //no tiene hijo derecho ni padre, es null
				this->masChico = NULL;
			}
		}

		if (NoTieneHijos(paraborrar)){

			BorrarCasoNoTieneHijos(paraborrar);

		} else if (TieneUnHijo(paraborrar)){

			BorrarCasoTieneUnHijo(paraborrar);

		} else {
		
			BorrarCasoTieneDosHijos(paraborrar);

		}

		this->cantnodos--;
		delete paraborrar;
	}
}

template <typename T>
int ABB<T>::CantClaves(){
	return this->cantnodos;
}

template <typename T>
bool ABB<T>::EsVacio(){
	return this->raiz == NULL && this->cantnodos == 0;
}

template <typename T>
int ABB<T>::Raiz(){
// requiere !EsVacio()
	assert(!EsVacio());
	return this->raiz->clave;
}

template <typename T>
int ABB<T>::Altura(){
	return (Niveles()-1);
}

template <typename T>
int ABB<T>::Niveles(){
	if (this->raiz == NULL){
		return 1;
	} else {
		return NivelesDyC(this->raiz);
	}
}

template <typename T>
bool ABB<T>::EsCompleto(){
	if (EsVacio()){
		return true;
	} else {
		return (CantidadNodosAlturaMax() == DosALaAltura());
	}
}

template <typename T>
void ABB<T>::Inorder(){
	cout << endl << endl << "INORDER" << endl;
	
	if (EsVacio()){
		cout << "Esta vacio.";
	} else {
		InorderDyC(cout, this->raiz);
	}
}

template <typename T>
void ABB<T>::Preorder(){
	cout << endl << endl << "PREORDER" << endl;
	
	if (EsVacio()){
		cout << "Esta vacio.";
	} else {
		PreorderDyC(cout, this->raiz);
	}
}

template <typename T>
void ABB<T>::Postorder(){
	cout << endl << endl << "POSTORDER" << endl;
	
	if (EsVacio()){
		cout << "Esta vacio.";
	} else {
		PostorderDyC(cout, this->raiz);
	}
}

template <typename T>
bool ABB<T>::operator==(const ABB<T>& otro){
	bool res =  this->cantnodos == otro.cantnodos && 
				((this->masChico == NULL && otro.masChico == NULL) ||
				(this->masChico != NULL && otro.masChico != NULL &&
				 this->masChico->clave == otro.masChico->clave &&
				 this->masChico->sign == otro.masChico->sign));
	
	if (res && this->cantnodos > 0)
		 res = OperAsignacionDyC(this->raiz, otro.raiz);
	
	return res;
}

template <typename T>
bool ABB<T>::operator!=(const ABB<T>& otro){
	return !(*this == otro);
}

template <typename T>
ABB<T>& ABB<T>::operator=(const ABB<T>& otro){
	if (*this == otro) return *this;

	if (!EsVacio()) {
		Nodo* a = this->raiz;
		this->raiz = NULL;
		this->masChico = NULL;
		BorrarArbol(a);
		this->cantnodos = 0;
	}
	
	if (otro.cantnodos > 0){
		Nodo* b = otro.raiz;
		AgregarNodos(b);
		this->cantnodos = otro.cantnodos;
	}

	return *this;
}

template <typename TT>
ostream& operator<<(ostream& os, const ABB<TT>& tree){
	os << endl << endl;
	
	if (tree.cantnodos > 0){
		ABB<TT> t = tree;
		typename ABB<TT>::Nodo* a = tree.raiz;

		os << "INORDER: ";
		t.InorderDyC(os, a);

		a = tree.raiz;

		os << endl << "PREORDER: ";
		t.PreorderDyC(os, a);

		a = tree.raiz;

		os << endl << "POSTORDER: ";
		t.PostorderDyC(os, a);

	} else {
		os << "ARBOL VACIO";
	}

	os << endl << endl;
	return os;
}

template <typename T>
typename ABB<T>::Iterador ABB<T>::CrearIt(){
	return Iterador(this, this->masChico);
}

template <typename T>
typename ABB<T>::const_Iterador ABB<T>::CrearItConst(){
	return const_Iterador(CrearIt());
}

template <typename T>
typename ABB<T>::Nodo* ABB<T>::BuscaNodoParaInsertar(int clave){
	typename ABB<T>::Nodo* buscanodo = this->raiz;
	typename ABB<T>::Nodo* nodores = NULL;

	while (buscanodo != NULL && nodores == NULL){
		if (clave < buscanodo->clave && buscanodo->hizq != NULL){
			buscanodo = buscanodo->hizq;
		} else if (clave > buscanodo->clave && buscanodo->hder != NULL){
			buscanodo = buscanodo->hder;
		} else if ((clave > buscanodo->clave && buscanodo->hder == NULL) ||
					(clave < buscanodo->clave && buscanodo->hizq == NULL) ){
			nodores = buscanodo;
		}
	}
	return nodores;
}

template <typename T>
typename ABB<T>::Nodo* ABB<T>::BuscaNodo(int clave){
	typename ABB<T>::Nodo* buscanodo = this->raiz;

	while (buscanodo != NULL && buscanodo->clave != clave)
		buscanodo = clave < buscanodo->clave ? buscanodo->hizq : buscanodo->hder;
	return buscanodo;
}

template <typename T>
void ABB<T>::BorrarArbol(typename ABB<T>::Nodo* a){
	if (a->hizq != NULL && a->hder == NULL){
		BorrarArbol(a->hizq);
	} else if (a->hizq == NULL && a->hder != NULL){
		BorrarArbol(a->hder);
	} else if (a->hizq != NULL && a->hder != NULL){
		BorrarArbol(a->hizq);
		BorrarArbol(a->hder);
	}
	delete a;
}

template <typename T>
bool ABB<T>::NoTieneHijos(typename ABB<T>::Nodo* pb){
	return (pb->hder == NULL && pb->hizq == NULL);
}

template <typename T>
void ABB<T>::BorrarCasoNoTieneHijos(typename ABB<T>::Nodo* pb){
	if (pb->padre == NULL){
		this->raiz = NULL;

	} else {

		if (EsHijoDerecho(pb->padre, pb->clave)){
			pb->padre->hder = NULL;

		} else {
			pb->padre->hizq = NULL;
		} //end if interno
	}
}

template <typename T>
bool ABB<T>::TieneUnHijo(typename ABB<T>::Nodo* pb){
	return ((pb->hder != NULL && pb->hizq == NULL) ||
			(pb->hder == NULL && pb->hizq != NULL));
}

template <typename T>
void ABB<T>::BorrarCasoTieneUnHijo(typename ABB<T>::Nodo* pb){
	if (pb->padre == NULL){ // no tiene padre

		if (TieneHijoDerecho(pb)){
			this->raiz = pb->hder;
			pb->hder->padre = NULL;

		} else {
			this->raiz = pb->hizq;
			pb->hizq->padre = NULL;
		}

	} else { // tiene padre

		if (TieneHijoDerecho(pb)){
			
			if (EsHijoDerecho(pb->padre, pb->clave)){
				pb->padre->hder = pb->hder;
			} else {
				pb->padre->hizq = pb->hder;
			}

			pb->hder->padre = pb->padre;

		} else {
			
			if (EsHijoDerecho(pb->padre, pb->clave)){
				pb->padre->hder = pb->hizq;
			} else {
				pb->padre->hizq = pb->hizq;
			}

			pb->hizq->padre = pb->padre;

		}

	}
}

template <typename T>
void ABB<T>::BorrarCasoTieneDosHijos(typename ABB<T>::Nodo* pb){
	ABB<T>::Nodo* masizq = BuscarNodoMasIzq(pb->hder);

	// acomodo hijos
	// si el nodo masizq es hijo de pb
	if (pb->hder->clave == masizq->clave){

		masizq->hizq = pb->hizq;
		pb->hizq->padre = masizq;

	} else { // si el nodo masizq NO es hijo de pb

		AcomodoNodoMasIzq(pb, masizq);
	}
	
	// acomodo el padre de pb y masizq
	if (pb->padre == NULL){
		masizq->padre = NULL;
		this->raiz = masizq;

	} else {
		masizq->padre = pb->padre;
		
		if (EsHijoDerecho(pb->padre, pb->clave)){
			pb->padre->hder = masizq;
		} else {
			pb->padre->hizq = masizq;

		} //end if interno
	}

}

template <typename T>
bool ABB<T>::EsHijoDerecho(typename ABB<T>::Nodo* pbpadre, int pbclave){
	return (pbpadre->hder != NULL && pbpadre->hder->clave == pbclave);
}

template <typename T>
bool ABB<T>::TieneHijoDerecho(typename ABB<T>::Nodo* pb){
	return (pb->hder != NULL);
}

template <typename T>
typename ABB<T>::Nodo* ABB<T>::BuscarNodoMasIzq(typename ABB<T>::Nodo* der){
	Nodo* buscanodo = der;
	
	if (buscanodo != NULL){
		while (buscanodo->hizq != NULL) buscanodo = buscanodo->hizq;
	}

	return buscanodo;
}

template <typename T>
void ABB<T>::AcomodoNodoMasIzq(typename ABB<T>::Nodo* pb, typename ABB<T>::Nodo* masizq){

	// el hijo que puede tener es el derecho
	if (TieneUnHijo(masizq)){

		masizq->hder->padre = masizq->padre;
		masizq->padre->hizq = masizq->hder;

	} else { // no tiene hijo

		masizq->padre->hizq = NULL;
		masizq->padre = NULL;
	}

	// acomodo los hijos de pb con masizq
	masizq->hder = pb->hder;
	pb->hder->padre = masizq;
	masizq->hizq = pb->hizq;
	pb->hizq->padre = masizq;
}

template <typename T>
int ABB<T>::NivelesDyC(typename ABB<T>::Nodo* a){
	if (NoTieneHijos(a)){
		return 1;

	} else if (TieneUnHijo(a)){
		
		if (TieneHijoDerecho(a)){
			return (1 + NivelesDyC(a->hder));
		} else {
			return (1 + NivelesDyC(a->hizq));
		}

	} else {

		return (1 + Max(NivelesDyC(a->hizq), NivelesDyC(a->hder)) );
	}
}

template <typename T>
int ABB<T>::Max(int a, int b){
	if (a < b){
		return b;
	} else {
		return a;
	}
}

template <typename T>
int ABB<T>::CantidadNodosAlturaMax(){
	return CNAMDyC(this->raiz, Altura());
}

template <typename T>
int ABB<T>::CNAMDyC(typename ABB<T>::Nodo* a, int n){
	if (NoTieneHijos(a) && n != 0){
		return 0;

	} else if (NoTieneHijos(a) && n == 0){
		return 1;

	} else if (TieneUnHijo(a)){
		return 0;

	} else {

		return (CNAMDyC(a->hizq, n-1) + CNAMDyC(a->hder, n-1));
	}

}

template <typename T>
int ABB<T>::DosALaAltura(){
	return DALAaux(Altura());
}

template <typename T>
int ABB<T>::DALAaux(int n){
	int i = n, res=1;

	while (i>0){
		res *= 2;
		i--;
	}
	return res;
}

template <typename T>
void ABB<T>::InorderDyC(ostream& os, typename ABB<T>::Nodo* a){
	// inorder(izq(a)) raiz(a) inorder(der(a))

	if (NoTieneHijos(a)){
		os << a->clave << " ";

	} else if (TieneUnHijo(a)){

		if (TieneHijoDerecho(a)){
			os << a->clave << " ";
			InorderDyC(os, a->hder);
		} else {
			InorderDyC(os, a->hizq);
			os << a->clave << " ";
		} // end if interno

	} else {
		InorderDyC(os, a->hizq);
		os << a->clave << " ";
		InorderDyC(os, a->hder);
	}
}

template <typename T>
void ABB<T>::PreorderDyC(ostream& os, typename ABB<T>::Nodo* a){
	// raiz(a) preorder(izq(a)) preorder(der(a))

	if (NoTieneHijos(a)){
		os << a->clave << " ";

	} else if (TieneUnHijo(a)){

		if (TieneHijoDerecho(a)){
			os << a->clave << " ";
			PreorderDyC(os, a->hder);
		} else {
			os << a->clave << " ";
			PreorderDyC(os, a->hizq);
		} // end if interno

	} else {
		os << a->clave << " ";
		PreorderDyC(os, a->hizq);
		PreorderDyC(os, a->hder);
	}
}

template <typename T>
void ABB<T>::PostorderDyC(ostream& os, typename ABB<T>::Nodo* a){
	// postorder(izq(a)) postorder(der(a)) raiz(a) 

	if (NoTieneHijos(a)){
		os << a->clave << " ";

	} else if (TieneUnHijo(a)){

		if (TieneHijoDerecho(a)){
			PostorderDyC(os, a->hder);
			os << a->clave << " ";
		} else {
			PostorderDyC(os, a->hizq);
			os << a->clave << " ";
		} // end if interno

	} else {
		PostorderDyC(os, a->hizq);
		PostorderDyC(os, a->hder);
		os << a->clave << " ";
	}
}

template <typename T>
bool ABB<T>::OperAsignacionDyC(typename ABB<T>::Nodo* a, typename ABB<T>::Nodo* b){
	
	if (NoTieneHijos(a) && NoTieneHijos(b)){
		return (a->clave == b->clave && a->sign == b->sign);

	} else if (TieneUnHijo(a) && TieneUnHijo(b)){

		if (TieneHijoDerecho(a) && TieneHijoDerecho(b)){
			
			return (a->clave == b->clave && a->sign == b->sign &&
					OperAsignacionDyC(a->hder, b->hder));

		} else if (TieneHijoIzquierdo(a) && TieneHijoIzquierdo(b)){
			
			return (a->clave == b->clave && a->sign == b->sign &&
					OperAsignacionDyC(a->hizq, b->hizq));

		} else {
			return false;
		}

	} else if (TieneDosHijos(a) && TieneDosHijos(b)){
		
		return (a->clave == b->clave && a->sign == b->sign &&
				OperAsignacionDyC(a->hizq, b->hizq) &&
				OperAsignacionDyC(a->hder, b->hder));

	} else {
		return false;
	}

}

template <typename T>
bool ABB<T>::TieneDosHijos(typename ABB<T>::Nodo* a){
	return (a->hder != NULL && a->hizq != NULL);
}

template <typename T>
bool ABB<T>::TieneHijoIzquierdo(typename ABB<T>::Nodo* a){
	return (a->hizq != NULL);
}

template <typename T>
void ABB<T>::AgregarNodos(typename ABB<T>::Nodo* b){
	Definir(b->clave, b->sign);

	if (TieneHijoDerecho(b)) AgregarNodos(b->hder);

	if (TieneHijoIzquierdo(b)) AgregarNodos(b->hizq);

}

template <typename T>
typename ABB<T>::Nodo* ABB<T>::BuscoNodoMasDerecha(typename ABB<T>::Nodo* a){
	while (a->hder != NULL) a = a->hder;
	
	return a;
}



/*************************************************************
*           IMPLEMENTACION ITERADOR MODIFICABLE              *
**************************************************************/

template <typename T>
bool ABB<T>::Iterador::HaySiguiente(){
	return paiter != NULL;
}

template <typename T>
int ABB<T>::Iterador::SiguienteClave(){
	return paiter->clave;
}

template <typename T>
T& ABB<T>::Iterador::SiguienteSignificado(){
	return paiter->sign;
}

template <typename T>
bool ABB<T>::Iterador::HayAnterior(){
	return pbiter != NULL;
}

template <typename T>
int ABB<T>::Iterador::AnteriorClave(){
	return pbiter->clave;
}

template <typename T>
T& ABB<T>::Iterador::AnteriorSignificado(){
	return pbiter->sign;
}

template <typename T>
void ABB<T>::Iterador::Avanzar(){

	if (paiter == NULL){
		// termino de iterar y vuelvo a iterar
		
		paiter = arboliter->masChico;
		pbiter = NULL;

	} else if (arboliter->TieneHijoDerecho(paiter)){
		// si el nodo actual tiene un hijo derecho, me muevo a el y luego
		// a la izquierda hasta el ultimo izquierdo.

		//actualizo el anterior
		pbiter = paiter;
		paiter = arboliter->BuscarNodoMasIzq(paiter->hder);

	} else if ( !arboliter->TieneHijoDerecho(paiter) ){
		// no tiene hijo derecho entonces subo hasta encontrar que es hijo
		// izquierdo de algun nodo.

		pbiter = paiter;
		
		paiter = BuscoNodoSiguiente(paiter);

		if (paiter == NULL){
			// no tiene nodo siguiente, o sea era el ultimo.
			// vuelvo a iterar

			paiter = arboliter->masChico;
			pbiter = NULL;
		}

	}

}

template <typename T>
void ABB<T>::Iterador::Retroceder(){
	// si es igual a NULL comienza a iterar el iterador.
	// No esta hecho circular.

	if (pbiter != NULL){
		paiter = pbiter;
		
		if (arboliter->TieneHijoIzquierdo(pbiter)){
			pbiter = arboliter->BuscoNodoMasDerecha(pbiter->hizq);

		} else {
			pbiter = BuscoNodoAnterior(pbiter);
		}
	}
}

template <typename T>
bool ABB<T>::Iterador::operator==(const typename ABB<T>::Iterador& otro){
	return (arboliter == otro.arboliter &&
			paiter == otro.paiter &&
			pbiter == otro.pbiter);
}

template <typename T>
bool ABB<T>::Iterador::operator!=(const typename ABB<T>::Iterador& otro){
	return !(*this == otro);
}

template <typename T>
typename ABB<T>::Nodo* ABB<T>::Iterador::BuscoNodoSiguiente(typename ABB<T>::Nodo* pa){
	if (EsHijoIzquierdo(pa)){
		pa = pa->padre;

	} else {
		Nodo* nodopadre = pa->padre;
		while (nodopadre != NULL && nodopadre->hder->clave == pa->clave){
			nodopadre = nodopadre->padre;
			pa = pa->padre;
		}
		pa = nodopadre;

	}

	return pa;
}

template <typename T>
bool ABB<T>::Iterador::EsHijoIzquierdo(typename ABB<T>::Nodo* pa){
	return (pa->padre != NULL &&
			pa->padre->hizq != NULL &&
		    pa->padre->hizq->clave == pa->clave);

}

template <typename T>
typename ABB<T>::Nodo* ABB<T>::Iterador::BuscoNodoAnterior(typename ABB<T>::Nodo* pb){
	if (!EsHijoIzquierdo(pb)){
		// es hijo derecho
		pb = pb->padre;
	
	} else {
		// es hijo izquierdo
		Nodo* nodopadre = pb->padre;
		while (nodopadre != NULL && nodopadre->hizq->clave == pb->clave){
			nodopadre = nodopadre->padre;
			pb = pb->padre;
		}
		pb = nodopadre;
	}

	return pb;
}



/*************************************************************
*           IMPLEMENTACION ITERADOR NO MODIFICABLE           *
**************************************************************/

template <typename T>
bool ABB<T>::const_Iterador::HaySiguiente(){
	return itconst.HaySiguiente();
}

template <typename T>
int ABB<T>::const_Iterador::SiguienteClave(){
	return itconst.SiguienteClave();
}

template <typename T>
const T& ABB<T>::const_Iterador::SiguienteSignificado(){
	return itconst.SiguienteSignificado();
}

template <typename T>
bool ABB<T>::const_Iterador::HayAnterior(){
	return itconst.HayAnterior();
}

template <typename T>
int ABB<T>::const_Iterador::AnteriorClave(){
	return itconst.AnteriorClave();
}

template <typename T>
const T& ABB<T>::const_Iterador::AnteriorSignificado(){
	return itconst.AnteriorSignificado();
}

template <typename T>
void ABB<T>::const_Iterador::Avanzar(){
	itconst.Avanzar();
}

template <typename T>
void ABB<T>::const_Iterador::Retroceder(){
	itconst.Retroceder();
}

template <typename T>
bool ABB<T>::const_Iterador::operator==(const typename ABB<T>::const_Iterador& otro){
	return itconst == otro.itconst;
}

template <typename T>
bool ABB<T>::const_Iterador::operator!=(const typename ABB<T>::const_Iterador& otro){
	return itconst != otro.itconst;
}
