#include <iostream>
#include "dynamic_array.h"
#include "linked_list.h"
#include "sequence.h"
#include "array_sequence.h"
#include "list_sequence.h"
#include "deque.h"
#include "tests.h"

int main()
{
	RepeatedTest(TestAll, 10000, "", false);
	WaitKey();
}