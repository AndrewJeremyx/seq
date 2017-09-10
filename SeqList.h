#ifndef SEQLIST_H
#define SEQLIST_H
#include "seq.h"
#include <initializer_list>
#include <utility>
template <typename T>
class SeqList : public Seq<T>
{
    struct Node
    {
        T data_;
        Node* next_;
        Node(T data): data_(data), next_(nullptr) {}
        ~Node()
        {
            if (!next_)
                delete next_;
        }
    };
    Node* head_;
public:
    SeqList() : Seq<T>(), head_(nullptr) {}
    SeqList(std::initializer_list<T> init_list) : Seq<T>()
    {
        for (auto& item : init_list)
        {
            this->Append(item);
        }
    }
    virtual ~SeqList() override
    {
        delete head_;
    }
    virtual T Get(std::size_t index) const override
    {
        if (index < this->length_ && index  >= 0 )
        {
            Node* tmp = head_;
            for (int i = 0; i < index; ++i)
            {
               tmp = tmp->next_;
            }
            return tmp->data_;
        }
        else
            throw 8;
    }
    virtual void InsertAt(std::size_t index, T elem) override
    {
        Node* next = new Node(elem);
        if (index > this->length_)
            throw 8;
        if (index == 0)
        {
            std::swap(next, head_);
            head_->next_ = next;
            this->isEmpty = 0;
        }
        else
        {
            auto tmp = head_;
            for (auto i = 0; i < index - 1; i++)
            {
                tmp = tmp->next_;
            }
            auto tmp2 = tmp->next_;
            tmp->next_ = next;
            next->next_ = tmp2;
        }
        ++this->length_;
    }
    virtual void Remove(T elem) override
    {
        auto tmp = head_->next_;
        while(tmp != nullptr)
        {
            auto tmp2 = tmp->next_;
            if (tmp2 != nullptr && tmp2->data_ == elem)
            {
                tmp->next_ = tmp2->next_;
                tmp2->next_ = nullptr;
                delete tmp2;
                --this->length_;
            }
            tmp = tmp->next_;
        }
        if (head_->data_ == elem)
        {
            tmp = head_;
            head_ = head_->next_;
            tmp->next_ = nullptr;
            delete tmp;
            --this->length_;
        }
        if (this->length_ == 0)
            this->isEmpty = 1;
    }
};
#endif

