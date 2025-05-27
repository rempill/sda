#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

Nod::Nod(TElem e,PNod st,PNod dr): e(e), st(st), dr(dr) {}

AB::AB() {
	root= nullptr;
}

AB::AB(const AB& ab) {
	root= copy(ab.root);
}

AB::AB(TElem e){
	root=new Nod(e, nullptr, nullptr);
}

AB::AB(const AB& st, TElem e, const AB& dr){
    root=new Nod(e, copy(st.root), copy(dr.root));
}


void AB::adaugaSubSt(const AB& st){
 	if(vid()){
          throw std::exception(); // arunca exceptie daca arborele este vid
          }
    destroySubtree(root->st);
    root->st = copy(st.root);
}

void AB::adaugaSubDr(const AB& dr){
	if(vid()){
		  throw std::exception(); // arunca exceptie daca arborele este vid
		  }
	destroySubtree(root->dr);
	root->dr = copy(dr.root);
}

TElem AB::element() const{
 		if (vid()) {
		throw std::exception(); // arunca exceptie daca arborele este vid
	}
	return root->e;
}

AB AB::stang() const{
 	if(vid()){
          throw std::exception(); // arunca exceptie daca arborele este vid
	}
    AB ab;
    ab.root=copy(root->st);
    return ab;
}

AB AB::drept() const{
	if(vid()){
          throw std::exception(); // arunca exceptie daca arborele este vid
	}
	AB ab;
	ab.root=copy(root->dr);
	return ab;
}

AB::~AB() {
	destroy(root);
}

bool AB::vid() const{
	return root == nullptr;
}

void AB::destroy(PNod nod) {
	if (nod != nullptr) {
		destroySubtree(nod->st);
		destroySubtree(nod->dr);
		delete nod;
	}
}

void AB::destroySubtree(PNod nod) {
	destroy(nod);
}

PNod AB::copy(PNod nod) const {
	if (nod == nullptr) {
		return nullptr;
	}
	return new Nod(nod->e, copy(nod->st), copy(nod->dr));
}

void AB::visit(PNod nod, PFunctie f) const {
	if (nod != nullptr) {
		f(nod->e);
		visit(nod->st, f);
		visit(nod->dr, f);
	}
}

IteratorAB* AB::iterator(string s) const {
	if (s=="preordine")
		return new IteratorPreordine(*this);
	if (s=="inordine")
		return new IteratorInordine(*this);
	if (s=="postordine")
		return new IteratorPostordine(*this);
	if (s=="latime")
		return new IteratorLatime(*this);
	return nullptr;
};
