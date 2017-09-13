#ifndef SEQLIST_H
#define SEQLIST_H
#include "seq.h"
#include <initializer_list>
#include <utility>
template <typename T>
class SeqList : public Seq<T> {

    struct Node {

        T data_;

        Node* next_;

        Node(T data): data_(data), next_(nullptr) {}

        ~Node() {
            if (next_) {delete next_;}
        }
    };

    Node* head_;

public:

    SeqList() : Seq<T>(), head_(nullptr) {}

    SeqList(std::initializer_list<T> init_list) : Seq<T>() {
        for (auto& item : init_list) {this->Append(item);}
    }

    virtual ~SeqList() override {
        if (head_) {delete head_;}
    }

    virtual T Get(std::size_t index) const override {
        if ((index < this->length_) && (index  >= 0)) {
            Node* tmp = head_;
            for (auto i = 0; i < index; ++i) {tmp = tmp->next_;}
            return tmp->data_;
        }
        else
            throw std::out_of_range("bad index");
    }

    virtual void InsertAt(std::size_t index, T elem) override {
        auto next = new Node(elem);
        if ((index > this->length_) && (index < 0)) {throw std::out_of_range("bad index");}
        if (!index) {
            auto tmp = next;
            next = head_;
            head_ = tmp;
            this->isEmpty = 0;
        }
        else {
            auto tmp = head_;
            for (auto i = 0; i < index - 1; i++) {tmp = tmp->next_;}
            auto tmp2 = tmp->next_;
            tmp->next_ = next;
            next->next_ = tmp2;
        }
        ++this->length_;
    }

    virtual void Remove(T elem) override {
        while ((head_) && (head_->data_ == elem)) {
            auto tmp = head_;
            head_ = head_->next_;
            tmp->next_ = nullptr;
            --this->length_;
            delete tmp;
            if (!head_) {
                this->isEmpty = 1;
                return;
            }
        }
            auto that = head_->next_;
            auto prev = head_;
            while (that) {
                if (that->data_ == elem) {
                    prev->next_ = that->next_;
                    that->next_ = nullptr;
                    delete that;
                    that = prev->next_;
                    --this->length_;
                }
                else {
                    that = that->next_;
                }
            }
        }
};
#endif

