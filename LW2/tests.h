#include "sequence.h"
#pragma once

//Dynamic array tests
//Assuming Get and GetSize work correctly
void TestDynamicArrayCreation(std::string prefix = "", bool silent = true);
void TestDynamicArraySet(std::string prefix = "", bool silent = true);
void TestDynamicArrayResize(std::string prefix = "", bool silent = true);
void TestDynamicArrayDelete(std::string prefix = "", bool silent = true);
void TestDynamicArrayOperators(std::string prefix = "", bool silent = true);
void TestDynamicArrayAll(std::string prefix = "", bool silent = true);

//Linked list tests
//Assuming Get and GetLength work correctly
void TestLinkedListCreation(std::string prefix = "", bool silent = true);
void TestLinkedListSet(std::string prefix = "", bool silent = true);
void TestLinkedListAdd(std::string prefix = "", bool silent = true);
void TestLinkedListDelete(std::string prefix = "", bool silent = true);
void TestLinkedListConcat(std::string prefix = "", bool silent = true);
void TestLinkedListSublist(std::string prefix = "", bool silent = true);
void TestLinkedListOperators(std::string prefix = "", bool silent = true);
void TestLinkedListAll(std::string prefix = "", bool silent = true);

//Sequence tests
//Assuming DynamicArray, LinkedList, Get and GetLength work correctly
void TestArraySequenceCreation(std::string prefix = "", bool silent = true);
void TestListSequenceCreation(std::string prefix = "", bool silent = true);
void TestSequenceSet(SequenceType seqType, std::string prefix = "", bool silent = true);
void TestSequenceAdd(SequenceType seqType, std::string prefix = "", bool silent = true);
void TestSequenceDelete(SequenceType seqType, std::string prefix = "", bool silent = true);
void TestSequenceConcat(SequenceType seqType, std::string prefix = "", bool silent = true);
void TestSequenceSubsequence(SequenceType seqType, std::string prefix = "", bool silent = true);
void TestSequenceOperators(SequenceType seqType, std::string prefix = "", bool silent = true);
void TestSequenceAll(std::string prefix = "", bool silent = true);

//Deque tests
//Assuming Sequence and all getters work correctly
//A correct Sequence interface allows us to test all Deque methods only with a one Sequence implementation
//So we will use Sequence implementation defined by Deque::kDefaultSequenceType
void TestDequeCreation(std::string prefix = "", bool silent = true);
//Deque constructor	is fully based on Sequence constructors, which we assume are working properly,
//so test_deque_creation exists only for SequenceType tests
void TestDequePopPush(std::string prefix = "", bool silent = true);
void TestDequeSort(std::string prefix = "", bool silent = true);
void TestDequeMap(std::string prefix = "", bool silent = true);
void TestDequeWhere(std::string prefix = "", bool silent = true);
void TestDequeReduce(std::string prefix = "", bool silent = true);
void TestDequeSequenceMethods(std::string prefix = "", bool silent = true);
//Concat and GetSubsequence are fully implemented by Sequence, which we assume are working properly,
//so test_deque_sequence_methods exists only for memory leaks detection
void TestDequeAll(std::string prefix = "", bool silent = true);

//Test all
void TestAll(std::string prefix = "", bool silent = true);

//Tools
void RepeatedTest(void (*f)(std::string, bool), int n, std::string prefix = "", bool silent = true);
void WaitKey();

