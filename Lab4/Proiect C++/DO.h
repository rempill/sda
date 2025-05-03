#pragma once

typedef int TCheie;
typedef int TValoare;

#define init_capacity 10
#define null_value (-1)

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

typedef bool(*Relatie)(TCheie, TCheie);

/*Să se implementeze în C++ un anumit container de date (TAD) folosind o anumită
reprezentare (indicată) și o listă înlănțuită (LSI – lista simplu înlănțuită, LDI – lista dublu înlănțuită)
ca structură de date, cu reprezentarea înlănțuirilor pe tablou dinamic.
TAD Dictionar Ordonat – reprezentare sub forma unei LDI cu perechi (cheie, valoare) ordonate
în raport cu cheile și cu o relație de ordine  între chei .
*/
class IteratorDO;

class DO {
	friend class IteratorDO;
    private:
	Relatie rel;
	TElem* elems;
	int* next;
	int* prev;
	int head;
	int capacity;
	int size;
	int first_free;
	//upd first free
	void update_first_free();
    public:

	// constructorul explicit al dictionarului
	explicit DO(Relatie r);

	//resize func
	void resize();

	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	[[nodiscard]] TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	[[nodiscard]] int dim() const;

	//verifica daca dictionarul e vid
	[[nodiscard]] bool vid() const;

	[[nodiscard]] IteratorDO iterator() const;
	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	//Iterator iterator() const;

	// destructorul dictionarului
	~DO();

};
