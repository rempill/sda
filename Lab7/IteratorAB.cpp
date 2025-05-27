#include "AB.h"
#include "IteratorAB.h"

IteratorInordine::IteratorInordine(const AB& _ab):ab(_ab),current(nullptr) {}

void IteratorInordine::prim(){
	while(!stack.empty()) {
		stack.pop(); // golim stiva pentru a incepe de la radacina
	}
    current=ab.root;
    goLeft(current); // mergem la cel mai din stanga nod
    if(!stack.empty()){
      current = stack.top(); // setam current la nodul de sus din stiva
    }
    else{
      current = nullptr; // daca stiva e goala, current devine nullptr
	}
}

bool IteratorInordine::valid(){
	return current != nullptr;
}

TElem IteratorInordine::element() {
	if(!valid()) {
		throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	}
    return current->e; // returneaza elementul curent
}

void IteratorInordine::urmator(){
	if(!valid()) throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	PNod nod=stack.top(); stack.pop();
    if(nod->dr != nullptr) {
      goLeft(nod->dr); // mergem la subarborele drept
    }
    current=stack.empty() ? nullptr : stack.top(); // actualizam current
}

void IteratorInordine::goLeft(PNod nod) {
	while (nod != nullptr) {
		stack.push(nod);
		nod = nod->st;
	}
}

IteratorPreordine::IteratorPreordine(const AB& _ab):ab(_ab){
}

void IteratorPreordine::prim(){
 	while(!stack.empty()){
        stack.pop(); // golim stiva pentru a incepe de la radacina
 	}
    if(ab.root!= nullptr) {
		stack.push(ab.root); // adaugam radacina in stiva
	}
}


bool IteratorPreordine::valid(){
	return !stack.empty(); // verifica daca stiva nu este goala
}

TElem IteratorPreordine::element(){
	if(!valid()) {
		throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	}
    return stack.top()->e; // returneaza elementul din varful stivei
}

void IteratorPreordine::urmator(){
	if(!valid()){
        throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	}
    PNod nod=stack.top(); // preluam nodul curent
	if(nod->dr!=nullptr){
		stack.push(nod->dr); // adaugam subarborele drept in stiva
	}
    if(nod->st!=nullptr){
      stack.push(nod->st); // adaugam subarborele stang in stiva
    }
}

IteratorPostordine::IteratorPostordine(const AB& _ab):ab(_ab){
	current = nullptr;
	lastVisited= nullptr; // initializam lastVisited
}

void IteratorPostordine::prim(){
	while(!stack.empty()) {
		stack.pop(); // golim stiva pentru a incepe de la radacina
	}
	goLeftMost(ab.root);
	if (!stack.empty()) {
		current=stack.top();
	}
	else {
		current = nullptr;
	}
	lastVisited=nullptr;
}


bool IteratorPostordine::valid(){
	return current != nullptr; // verifica daca current nu este nullptr
}

TElem IteratorPostordine::element(){
	if(!valid()) {
		throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	}
	return current->e; // returneaza elementul curent
}

void IteratorPostordine::urmator(){
	if (!valid()) {
		throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	}
	PNod nod=stack.top(); stack.pop(); // preluam nodul curent
	lastVisited=nod;
	if (!stack.empty()) {
		PNod top = stack.top();
		if (top->st==nod && top->dr != nullptr) {
			// daca nodul curent este stangul lui top si top are drept
			goLeftMost(top->dr); // mergem la subarborele drept
		}
	}
	current=stack.empty() ? nullptr : stack.top();
}

void IteratorPostordine::goLeftMost(PNod nod){
	while(nod!=nullptr){
        stack.push(nod);
        if(nod->st!=nullptr){
			nod=nod->st; // mergem la subarborele stang
		} else {
			nod=nod->dr; // daca nu exista stang, mergem la drept
		}
    }
}

IteratorLatime::IteratorLatime(const AB& _ab):ab(_ab){
}

void IteratorLatime::prim(){
	while (!queue.empty()) {
		queue.pop(); // golim coada pentru a incepe de la radacina
	}
	if (ab.root != nullptr) {
		queue.push(ab.root);
	}
}


bool IteratorLatime::valid(){
	return queue.empty();
}

TElem IteratorLatime::element(){
	if (!valid()) {
		throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	}
	return queue.front()->e; // returneaza elementul din fata cozii
}

void IteratorLatime::urmator(){
	if (!valid()) {
		throw std::exception(); // arunca exceptie daca iteratorul nu e valid
	}
	PNod nod=queue.front(); queue.pop(); // preluam nodul curent
	if (nod->st != nullptr) {
		queue.push(nod->st); // adaugam subarborele stang in coada
	}
	if (nod->dr != nullptr) {
		queue.push(nod->dr); // adaugam subarborele drept in coada
	}
}
