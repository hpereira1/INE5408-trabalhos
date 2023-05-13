#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>  
#include <string>
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

using namespace std;
using namespace structures;

namespace structures {
template <typename T>
class LinkedStack {
 public:
    // Construtor
    LinkedStack();
    // Destrutor
    ~LinkedStack();
    // limpa pilha
    void clear();
    // empilha
    virtual void push(const T& data);
    // desempilha
    virtual T pop();
    // dado no topo
    T& top() const;
    // pilha vazia
    bool empty() const;
    // tamanho da pilha
    size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data) : data_{data} {}
        Node(const T& data, Node* next) : data_{data},
                                          next_{next} {}
        // getter: info
        T& data() {
            return data_;
        }
        // getter-constante: info
        const T& data() const {
            return data_;
        }
        // getter: próximo
        Node* next() {
            return next_;
        }
        // getter-constante: próximo
        const Node* next() const {
            return next_;
        }
        // setter: próximo
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    // nodo-topo
    Node* top_{nullptr};
    // tamanho
    std::size_t size_{0u};
};

} 

template <typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template <typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template <typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty())
        pop();
}

template <typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_node = new Node(data, top_);
    if (new_node == nullptr)
        throw std::out_of_range("pilha cheia");
    top_ = new_node;
    size_++;
}

template <typename T>
T structures::LinkedStack<T>::pop() {
    if (empty())
        throw std::out_of_range("pilha vazia");

    Node* aux = top_;
    top_ = top_->next();
    T data = aux->data();
    delete aux;
    size_--;
    return data;
}

template <typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty())
        throw std::out_of_range("lista vazia");
    return top_->data();
}

template <typename T>
bool structures::LinkedStack<T>::empty() const {
    return (size_ == 0);
}

template <typename T>
size_t structures::LinkedStack<T>::size() const {
    return size_;
}


bool xml_valido(const string& xmlfilename) {
    ifstream xml(xmlfilename);
    bool erro = false;
    string tag_aux;
    string linha;
    LinkedStack<string> pilhatag;
    if (xml.is_open()) {
        while(getline(xml, linha)) {
            for(size_t i = 0; i < linha.length(); i++) {
                if (linha[i] == '<') {
                    if (!tag_aux.empty()){
                        tag_aux.clear(); 
                        }
                    if(linha[i + 1] != '/') {
                        i++;
                        while(linha[i] != '>') {
                            tag_aux= tag_aux + linha[i];
                            ++i;
                        }
                        pilhatag.push(tag_aux); 
                    } else {
                    i = i + 2;
                    while (linha[i] != '>' || linha[i] < linha.length()) {
                        tag_aux = tag_aux + linha[i];
                        i++;
                    }
                    if ((pilhatag.top() != tag_aux) || pilhatag.empty()) {
                        erro = true;
                    } else {
                        pilhatag.pop();
                    }
                }
            }
        }
    if (!pilhatag.empty()) {
        erro = true;
    }
    xml.close();
    return erro;
} }}

int main() {

    char xmlfilename[100];
    ifstream xmlfile;
    cin >> xmlfilename;  // entrada
    xmlfile.open(xmlfilename);
    if (!xmlfile.is_open()) {
        cout << "erro\n";
        return -1;
    }
    if (xml_valido(xmlfilename)) {
        cout << "erro\n";
        return -1;
    }
    
    return 0;
}
