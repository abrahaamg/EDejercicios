#include <utility>

template <class T> class BinTree {
public:
	bool empty() const;
	const T& root() const;
	BinTree<T> left() const;
	BinTree<T> right() const;
private:
};

template<typename T>
std::pair<bool, int> es_zurdo(const BinTree<T>& t) {
	if (t.empty()) return { true, 0 };
	else if (t.left().empty() && t.right().empty()) return { true, 1 };
	else {
		auto [es_zurdo_iz, num_nodos_iz] = es_zurdo(t.left());
		auto [es_zurdo_dr, num_nodos_dr] = es_zurdo(t.right());

		bool zurdo = es_zurdo_iz && es_zurdo_dr && num_nodos_iz > num_nodos_dr;
		int num_nodos = 1 + num_nodos_iz + num_nodos_dr;

		return { zurdo, num_nodos };
	}
}

void tratar_caso() {

}