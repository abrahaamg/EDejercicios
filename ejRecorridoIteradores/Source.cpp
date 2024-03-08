#include <list>
#include <iostream>
using namespace std;

void eliminar_pares(list<int>& list);
template <typename T>
bool ordenada_ascendente(const list<T>& list);
void display(const list<int>& lista);
bool es_palindromo(const string& cadena);


int main() {
	list<int> l;
	cout << es_palindromo("");

	return 0;
}

void display(const list<int>& lista) {
	for (auto x : lista) {
		cout << x << " ";
	}
}


void eliminar_pares(list<int>& list) {

	auto it = list.begin(); 
	while (it != list.end()) {
		if (*it % 2 == 0) {
			it = list.erase(it);
		}
		else {
			it++;
		}
	}
}

template <typename T>
bool ordenada_ascendente(const list<T>& list) {
	auto it = list.begin();
	if (it == list.end()) {
		return true;
	}
	auto it2 = ++list.begin();
	while (it2 != list.end() && *it <= *it2) {
		it++;
		it2++;
	}
	return it2 == list.end();
}

bool es_palindromo(const string& cadena) {
	auto it1 = cadena.begin();
	if (!cadena.empty()) {
		auto it2 = --cadena.end();

		while (it1 != it2 && it2 + 1 != it1 && *it1 == *it2) {
			it1++;
			it2--;
		}
		return *it1 == *it2;
	}
	else {
		return true;
	}
		
}

