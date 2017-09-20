#ifndef SEQ_SEQARRAY_H
#define SEQ_SEQARRAY_H
#include "seq.h"
#include <cstring>
#include <cstddef>
template <typename T>
class SeqArray : public Seq<T> {

    std::size_t length_;

    bool isEmpty;

    T* array_;

public:

    SeqArray() : length_(0), isEmpty(1), array_(nullptr) {}

    SeqArray(const SeqArray& other): length_(other.length_), isEmpty(other.isEmpty),
                                     array_(new T[this->length_]) {
        for (auto i = 0; i < length_; ++i) {array_[i] = other.array_[i];}
    }

    SeqArray(SeqArray&& other): length_(other.length_), isEmpty(other.isEmpty),
                                array_(other.array_) {
        other.array_ = nullptr;
        other.length_ = 0;
        other.isEmpty = 1;
    }

    SeqArray(std::initializer_list<T> init_list) : length_(init_list.size()), isEmpty(!init_list.size()),
                                                   array_(new T[init_list.size()]) {
        int i = 0;
        for (auto& item : init_list) {array_[i++] = std::move(item);}
    }

    SeqArray& operator = (const SeqArray& rhs) {
        if (&rhs != this) {
            if (array_) {delete[] array_;}
            array_ = new T[rhs.length_];
            length_ = rhs.length_;
            isEmpty = rhs.isEmpty;
            for (auto i = 0; i < length_; ++i) {array_[i] = rhs.array_[i];}
        }
        return *this;
    }

    SeqArray& operator = (SeqArray&& rhs) {
        if (this != &rhs) {
            if (array_) {delete[] array_;}
            length_ = rhs.length_;
            isEmpty = rhs.isEmpty;
            array_ = rhs.array_;
        }
        return *this;
    }

    SeqArray&operator = (std::initializer_list<T> init_list) {
        if (array_) {delete[] array_;}
        array_ = new T[init_list.size()];
        length_ = init_list.size();
        if (length_) {isEmpty = 0;}
        int i = 0;
        for (auto& item : init_list) {array_[i++] = std::move(item);}
    }

    virtual ~SeqArray() override {
        if (*this) {delete[] array_;}
    }

    virtual std::size_t getLength() const noexcept override {return length_;}

    virtual bool getIsEmpty() const noexcept override {return isEmpty;}

    virtual T Get(std::size_t index) const override {
        if ((index < length_) && (index  >= 0)) {
            return array_[index];}
        else {
            throw std::out_of_range("bad index");
        }
    }

    virtual void InsertAt(std::size_t index, T elem) override {
        if (index > length_) {throw std::out_of_range("invalid index");}
        T* tmp = new T [length_ + 1];
        for (auto i = 0; i < index; ++i) {tmp[i] = std::move(array_[i]);}
        tmp[index] = elem;
        ++length_;
        for (auto i = index + 1; i < length_; ++i) {tmp[i] = std::move(array_[i - 1]);}
        delete[] array_;
        array_ = tmp;
        isEmpty = 0;
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
        length_ = counter;
    }

    SeqArray GetSubSeq(std::size_t begin, std::size_t end) {
        if ((begin > end) || (end >= this->length_)) {throw std::out_of_range("bad index");}
        SeqArray result;
        result.length_ = end - begin + 1;
        result.array_ = new T[result.length_];
        result.isEmpty = 0;
        for (auto i = begin; i < end + 1; ++i) {result.array_[i - begin] = std::move(this->Get(i));}
        return std::move(result);
    }

    virtual Seq<T>* Copy() const override {return new SeqArray();}
};
#endif
