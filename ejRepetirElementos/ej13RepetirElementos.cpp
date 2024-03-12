
/*
 * ---------------------------------------------------
 *            Solución a la práctica L02
 * ---------------------------------------------------
 *             Manuel Montenegro Montes
 * ---------------------------------------------------
 */


#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 


 /*
   Implementación de listas enlazadas simples vista en clase.

   https://github.com/manuelmontenegro/ED/tree/main/lineales/list_linked_single_v2

   En este caso, los valores contenidos en los nodos no son de tipo entero,
   sino de tipo char, porque es lo que requiere el ejercicio. En la Semana 4
   veremos cómo hacer que una misma implementación del TAD Lista pueda
   aplicarse a distintos tipos de elementos (int, char, string, etc.)
 */
class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }

    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    void replicate(const ListLinkedSingle& ys);


private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}




// Coste: lineal con respecto a la longitud de la lista this y la que entra como parametro: O(n*max(ys)) 
// ya que el bucle externo realiza n iteraciones donde n = longitud de la lista this y el bucle interno (realizado a veces) 
// da, como cota superior, el numero maximo presente en la lista parametro iteraciones, cada una de coste constante.

void ListLinkedSingle::replicate(const ListLinkedSingle& ys) {
    Node* curr = head;
    Node* prev = head;
    Node* mult = ys.head;

    head = nullptr; //cabeza a null dando por hecho que ys va a tener un cero como primer elemento, si no es el caso,
    // actualizo la cabeza abajo

    //caso vacio controlado por defecto

    while (curr != nullptr) {
        if (mult->value == 0) {
            Node* aux = curr;
            curr = curr->next;
            delete aux;
            prev->next = curr;
        } //elimino el nodo, paso al siguiente
        else if (mult->value == 1) {
            if (head == nullptr) head = curr;
            prev = curr;
            curr = curr->next;
        } //no hago nada, paso al siguiente
        else { //doy por hecho que mult->value >= 2
            if (head == nullptr) head = curr;
            prev = curr;
            for (int i = 0; i < mult->value - 1; i++) {
                Node* dupe = new Node{ curr->value, prev->next };
                prev->next = dupe;
                prev = dupe;
            }
            curr = prev->next;
        }
        mult = mult->next;
    }
}


using namespace std;


void tratar_caso() {
    ListLinkedSingle l, dest;
    int size, num;
    cin >> size;
    for (int i = 0; i < size; i++) {
        cin >> num;
        l.push_front(num);
    }

    for (int i = 0; i < size; i++) {
        cin >> num;
        dest.push_front(num);
    }

    l.replicate(dest);
    l.display();
    cout << endl;

}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}