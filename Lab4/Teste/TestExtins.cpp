#include <exception>
#include <assert.h>
#include <algorithm>
#include <vector>
#include "Iterator.h"
#include "DO.h"
#include "TestExtins.h"

using namespace std;

bool cresc(TCheie c1, TCheie c2) {
	if (c1 <= c2) {
		return true;
	} else {
		return false;
	}
}

bool desc(TCheie c1, TCheie c2) {
	if (c1 >= c2) {
		return true;
	} else {
		return false;
	}
}

void testCreeaza() {
	DO d = DO(cresc);
	assert(d.dim() == 0);
	assert(d.vid());

	auto it = d.iterator();
	it.first();
	assert(!it.valid());

	for (int i = 0; i < 10; i++) {
		assert(d.cauta(i) == null_value);
	}

	for (int i = -10; i < 10; i++) {
		assert(d.sterge(i) == null_value);
	}
}

void testCauta(Relatie r) {
	DO d = DO(r);
	int cMin = 0;
	int cMax = 10;
	try {
		for (int i = cMin; i <= cMax; i++) {
			d.adauga(i, i + 1);
		}
		assert(true);
	} catch (exception&) {
		assert(false);
	}
	int intervalDim = 10;
	for (int i = cMin; i <= cMax; i++) {
		assert(d.cauta(i) == i + 1);
	}
	for (int i = cMin - intervalDim; i < cMin; i++) {
		assert(d.cauta(i) == null_value);
	}
	for (int i = cMax + 1; i < cMax + intervalDim; i++) {
		assert(d.cauta(i) == null_value);
	}
}

void testCauta() {
	testCauta(cresc);
	testCauta(desc);
}

//genereaza un vector continand in ordine aleatoare valorile naturale din intervalul inchis [cMin, cMax]
vector<int> cheiInOrdineAleatoare(int cMin, int cMax) {
	vector<int> chei;
	for (int c = cMin; c <= cMax; c++) {
		chei.push_back(c);
	}
	int n = chei.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(chei[i], chei[j]);
	}
	return chei;
}

void populeazaDOVidIdentic(DO& doc, int cMin, int cMax) {
	vector<int> chei = cheiInOrdineAleatoare(cMin, cMax);
	int n = chei.size();
	for (int i = 0; i < n; i++) {
		assert(doc.adauga(chei[i], chei[i]) == null_value);
	}
}

void rePopuleazaDOSh(DO& doc, int cMin, int cMax, int shift) {
	vector<int> chei = cheiInOrdineAleatoare(cMin, cMax);
	int n = chei.size();
	for (int i = 0; i < n; i++) {
		assert(doc.adauga(chei[i], chei[i] - shift) == chei[i]);
	}
}

void populeazaDOSh(DO& doc, int cMin, int cMax, int shift) {
	vector<int> chei = cheiInOrdineAleatoare(cMin, cMax);
	int n = chei.size();
	for (int i = 0; i < n; i++) {
		doc.adauga(chei[i], chei[i] - shift);
	}
}

void testAdaugaSiCauta(Relatie r) {
	DO d = DO(r);
	int cMin = 100;
	int cMax = 200;

	populeazaDOVidIdentic(d, cMin, cMax);
	for (int c = cMin; c <= cMax; c++) {
		assert(d.cauta(c) == c);
	}
	assert(d.dim() == (cMax - cMin + 1));

	rePopuleazaDOSh(d, cMin, cMax, 1);
	assert(d.dim() == (cMax - cMin + 1));

	populeazaDOSh(d, 2 * cMax, 3 * cMax, 2 * cMax - cMin);
	for (int c = 2 * cMax; c <= 3 * cMax; c++) {
		assert(d.cauta(c) == c - 2 * cMax + cMin);
	}
	assert(d.dim() == (cMax - cMin + 1) + (cMax + 1));

	auto it = d.iterator();
	it.first();
	if (it.valid()) {
		TCheie cPrec = it.element().first;
		assert(d.cauta(cPrec) != null_value);
		it.next();
		while (it.valid()) {
			TCheie c = it.element().first;
			assert(r(cPrec, c));
			assert(d.cauta(c) != null_value);
			cPrec = c;
			it.next();
		}
	}

}

void testAdauga() {
	testAdaugaSiCauta(cresc);
	testAdaugaSiCauta(desc);
}

void testStergeCauta(Relatie r) {
	DO d = DO(r);
	int cMin = 10;
	int cMax = 20;
	populeazaDOVidIdentic(d, cMin, cMax);
	for (int c = cMax + 1; c <= 2 * cMax; c++) {
		assert(d.sterge(c) == null_value);
	}
	int dim = cMax - cMin + 1;
	assert(d.dim() == dim);
	for (int c = cMin; c <= cMax; c++) {
		assert(d.sterge(c) == c);
		assert(d.cauta(c) == null_value);

		auto it = d.iterator();
		it.first();
		if (it.valid()) {
			TCheie cPrec = it.element().first;
			it.next();
			while (it.valid()) {
				TCheie c = it.element().first;
				assert(r(cPrec, c));
				cPrec = c;
				it.next();
			}
		}

		dim--;
		assert(d.dim() == dim);

	}

	for (int c = cMin; c <= cMax; c++) {
		assert(d.sterge(c) == null_value);
	}
	assert(d.vid());
	assert(d.dim() == 0);

}

void testSterge() {
	testStergeCauta(cresc);
	testStergeCauta(desc);
}

void testIterator(Relatie r) {
	DO d = DO(r);
	auto it = d.iterator();
	assert(!it.valid());
	it.first();
	assert(!it.valid());
	int cMin = 100;
	int cMax = 300;
	vector<int> chei = cheiInOrdineAleatoare(cMin, cMax);
	int n = chei.size();
	for (int i = 0; i < n; i++) {
		assert(d.adauga(chei[i], chei[n - i - 1]) == null_value);
	}

	auto itD = d.iterator();
	assert(itD.valid());
	itD.first();
	assert(itD.valid());

	TCheie cPrec = itD.element().first;
	for (int i=1; i<100; i++){
		assert(cPrec == itD.element().first);
	}
    itD.next();
	while (itD.valid()) {
		TCheie c = itD.element().first;
		assert(cMin <= c && c <= cMax);
		assert(d.cauta(c) != null_value);
		assert(r(cPrec, c));
		cPrec = c;
		itD.next();
	}
}

void testCantitativ(){
	DO d = DO(cresc);
	int cMin = -3000;
	int cMax = 3000;
	vector<int> chei  = cheiInOrdineAleatoare(cMin, cMax);
    populeazaDOVidIdentic(d, cMin, cMax);
    for (int c = cMin; c <= cMax; c++){
      	assert(d.cauta(c) == c);
    }
    assert(d.dim() == cMax - cMin + 1);
    auto it  = d.iterator();
    assert(it.valid());
    it.first();
    assert(it.valid());
    for (int i = 0; i < d.dim(); i++) {
    	it.next();
    }
    assert(!it.valid());
    it.first();
    while (it.valid()){
    	TCheie c = it.element().first;
    	assert(d.cauta(c) == c);
        TValoare v  = it.element().second;
        assert(c == v);
        it.next();
    }
    assert(!it.valid());
    for (int c = cMin-100; c <= cMax+100; c++){
         d.sterge(c);
         assert(d.cauta(c) == null_value);
    }
    assert(d.dim() == 0);
    assert(d.vid());
}

void testIterator() {
	testIterator(cresc);
	testIterator(desc);
}

void testAllExtins() {
	testCreeaza();
	testAdauga();
	testCauta();
	testSterge();
	testIterator();
	testCantitativ();
}
