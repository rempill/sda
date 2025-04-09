#pragma once
#include "LSI.h"
//#include "IteratorMatrice.h"
typedef int TElem;


#define NULL_TELEMENT 0

typedef struct {
	int row;
	int column;
	TElem value;
}triplet;

class Matrice {
private:
	TElem rows;
	TElem columns;
	LinkedList<triplet> elements;
	TElem capacity;
	TElem size;
	void realloc(TElem capacity);
public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;

	bool vida() const;

	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;

	LinkedList<triplet>::iterator begin() const {
		return this->elements.begin();
	}

	//transforma matricea initiala in transpusa ei
	void transpose();

	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

	//destructor
	~Matrice();

};







