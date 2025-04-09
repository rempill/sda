#include "TestScurt.h"
#include <assert.h>
#include "../Proiect C++/Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4,4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1,1,5);
	assert(m.element(1,1) == 5);
	m.modifica(1,1,6);
	assert(m.element(1,2) == NULL_TELEMENT);
	auto it=m.begin();
	assert(it.current->data.value == 6);
	m.modifica(1,3,10);
	++it;
	assert(it.current->data.value == 10);
	++it;
	assert(it.current == nullptr);
}

void testTranspose() {
	Matrice m(5,5);
	m.modifica(0, 1, 1);
	m.modifica(1, 0, 2);
	m.modifica(2, 3, 3);
	m.modifica(3, 2, 4);
	m.modifica(4, 4, 5);
	m.transpose();
	assert(m.element(1, 0) == 1);
	assert(m.element(0, 1) == 2);
	assert(m.element(3, 2) == 3);
	assert(m.element(2, 3) == 4);
	assert(m.element(4, 4) == 5);
	m.transpose();
	assert(m.element(0, 1) == 1);
	assert(m.element(1, 0) == 2);
	assert(m.element(2, 3) == 3);
	assert(m.element(3, 2) == 4);
	assert(m.element(4, 4) == 5);
}