#include "Matrice.h"

#include <algorithm>
#include <exception>
#include <Matrice.h>

using namespace std;

#define INITIAL_CAPACITY 2
#define ALPHA 0.7
#define BETA 0.3

Matrice::Matrice(int m, int n) {
	this->rows=n;
	this->columns=m;
	this->capacity=INITIAL_CAPACITY;
	this->elements=LinkedList<triplet>();
	this->size=0;
}

bool Matrice::vida() const{
	return this->size==0;
}
// // Theta(n), nu exista caz favorabil sau defavorabil
// void Matrice::realloc(int capacity) {
// 	//realoca vectorul `elements` cu capacitatea `capacity`
// 	triplet *elements=new triplet[capacity];
// 	for (int i=0; i<min(this->size, capacity); i++) {
// 		//min asigura ca nu suprascriem adrese de memorie nealocate
// 		elements[i]=this->elements[i];
// 	}
// 	delete [] this->elements;
// 	this->elements=elements;
// 	this->capacity=capacity;
// }
/// nu e useless realloc la linked list makes no sense nu avem tad inlantuit ca la alocare dinamica?
//Tetha(1), nu exista caz favorabil sau defavorabil
int Matrice::nrLinii() const{
	return this->rows;
}

//Tetha(1), nu exista caz favorabil sau defavorabil
int Matrice::nrColoane() const{
	/* de adaugat */
	return this->columns;
}

// mediu: O(n), favorabil: tetha(1), defavorabil: tetha(n);
//arunca exceptie daca (i,j) nu e pozitie valida in Matrice sau daca e goala
TElem Matrice::element(int i, int j) const{
	/* de adaugat */
	if (i<0 || i>=this->rows || j<0 || j>=this->columns) {
		throw std::exception();
	}
	auto it=this->elements.begin();
	while (it.current) {
		if (it.current->data.row==i && it.current->data.column==j) {
			return it.current->data.value;
		}
		++it;
	}
	return NULL_TELEMENT;
}


//favorabil, defavorabil, mediu: Theta(n)
//arunca exceptie daca (i,j) nu e o pozitie valida in Matrice sau daca e goala
TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || i >= this->rows || j < 0 || j >= this->columns) {
		throw std::exception();
	}
	if (this->vida()) {
		this->elements.push_back(triplet{i, j, e	});
        this->size++;
        return NULL_TELEMENT;
    }
	auto it=this->elements.begin();
	while (it.current) {
		if (it.current->data.row == i && it.current->data.column == j) {
			TElem oldValue = it.current->data.value;
			it.current->data=triplet{i,j,e};
			return oldValue;
		}
		++it;
	}
	// if (this->size >= this->capacity) {
	// 	this->realloc(this->capacity * 2);
	// }
	// Find the correct position to insert the new element
	it=this->elements.begin();
	while (it.current) {
		if (it.current->data.row > i || (it.current->data.row == i && it.current->data.column >= j)) {
			break;
		}
		++it;
	}
	if (!it.current) {
        // Insert at the end
        this->elements.push_back(triplet{i, j, e});
        this->size++;
        return 1;
    }
	// Shift elements to the right to make space for the new element and inserts it
	this->elements.insert(triplet{i,j,e}, it);
	this->size++;
	return 1;
}

///
///functie transpose(this)
///iterator it <- elements.begin()
///cat timp it != elements.end()
///		swap(it->row, it->column)
///		it <- it + 1
///	sf cat timp
///	elements.sort(linie apoi coloana, folosind comparatorul a.column < b.column si a.row < b.row)
///	swap(nr linii, nr coloane)
///	sf functie transpose
///	complexity where n is the number of elements in the list: O(n log n), or more precisely O(n+ n log n)
void Matrice::transpose() {
	auto it = this->elements.begin();
	while (it != this->elements.end()) {
		std::swap(it->row, it->column);
		++it;
	}

	this->elements.sort([](const triplet& a, const triplet& b) {
		if (a.row == b.row) {
			return a.column < b.column;
		}
		return a.row < b.row;
	});
	std::swap(this->rows, this->columns);
}

Matrice::~Matrice()= default;

