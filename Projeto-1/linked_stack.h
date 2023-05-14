#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>

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
    std::size_t size() const;

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
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
#endif