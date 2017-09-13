#ifndef SEQ_H
#define SEQ_H
#include <cstddef>
#include <initializer_list>
template<typename T>
class Seq {

protected:

    std::size_t length_;

    bool isEmpty;

public:

    Seq(): length_(0), isEmpty(1) {};

    Seq(const Seq& seq) {
        for (std::size_t i = 0; i < seq.length_; i++) {Append(seq.Get(i));}
    }

    virtual ~Seq(){}

    std::size_t getLength() const noexcept {return length_;}

    bool getIsEmpty() const noexcept {return isEmpty;}

    virtual T Get(size_t index) const = 0 ;

    T GetFirst() const {return Get(0);}

    T GetLast() const {return Get(length_ - 1);}

    virtual void InsertAt(std::size_t index, T elem) = 0;

    void Append(T elem){InsertAt(length_, elem);}

    void Prepend(T elem){InsertAt(0, elem);}

    virtual void Remove(T elem) = 0;

    operator bool() const {return !isEmpty;}
};
#endif
