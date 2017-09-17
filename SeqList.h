#ifndef SEQLIST_H
#define SEQLIST_H
#include "seq.h"
#include <iostream>
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

    SeqList(const SeqList& other) {
        std::cout << "копирование" << std::endl;
        this->length_ = other.length_;
        this->isEmpty = other.isEmpty;
        this->head_ = nullptr;
        if (other) {
            head_ = new Node(other.head_->data_);
            auto tmp = other.head_;
            auto tmp2 = head_;
            for (auto i = 1; i < other.length_; ++i) {
                tmp2->next_ = new Node(tmp->next_->data_);
                tmp = tmp->next_;
                tmp2 = tmp2->next_;
            }
        }
    }

    SeqList(SeqList&& other) {
        this->length_ = other.length_;
        this->isEmpty = other.isEmpty;
        this->head_ = other.head_;
        other.head_ = nullptr;
        other.isEmpty = 1;
        other.length_ = 0;
    }

    SeqList(std::initializer_list<T> init_list) : SeqList() {
        for (auto& item : init_list) {this->Append(item);}
    }

    SeqList&operator =(const SeqList& rhs) {
        if (&rhs != this) {
            if (*this) { delete head_; }
            this->length_ = rhs.length_;
            this->isEmpty = rhs.isEmpty;
            this->head_ = nullptr;
            if (rhs) {
                head_ = new Node(rhs.head_->data_);
                auto tmp = rhs.head_;
                auto tmp2 = head_;
                for (auto i = 1; i < rhs.length_; ++i) {
                    tmp2->next_ = new Node(tmp->next_->data_);
                    tmp = tmp->next_;
                    tmp2 = tmp2->next_;
                }
            }
        }
    }

    SeqList&operator =(SeqList&& rhs) {
        if (&rhs != this) {
            if (head_) {delete head_;}
            this->length_ = rhs.length_;
            this->isEmpty = rhs.isEmpty;
            this->head_ = rhs.head_;
            rhs.head_ = nullptr;
            rhs.isEmpty = 1;
            rhs.length_ = 0;
        }
        return *this;
    }

    SeqList&operator =(std::initializer_list<T> init_list) {
        if (*this) {delete head_;};
        this->length_ = init_list.size();
        this->isEmpty = !init_list.size();
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
            head_->next_ = next;
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
    SeqList<T> GetSubSeq(std::size_t begin, std::size_t end) const {
        if ((begin > end) || (end >= this->length_)) {throw std::out_of_range("bad index");}
        SeqList<T> result;
        auto tmp = head_;
        Node* tmp2;
        for (auto i = 0; i < end + 1; ++i) {
            if (i < begin) {tmp = tmp->next_;}
            else if (i == begin) {
                result.head_ = new Node(tmp->data_);
                tmp2 = result.head_;
                ++result.length_;
                result.isEmpty = 0;
                tmp = tmp->next_;
            }
            else {
                tmp2->next_ = new Node(tmp->data_);
                tmp2 = tmp2->next_; 
                tmp = tmp->next_;
                ++result.length_;
            }
        }
        return std::move(result);
    }
};
#endif

