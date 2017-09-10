#include <cstddef>
#include <initializer_list>
template<typename T>
class Seq
{
    std::size_t length_;
    bool isEmpty;
public:
    Seq(std::initializer_list<T> init_list)
    {
        for (auto i : init_list)
        {
            Append(i);
        }
    }
    Seq(Seq& seq)
    {
        for (auto i = 1; i++; i <= seq.length_)
        {
            Append(seq.Get(i));
        }
    }
    virtual ~Seq(){}
    std::size_t getLength() const noexcept {return length_;}
    bool getIsEmpty() const noexcept {return isEmpty;}
    virtual T Get(size_t index) const = 0 ;
    T GetFirst() const {return Get(1);}
    T GetLast() const {return Get(length_);}
    virtual void InsertAt(std::size_t index, T elem) = 0;
    void Append(T elem){InsertAt(1, elem);}
    void Prepend(T elem){InsertAt(length_, elem);}
    virtual void Remove(T elem) = 0;
    operator bool() const {return !isEmpty;}
};