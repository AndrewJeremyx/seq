#ifndef SEQ_SEQARRAY_H
#define SEQ_SEQARRAY_H
#include "seq.h"
#include <cstring>
template <typename T>
class SeqArray : public Seq<T> {

    T* array_;

public:

    SeqArray() : Seq<T>(), array_(nullptr) {}

    SeqArray(std::initializer_list<T> init_list) : Seq<T>(), array_(new T[init_list.size()]) {
        this->length_ = init_list.size();
        int i = 0;
        for (auto& item : init_list) {array_[i++] = std::move(item);}
    }

    virtual ~SeqArray() override {
        if (*this) {delete[] array_;}
    }

    virtual T Get(std::size_t index) const override {
        if ((index < this->length_) && (index  >= 0)) {
            return array_[index];}
        else {
            throw std::out_of_range("bad index");
        }
    }

    virtual void InsertAt(std::size_t index, T elem) override {
        if (index > this->length_) {throw 8;}
        T* tmp = new T [this->length_ + 1];
        for (auto i = 0; i < index; ++i) {tmp[i] = std::move(array_[i]);}
        tmp[index] = elem;
        ++this->length_;
        for (auto i = index + 1; i < this->length_; ++i) {tmp[i] = std::move(i - 1);}
        delete[] array_;
        array_ = tmp;
        this->isEmpty = 0;
    }

    virtual void Remove(T elem) override {
        auto counter = 0;
        for (auto i = 0; i < this->length_; ++i) {
            if (Get(i) != elem) {++counter;}
        }
        if (!counter) {
            this->isEmpty = 1;
            this->length_ = counter;
            return;
        }
        auto tmp = new T[counter];
        counter = 0;
        for (auto i = 0; i < this->length_; ++i) {
            if (Get(i) != elem) {tmp[counter++] = std::move(Get(i));}
        }
        delete[] array_;
        array_ = tmp;
        this->length_ = counter;
    }

    T* begin() {return array_;}

    T* end() {return array_ + this->length_;}
};
#endif
