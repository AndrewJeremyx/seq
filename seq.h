#ifndef SEQ_H
#define SEQ_H
#include <cstddef>
#include <initializer_list>
template<typename T>
class Seq {

public:

    virtual ~Seq(){}

    virtual std::size_t getLength() const noexcept = 0;

    virtual bool getIsEmpty() const noexcept = 0;

    virtual T Get(size_t index) const = 0;

    virtual T& Get(size_t index) = 0;

    T GetFirst() const {return Get(0);}

    T GetLast() const {return Get(getLength() - 1);}

    virtual void InsertAt(std::size_t index, T elem) = 0;

    void Append(T elem){InsertAt(getLength(), elem);}

    void Prepend(T elem){InsertAt(0, elem);}

    virtual void Remove(T elem) = 0;

    virtual void Clear() = 0;

    operator bool() const {return !getIsEmpty();}

    virtual Seq<T>* GetSubSeq(std::size_t begin, std::size_t end) const = 0; 

    virtual Seq<T>* Copy() const = 0;
};
#endif
