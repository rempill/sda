#include "DO.h"
#include <iostream>

#include <exception>

#include "Iterator.h"
using namespace std;

DO::DO(Relatie relatie) {
	size=0;
	rel=relatie;
	capacity=init_capacity;
	elems=new TElem[capacity];
	next=new int[capacity];
	prev=new int[capacity];
	head=-1;
	//init lists
	for (int i=0;i<capacity;++i) {
		elems[i]={null_value,null_value};
		next[i]=-1;
		prev[i]=-1;
	}
	first_free=0;
}

void DO::resize() {
	int new_capacity = capacity * 2; // Double the capacity
	auto* new_elems = new TElem[new_capacity];
	int* new_next = new int[new_capacity];
	int* new_prev = new int[new_capacity];

	// Copy existing elements
	for (int i = 0; i < capacity; ++i) {
		new_elems[i] = elems[i];
		new_next[i] = next[i];
		new_prev[i] = prev[i];
	}

	// Initialize the new slots
	for (int i = capacity; i < new_capacity; ++i) {
		new_elems[i] = {null_value, null_value};
		new_next[i] = -1;
		new_prev[i] = -1;
	}

	// Update first_free
	first_free = capacity;

	// Delete old arrays
	delete[] elems;
	delete[] next;
	delete[] prev;

	// Update pointers and capacity
	elems = new_elems;
	next = new_next;
	prev = new_prev;
	capacity = new_capacity;
}

//functie de actualizare a primului liber
void DO::update_first_free() {
	first_free++;
	while (first_free<capacity && elems[first_free]!=std::make_pair(null_value,null_value) ) {
		first_free++;
	}
	if (first_free==capacity) {
		first_free=-1;
	}
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	IteratorDO it(*this);
	int prev_pos = -1;

	// Traverse the list
	while (it.valid() && rel(it.element().first, c)) {
		if (it.element().first == c) {
			// Key already exists, update its value
			TValoare old_value = it.element().second;
			elems[it.current].second = v;
			return old_value;
		}
		prev_pos = it.current;
		it.next();
	}

	// If the dictionary is full, throw exception
	if (first_free == -1) {
		resize();
	}

	// Insert the new element at the correct position
	elems[first_free] = {c, v};
	next[first_free] = it.current;
	prev[first_free] = prev_pos;

	if (prev_pos != -1) {
		next[prev_pos] = first_free;
	} else {
		head = first_free; // Update head if inserting at the beginning
	}

	if (it.valid()) {
		prev[it.current] = first_free;
	}

	// Update the first free position
	update_first_free();
	++size;

	return null_value;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	IteratorDO it(*this);
	while (it.valid()) {
		if (it.element().first == c) {
			return it.element().second;
		}
		it.next();
	}
	return null_value;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	IteratorDO it(*this);
	while (it.valid()) {
		if (it.element().first == c) {
			TValoare old_value = it.element().second;

			int current = it.current;

			// Update links
			if (prev[current] != -1) {
				next[prev[current]] = next[current];
			} else {
				head = next[current];
			}

			if (next[current] != -1) {
				prev[next[current]] = prev[current];
			}

			// Mark the slot as free
			elems[current] = {null_value, null_value};
			next[current] = -1;
			prev[current] = -1;

			if (first_free == -1 || current < first_free) {
				first_free = current;
			}

			--size;
			return old_value;
		}
		it.next();
	}
	return null_value; 
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return size;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	return size == 0;
}

IteratorDO DO::iterator() const{
	return IteratorDO(*this);
}

DO::~DO() = default;
