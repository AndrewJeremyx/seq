template<typename T>
class Seq
{
    std::size_t length;
    bool isEmpty;
public:
    std::size_t getLength() const noexcept {return length;}
    bool getIsEmpty() const noexcept {return isEmpty;}
    virtual T Get(size_t index) const = 0 ;
    T GetFirst() const {return Get(1);}
    T GetLast() const {return Get(length);}
    virtual void InsertAt(std::size_t index, T elem) = 0;
    void Append(T elem){InsertAt(1, elem)}
    void Prepend(T elem){InsertAt(length, elem)}
    virtual void Remove(T elem) = 0;
};