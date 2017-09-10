#ifndef SEQ_SEQARRAY_H
#define SEQ_SEQARRAY_H
#include "seq.h"
#include <cstring>
template <typename T>
class SeqArray : public Seq<T>
{
    T* array_;
public:
    SeqArray() : Seq<T>(), array_(nullptr) {}
    SeqArray(std::initializer_list<T> init_list) : Seq<T>(),
                                                   array_(new T[init_list.size()])
    {
        this->length_ = init_list.size();
        int i = 0;
        for (auto& item : init_list)
        {
            array_[i++] = item;
        }
    }
    virtual ~SeqArray() override
    {
        if (*this)
        {
            delete[] array_;
        }
    }
    virtual T Get(std::size_t index) const override
    {
        if (index < this->length_ && index  >= 0 )
            return array_[index];
        else
            throw 8;
    }
    virtual void InsertAt(std::size_t index, T elem) override
    {
        if (index > this->length_)
        {
            throw 8;
        }
        T* tmp = new T [this->length_ + 1];
        memcpy(tmp, array_, (index) * sizeof(elem));
        tmp[index] = elem;
        memcpy(tmp + index + 1, array_ + index, (++this->length_ - index - 1) * sizeof(elem));
        delete[] array_;
        array_ = tmp;
        this->isEmpty = 0;
    }
    virtual void Remove(T elem) override
    {
        int counter = 0;
        for (auto i = 0; i < this->length_; ++i)
        {
            if (Get(i) != elem)
                ++counter;
        }
        T* tmp;
        if (counter == 0)
        {
            tmp = nullptr;
            this->isEmpty = 1;
            return;
        }
        else
            tmp = new T[counter];
        counter = 0;
 	for (auto i = 0; i < this->length_; ++i)
        {
            if (Get(i) != elem)
                tmp[counter++] = Get(i);
        }
        delete[] array_;
        array_ = tmp;
    }
    T* begin() {return array_;}
    T* end() {return array_ + this->length_;}
};
#endif
