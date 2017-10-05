#include <iostream>
#include <array>
#include "seq.h"
#include "SeqArray.h" 
#include "SeqList.h" 
#include "tree.h"
#include <ctime>
#include <cstddef>

template <typename T>
void graph1(std::size_t size, Seq<T> * seq1) {
    MergeSorter<T> MS;
    TreeSorter<T> TS;
    ShellSorter<T> SS;
    auto seq = seq1->Copy();
    std::array<Seq<T>*, 10> ar;
    for (int i = 0; i < size; ++i) {
        seq->Append(i);
    }
    std::cout << size <<" "; 
    auto time1 = time(nullptr);
    for (auto it = ar.begin(); it != ar.end(); ++it ){
        *it = TS.sort(seq);
    }
    std::cout << (double)((time(nullptr) - time1)) / 10<<" ";
    for (auto it = ar.begin(); it != ar.end(); ++it ){
        delete *it; 
    }
    time1 = time(nullptr);
    for (auto it = ar.begin(); it != ar.end(); ++it ){
        *it = SS.sort(seq);
    }
    std::cout << (double)((time(nullptr) - time1)) / 10<<" ";
    for (auto it = ar.begin(); it != ar.end(); ++it ){
        delete *it;
    }
    time1 = time(nullptr);
    for (auto it = ar.begin(); it != ar.end(); ++it ){
        *it = MS.sort(seq);
    }
    std::cout <<(double)((time(nullptr) - time1)) / 10<< std::endl;
    for (auto it = ar.begin(); it != ar.end(); ++it ){
        delete *it;
    }

}


int main () {
    SeqList<int> A;
    std::cout << "? 'Tree Sort' 'Shell sort' 'Merge Sort'" << std::endl;
    for (auto i = 100; i <= 10000; i *= 2 ) {
    graph1(i, &A);
    }
    return 1;
}
