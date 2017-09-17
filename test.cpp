#include <iostream>
#include <string>
#include "SeqArray.h"
#include "SeqList.h"


class Tester {
    unsigned int countOfTests;
    unsigned int countOfTrueTests;
    bool isFullLog;
public:
    Tester(bool isFullLog): isFullLog(isFullLog), countOfTests(0), countOfTrueTests(0) {}
    void operator()(bool state, std::string str) {
	++countOfTests;
        if (!state) {
	    std::cout << "test " << countOfTests << " failed " << str << std::endl; 
	}
	else if ((state) && (isFullLog)) {
	    std::cout << "test " << countOfTests << " correct " << str << std::endl;
        ++countOfTrueTests;
	}
	else {
	   ++countOfTrueTests; 
        }
    }
    void operator()() {
    std::cout << countOfTrueTests << "/" << countOfTests << std::endl;
    }
};
template <class SeqType>
struct test {
    void testss() {
        Tester tester(0);
        SeqType *seq = new(SeqType);
        tester(seq->getLength() == 0, "Length() == 0");
        tester(seq->getIsEmpty() == 1, "IsEmpty == 1");
        seq->Append(23);
        tester(seq->getLength() == 1, "Length() == 1");
        tester(seq->getIsEmpty() == 0, "IsEmpty == 0");
        tester(seq->GetFirst() == 23, "GetFirst == 23");
        tester(seq->GetLast() == 23, "GetLast == 23");
        tester(seq->Get(0) == 23, "Get(0) == 23");
        try {
            seq->Get(1);
            tester(false, "Get(1) => throw exception");
        }
        catch (std::exception &) { tester(true, "Get(1) => throw exception");};
        try {
            seq->Get(-1);
            tester(false, "Get(-1) => throw exception");
        }
        catch (std::exception &) { tester(true, "Get(-1) => throw exception"); };
        seq->Append(43);
        tester(seq->getLength() == 2, "Length() == 2");
        tester(seq->GetFirst() == 23, "GetFirst == 23");
        tester(seq->GetLast() == 43, "GetLast == 43");
        tester(seq->Get(0) == 23, "Get(0) == 23");
        tester(seq->Get(1) == 43, "Get(1) == 43");
        try {
            seq->Get(-1);
            tester(false, "Get(-1) => throw exception");
        }
        catch (std::exception &) { tester(true, "Get(-1) => throw exception"); };
        try {
            seq->Get(2);
            tester(false, "Get(2) => throw exception");
        }
        catch (std::exception &) { tester(true, "Get(2) => throw exception"); };
        seq->Prepend(53);
        tester(seq->getLength() == 3, "Length() == 3");
        tester(seq->GetFirst() == 53, "GetFirst == 53");
        tester(seq->GetLast() == 43, "GetLast == 43");
        tester(seq->Get(0) == 53, "Get(0) == 53");
        tester(seq->Get(1) == 23, "Get(1) == 23");
        try {
            seq->Get(-1);
            tester(false, "Get(-1) => throw exception");
        }
        catch (std::exception &) { tester(true, "Get(-1) => throw exception"); };
        try {
            seq->Get(3);
            tester(false, "Get(3) => throw exception");
        }
        catch (std::exception &) { tester(true, "Get(3) => throw exception"); };
        seq->Remove(53);
        tester(seq->getLength() == 2,"Length == 2");
        tester(seq->GetFirst() == 23, "GetFirst == 23");
        auto seq2 = new SeqType(seq->GetSubSeq(1,1));
        tester(seq2->getLength() == 1, "Length() == 1");
        tester(seq2->getIsEmpty() == 0, "IsEmpty == 0");
        tester(seq2->GetFirst() == 43, "GetFirst == 43");
        tester(seq2->GetLast() == 43, "GetLast == 43");
        delete seq;
        delete seq2;
        seq = new SeqType({});
        seq->Append(1);
        seq->Append(1);
        seq->Append(1);
        seq2 = new SeqType(*seq);
        tester(seq2->getLength() == 3,"Length == 3");
        seq2->Remove(1);
        tester(seq2->getLength() == 0,"Length == 0");
        tester(seq2->getIsEmpty() == 1,"IsEmpty == 1");
        tester(seq->getLength() == 3,"Length == 3");
        seq->Append(3);
        delete seq2;
        seq2 = new SeqType(std::move(*seq));
        tester(seq->getLength() == 0,"Length == 0");
        tester(seq->getIsEmpty() == 1,"IsEmpty == 1");
        tester(seq2->getLength() == 4,"Length == 4");
        tester(seq2->GetFirst() == 1,"GetFirst == 1");
        tester(seq2->GetLast() == 3,"GetLast == 3");
        tester();
    }
};

int main() {
    test<SeqList<int> > A;
    test<SeqArray<int> > B;
    A.testss();
    B.testss();
    return 0;
}
