#include "queue.h"

Node::Node(int32_t value, Node* next) : value(value), next(next) {
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    Node* new_node_ptr = new Node(value, nullptr);
    if (tail_) {
        tail_->next = new_node_ptr;
    } else {
        front_ = new_node_ptr;
    }
    tail_ = new_node_ptr;
    ++size_;
}

void Queue::Pop() {
    Node* mem = front_->next;
    delete front_;
    front_ = mem;
    --size_;
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (front_) {
        Pop();
    }
}

bool Queue::Empty() const {
    return size_ == 0;
}