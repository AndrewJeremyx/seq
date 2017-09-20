#include "seq.h"
template <typename T>
class Tester {

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

public:

    static void fromTreeToSeq(Tree  *tree, Seq<T> *result) {
        if (tree->left_) { fromTreeToSeq(tree->left_, result); }
        result->Append(tree->data_);
        if (tree->right_) { fromTreeToSeq(tree->right_, result); }
    }

    static Seq<T> *treeSort(const Seq<T> *seq) {
        Tree tree(seq->GetFirst());
        for (auto i = 1; i < seq->getLength(); ++i) {tree.Insert(seq->Get(i)); }
        Seq<T> *result = seq->Copy();
        fromTreeToSeq(&tree, result);
        return result;
    }
};
