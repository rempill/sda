#include <assert.h>

#include "DO.h"
#include "Iterator.h"
#include <exception>
using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void test1(){
	DO dictOrd = DO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
	dictOrd.adauga(1,2);
	assert(dictOrd.dim() == 1);
	assert(!dictOrd.vid());
	assert(dictOrd.cauta(1)!=null_value);
	TValoare v =dictOrd.adauga(1,3);
	assert(v == 2);
	assert(dictOrd.cauta(1) == 3);
	auto it = dictOrd.iterator();
	it.first();
	while (it.valid()){
		TElem e = it.element();
		assert(e.second != null_value);
		it.next();
	}
	assert(dictOrd.sterge(1) == 3);
	assert(dictOrd.vid());
}

void testAll() {
	test1();
}