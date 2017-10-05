#include "seq.h"
#include <cstddef>
template <typename T>
class iSorter {

public:

    virtual Seq<T> *sort(const Seq<T> *seq) = 0;
};


template <typename T>
class TreeSorter : public iSorter<T> {

public:

    virtual Seq<T> *sort(const Seq<T> *seq) override {
        Tree tree(seq->GetFirst());
        for (auto i = 1; i < seq->getLength(); ++i) {tree.Insert(seq->Get(i)); }
        Seq<T> *result = seq->Copy();
        result->Clear();
        fromTreeToSeq(&tree, result);
        return result;
    }
    
private:

    struct Tree {

        Tree *left_;

        Tree *right_;

        T data_;

        Tree(T data) : data_(data), left_(nullptr), right_(nullptr) {}

        ~Tree() {
            delete left_;
            delete right_;
        }

        void Insert(T data) {
            auto tmp = this;
            while (1) {
                if (data >= tmp->data_) {
                    if (tmp->right_) { tmp = tmp->right_; }
                    else {
                        tmp->right_ = new Tree(data);
                        return;
                    }
                } else {
                    if (tmp->left_) { tmp = tmp->left_; }
                    else {
                        tmp->left_ = new Tree(data);
                        return;
                    }
                }
            }
        }

    };

    static void fromTreeToSeq(Tree  *tree, Seq<T> *result) {
        if (tree->left_) { fromTreeToSeq(tree->left_, result); }
        result->Append(tree->data_);
        if (tree->right_) { fromTreeToSeq(tree->right_, result); }
    }

};

template <typename T>
class ShellSorter : public iSorter<T> {

public:

    virtual Seq<T> *sort(const Seq<T> *seq) override {
        auto result = seq->Copy();
        T t;
        for (std::size_t k = result->getLength()/2; k > 0; k /= 2) {
            for (auto i = k; i < result->getLength(); ++i) {
                t = result->Get(i);
                std::size_t j;
                for (j = i; j >= k; j -= k) {
                    if (t < result->Get(j - k)) {
                        result->Get(j) = result->Get(j - k);
                    }
                    else  break;
                }
                result->Get(j) = t;
            }
        }
        return result;
    }
};
template <typename T>
class MergeSorter : public iSorter<T> {

public:

    virtual Seq<T> *sort(const Seq<T> *seq) override {
        auto result = seq->Copy();
        merge_sort(result);
        return result;
    }
private:
    void merge_sort(Seq<T>* seq) {
        if (seq->getLength() > 1) {
            std::size_t const left_size = seq->getLength() / 2;
            std::size_t const right_size = seq->getLength() - left_size;
            Seq<T>* left = seq->GetSubSeq(0, left_size - 1);
            Seq<T>* right = seq->GetSubSeq(left_size, seq->getLength() - 1);
            merge_sort(right);
            merge_sort(left);
            std::size_t l = 0, r = 0;
            for (auto i = 0; i < seq->getLength(); ++i) {
                if (r >= right->getLength()) {
                    seq->Get(i) = std::move(left->Get(l++));
                }
                else if (l >= left->getLength()) {
                    seq->Get(i) = std::move(right->Get(r++));
                }
                else { 
                    if (right->Get(r) > left->Get(l)) {
                        seq->Get(i) = std::move(left->Get(l++));
                    }
                    else {
                        seq->Get(i) = std::move(right->Get(r++));
                    }
                }
            }
            delete left;
            delete right;
        }
    }
};
