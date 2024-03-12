#include <iostream>
#include <fstream>  
#include <cassert>
using namespace std;

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


    void mezclar(ListLinkedSingle& dest);


    void merge(ListLinkedSingle list) {
        Node* curr = this->head;
        Node* other = list.head;
        Node* prev;

        if (curr->value <= other->value) {
            prev = this->head;
            curr = head->next;
        }
        else {
            //
        }

        while (curr != nullptr && other != nullptr) {
            if (curr->value <= other->value) {
                prev->next = curr;
                prev = curr;
                curr = curr->next;
            }
            else {
                prev->next = other,
                    prev = other;
                other = other->next;
            }
        }
    }

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

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;

};

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

// El coste de mezclar es de O(N+M) = O(max(N,M)) donde N representa el numero de elementos de la lista this y M el numero de elementos de la lista list ya
// que en el caso peor se realizan N+M iteraciones cada una de coste constante

void ListLinkedSingle::mezclar(ListLinkedSingle& list) {
    Node* prev;
    Node* curr = head;
    Node* other = list.head;
    if (head == nullptr) {
        head = list.head;
        list.head = nullptr;
    }
    else if (list.head == nullptr);
    else {
        if (head->value <= list.head->value) {
            prev = head;
            curr = head->next;
            other = list.head;
        }
        else {
            prev = list.head;
            curr = head;
            other = list.head->next;
            head = list.head;
        }

        while (curr != nullptr && other != nullptr) {
            if (curr->value <= other->value) {
                prev->next = curr;
                prev = curr;
                curr = curr->next;
            }
            else {
                prev->next = other;
                prev = other;
                other = other->next;
            }
        }
        if (curr == nullptr) prev->next = other;
        else prev->next = curr;

        list.head = nullptr;
    }
}


// EL coste es del orden de O(N) donde N es el numero de elementos de la lista ya que hace del orden de N iteraciones cada una de coste constante 

void tratar_caso() {
    ListLinkedSingle l, other;
    int num;
    cin >> num;
    while(num!=0) {
        l.push_back(num);
        cin >> num;
    }

    cin >> num;
    while (num != 0) {
        other.push_back(num);
        cin >> num;
    }

    l.mezclar(other);
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