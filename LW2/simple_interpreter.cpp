#include "simple_interpreter.h"
#include <cstring>
#include <stdio.h>
#include "dynamic_array.h"
#include "linked_list.h"
#include "sequence.h"
#include "list_sequence.h"
#include "array_sequence.h"
#include "deque.h"
#include "tests.h"

//Example functions
bool compare_char(char a, char b) {
    return a > b;
}

char MakeSnakeCase(char x) {
    if (x == ' ')
        return '_';
    return x;
}

char MakeUppercase(char x) {
    if (x <= 122 && x >= 97)
        return x - 32;
    return x;
}

char MakeLowercase(char x) {
    if (x <= 90 && x >= 65)
        return x + 32;
    return x;
}

bool IsNotSpace(char x) {
    return x != ' ';
}

bool IsLowercase(char x) {
    return x <= 122 && x >= 97;
}

bool IsUppercase(char x) {
    return x <= 90 && x >= 65;
}

char CountSpaces(char x, char c) {
    if (x == ' ' && c < 57)
        return c + 1;
    return c;
}

char CountUppercase(char x, char c) {
    if (IsUppercase(x) && c < 57)
        return c + 1;
    return c;
}

char CountLowercase(char x, char c) {
    if (IsLowercase(x) && c < 57)
        return c + 1;
    return c;
}

//Help printers
void PrintHelp() {
    printf("Global commands:\n");
    printf("  Quit\n");
    printf("  = | items\n");
    printf("  switch | (DynamicArray, LinkedList, ArraySequence, ListSequence, Deque)\n");
}

void PrintHelpDynamicArray()
{
    PrintHelp();
    printf("DynamicArray commands:\n");
    printf("  Get | index\n");
    printf("  GetSize\n");
    printf("  Set | index item\n");
    printf("  Resize | size\n");
    printf("  Delete | index\n");
}

void PrintHelpLinkedList()
{
    PrintHelp();
    printf("LinkedList commands:\n");
    printf("  GetFirst\n");
    printf("  GetLast\n");
    printf("  Get | index\n");
    printf("  GetSize\n");
    printf("  Set | index item\n");
    printf("  Append | item\n");
    printf("  Prepend | item\n");
    printf("  InsertAt | item index\n");
    printf("  Delete | index\n");
    printf("  Concat | (r, l) items\n");
    printf("  GetSubList | start_index end_index\n");
}

void PrintHelpSequence()
{
    PrintHelp();
    printf("Sequence commands:\n");
    printf("  GetFirst\n");
    printf("  GetLast\n");
    printf("  Get | index\n");
    printf("  GetSize\n");
    printf("  Set | index item\n");
    printf("  Append | item\n");
    printf("  Prepend | item\n");
    printf("  InsertAt | item index\n");
    printf("  Delete | index\n");
    printf("  Concat | (r, l) items\n");
    printf("  GetSubsequence | start_index end_index\n");
}

void PrintHelpDeque()
{
    PrintHelp();
    printf("Deque commands:\n");
    printf("  PushBack | item\n");
    printf("  PushFront | item\n");
    printf("  PopBack\n");
    printf("  PopFront\n");
    printf("  Get | index\n");
    printf("  GetSize\n");
    printf("  GetSequenceType\n");
    printf("  IsEmpty\n");
    printf("  Concat | (r, l) items\n");
    printf("  GetSubsequence | start_index end_index\n");
    printf("  Map | (Snake, Upper, Lower)\n");
    printf("  Where | (NotSpace, Upper, Lower)\n");
    printf("  Reduce | (Spaces, Upper, Lower)\n");
    printf("  Split | item\n");
}

//Class methods

SimpleInterpreter::Word* SimpleInterpreter::readWord()
{
    char items[256];
    for (int i = 0; i < 256; i++)
        items[i] = 0;
    scanf_s(" %[^\n]s", items, 256);
    size_t length = 0;
    for (int i = 0; i < 256; i++) {
        if (items[i] != 0)
            length += 1;
        else
            break;
    }

    Word* word = new Word;
    word->items = (char*)malloc(length * sizeof(char));
    std::memcpy(word->items, items, length * sizeof(char));
    word->length = length;
    return word;
}

void SimpleInterpreter::SwitchDataType(DataType data_type)
{
    char* items = (char*)" ";
    size_t length = 1;
    switch (data_type_)
    {
    case DataType::DynamicArray:
        length = dynamic_array_->GetSize();
        items = (char*)std::malloc(length * sizeof(char));
        for (int i = 0; i < length; i++)
            items[i] = dynamic_array_->Get(i);
        delete(dynamic_array_);
        break;
    case DataType::LinkedList:
        length = linked_list_->GetLength();
        items = (char*)std::malloc(length * sizeof(char));
        for (int i = 0; i < length; i++)
            items[i] = linked_list_->Get(i);
        delete(linked_list_);
        break;
    case DataType::ListSequence:
        length = sequence_->GetLength();
        items = (char*)std::malloc(length * sizeof(char));
        for (int i = 0; i < length; i++)
            items[i] = sequence_->Get(i);
        delete(sequence_);
        break;
    case DataType::ArraySequence:
        length = sequence_->GetLength();
        items = (char*)std::malloc(length * sizeof(char));
        for (int i = 0; i < length; i++)
            items[i] = sequence_->Get(i);
        delete(sequence_);
        break;
    case DataType::Deque:
        length = deque_->GetLength();
        items = (char*)std::malloc(length * sizeof(char));
        for (int i = 0; i < length; i++)
            items[i] = deque_->Get(i);
        delete(deque_);
        break;
    default:
        throw std::invalid_argument("Got wrong sequence type.");
        break;
    }

    switch (data_type)
    {
    case DataType::DynamicArray:
        dynamic_array_ = new DynamicArray<char>(items, length);
        break;
    case DataType::LinkedList:
        linked_list_ = new LinkedList<char>(items, length);
        break;
    case DataType::ListSequence:
        sequence_ = new ListSequence<char>(items, length);
        break;
    case DataType::ArraySequence:
        sequence_ = new ArraySequence<char>(items, length);
        break;
    case DataType::Deque:
        deque_ = new Deque<char>(items, length);
        break;
    default:
        throw std::invalid_argument("Got wrong data type.");
        break;
    }

    data_type_ = data_type;
}

void SimpleInterpreter::SetItems(char* items, size_t length)
{
    switch (data_type_)
    {
    case DataType::DynamicArray:
        delete(dynamic_array_);
        dynamic_array_ = new DynamicArray<char>(items, length);
        break;
    case DataType::LinkedList:
        delete(linked_list_);
        linked_list_ = new LinkedList<char>(items, length);
        break;
    case DataType::ListSequence:
        delete(sequence_);
        sequence_ = new ListSequence<char>(items, length);
        break;
    case DataType::ArraySequence:
        delete(sequence_);
        sequence_ = new ArraySequence<char>(items, length);
        break;
    case DataType::Deque:
        delete(deque_);
        deque_ = new Deque<char>(items, length);
        break;
    default:
        throw std::invalid_argument("Got wrong sequence type.");
        break;
    }
}

void SimpleInterpreter::PrintStatus()
{
    size_t length;
    switch (data_type_)
    {
    case DataType::DynamicArray:
        printf("DynamicArray: ");
        length = dynamic_array_->GetSize();
        for (int i = 0; i < length; i++)
            printf("%c", dynamic_array_->Get(i));
        if (length > 0 && dynamic_array_->Get(length - 1) == ' ')
            printf("<");
        break;
    case DataType::LinkedList:
        printf("LinkedList: ");
        length = linked_list_->GetLength();
        for (int i = 0; i < length; i++)
            printf("%c", linked_list_->Get(i));
        if (length > 0 && linked_list_->Get(length - 1) == ' ')
            printf("<");
        break;
    case DataType::ListSequence:
        printf("ListSequence: ");
        length = sequence_->GetLength();
        for (int i = 0; i < length; i++)
            printf("%c", sequence_->Get(i));
        if (length > 0 && sequence_->Get(length - 1) == ' ')
            printf("<");
        break;
    case DataType::ArraySequence:
        printf("ArraySequence: ");
        length = sequence_->GetLength();
        for (int i = 0; i < length; i++)
            printf("%c", sequence_->Get(i));
        if (length > 0 && sequence_->Get(length - 1) == ' ')
            printf("<");
        break;
    case DataType::Deque:
        printf("Deque: ");
        length = deque_->GetLength();
        for (int i = 0; i < length; i++)
            printf("%c", deque_->Get(i));
        if (length > 0 && deque_->Get(length - 1) == ' ')
            printf("<");
        break;
    default:
        throw std::invalid_argument("Got wrong sequence type.");
        break;
    }
    printf("\n");
}

void SimpleInterpreter::ProcessCommand(char* command)
{
    if (!std::strcmp(command, "=")) {
        Word* word = readWord();
        SetItems(word->items, word->length);
        free(word->items);
    }
    else if (!strcmp(command, "test")) {
        int n_tests = 0;
        scanf_s(" %d", &n_tests);
        if (n_tests >= 0) {
            if (n_tests == 1)
                TestAll("", false);
            else
                RepeatedTest(TestAll, n_tests, "", false);
        }
        else
            printf("Error:  Invalid arguments.\n");
    }
    else if (!strcmp(command, "switch")) {
        char data_type_string[32];
        scanf_s("%s", data_type_string, 32);
        data_type_string[31] = 0;
        if (!strcmp(data_type_string, "DynamicArray"))
            SwitchDataType(DataType::DynamicArray);
        else if (!strcmp(data_type_string, "LinkedList"))
            SwitchDataType(DataType::LinkedList);
        else if (!strcmp(data_type_string, "ArraySequence"))
            SwitchDataType(DataType::ArraySequence);
        else if (!strcmp(data_type_string, "ListSequence"))
            SwitchDataType(DataType::ListSequence);
        else if (!strcmp(data_type_string, "Deque"))
            SwitchDataType(DataType::Deque);
        else
            printf("Error: Unknown data type.");
    }
    else {
        switch (data_type_)
        {
        case DataType::DynamicArray:
            ProcessDynamicArrayCommand(command);
            break;
        case DataType::LinkedList:
            ProcessLinkedListCommand(command);
            break;
        case DataType::ListSequence:
            ProcessSequenceCommand(command);
            break;
        case DataType::ArraySequence:
            ProcessSequenceCommand(command);
            break;
        case DataType::Deque:
            ProcessDequeCommand(command);
            break;
        }
    }
}

void SimpleInterpreter::ProcessDynamicArrayCommand(char* command)
{
    if (!std::strcmp(command, "Get")) {
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= dynamic_array_->GetSize()) {
            printf("Error: Index out of range.\n");
            return;
        }
        printf("Output: %c\n", dynamic_array_->Get(index));
    }
    else if (!std::strcmp(command, "GetSize")) {
        printf("Output: %d\n", (int)dynamic_array_->GetSize());
    }
    else if (!std::strcmp(command, "Set")) {
        int index;
        scanf_s(" %d", &index);
        char item;
        scanf_s(" %c", &item);
        if (index < 0 || index >= dynamic_array_->GetSize()) {
            printf("Error: Index out of range.\n");
            return;
        }
        dynamic_array_->Set(index, item);
    }
    else if (!std::strcmp(command, "Resize")) {
        int new_size;
        scanf_s(" %d", &new_size);
        if (new_size < 0) {
            printf("Error: Invalid size.\n");
            return;
        }
        dynamic_array_->Resize(new_size);
    }
    else if (!std::strcmp(command, "Delete")) {
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= dynamic_array_->GetSize()) {
            printf("Error: Index out of range.\n");
            return;
        }
        dynamic_array_->Delete(index);
    }
    else if (!std::strcmp(command, "Help")) {
        PrintHelpDynamicArray();
    }
    else
        printf("Error: Unknown command. Try help for a list of commands.\n");
}

void SimpleInterpreter::ProcessLinkedListCommand(char* command)
{
    if (!std::strcmp(command, "GetFirst")) {
        if (linked_list_->GetLength() == 0) {
            printf("Error: Sequence is empty.\n");
            return;
        }
        printf("Output: %c\n", linked_list_->GetFirst());
    }
    else if (!std::strcmp(command, "GetLast")) {
        if (linked_list_->GetLength() == 0) {
            printf("Error: Sequence is empty.\n");
            return;
        }
        printf("Output: %c\n", linked_list_->GetLast());
    }
    else if (!std::strcmp(command, "Get")) {
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= linked_list_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        printf("Output: %c\n", linked_list_->Get(index));
    }
    else if (!std::strcmp(command, "GetLength")) {
        printf("Output: %d\n", (int)linked_list_->GetLength());
    }
    else if (!std::strcmp(command, "Set")) {
        int index;
        scanf_s(" %d", &index);
        char item;
        scanf_s(" %c", &item);
        if (index < 0 || index >= linked_list_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        linked_list_->Set(index, item);
    }
    else if (!std::strcmp(command, "Append")) {
        char item;
        scanf_s(" %c", &item);
        linked_list_->Append(item);
    }
    else if (!std::strcmp(command, "Prepend")) {
        char item;
        scanf_s(" %c", &item);
        linked_list_->Prepend(item);
    }
    else if (!std::strcmp(command, "InsertAt")) {
        char item;
        scanf_s(" %c", &item);
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= linked_list_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        linked_list_->InsertAt(item, index);
    }
    else if (!std::strcmp(command, "Delete")) {
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= linked_list_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        linked_list_->Delete(index);
    }
    else if (!std::strcmp(command, "Concat")) {
        char dir;
        scanf_s(" %c", &dir);
        Word* word = readWord();
        LinkedList<char>* linked_list = new LinkedList<char>(word->items, word->length);
        free(word->items);
        LinkedList<char>* tmp = linked_list_;
        if (dir == 'r') {
            linked_list_ = linked_list_->Concat(linked_list);
            delete(tmp);
        }
        else if (dir == 'l') {
            linked_list_ = linked_list->Concat(linked_list_);
            delete(tmp);
        }
        else
            printf("Error: Unknown direction. Should be \'r\' or \'l\'.\n");
        delete(linked_list);
    }
    else if (!std::strcmp(command, "GetSubList")) {
        int start_index, end_index;
        scanf_s(" %d", &start_index);
        scanf_s(" %d", &end_index);

        if (start_index < 0 || start_index >= linked_list_->GetLength() ||
            end_index < 0 || end_index >= linked_list_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }

        Sequence<char>* tmp = sequence_;
        linked_list_ = linked_list_->GetSubList(start_index, end_index);
        delete(tmp);
    }
    else if (!std::strcmp(command, "Help")) {
        PrintHelpLinkedList();
    }
    else
        printf("Error: Unknown command. Try Help for a list of commands.\n");
}

void SimpleInterpreter::ProcessSequenceCommand(char* command)
{
    if (!std::strcmp(command, "GetFirst")) {
        if (sequence_->GetLength() == 0) {
            printf("Error: Sequence is empty.\n");
            return;
        }
        printf("Output: %c\n", sequence_->GetFirst());
    }
    else if (!std::strcmp(command, "GetLast")) {
        if (sequence_->GetLength() == 0) {
            printf("Error: Sequence is empty.\n");
            return;
        }
        printf("Output: %c\n", sequence_->GetLast());
    }
    else if (!std::strcmp(command, "Get")) {
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= sequence_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        printf("Output: %c\n", sequence_->Get(index));
    }
    else if (!std::strcmp(command, "GetLength")) {
        printf("Output: %d\n", (int)sequence_->GetLength());
    }
    else if (!std::strcmp(command, "Set")) {
        int index;
        scanf_s(" %d", &index);
        char item;
        scanf_s(" %c", &item);
        if (index < 0 || index >= sequence_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        sequence_->Set(index, item);
    }
    else if (!std::strcmp(command, "Append")) {
        char item;
        scanf_s(" %c", &item);
        sequence_->Append(item);
    }
    else if (!std::strcmp(command, "Prepend")) {
        char item;
        scanf_s(" %c", &item);
        sequence_->Prepend(item);
    }
    else if (!std::strcmp(command, "InsertAt")) {
        char item;
        scanf_s(" %c", &item);
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= sequence_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        sequence_->InsertAt(item, index);
    }
    else if (!std::strcmp(command, "Delete")) {
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= sequence_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        sequence_->Delete(index);
    }
    else if (!std::strcmp(command, "Concat")) {
        char dir;
        scanf_s(" %c", &dir);
        Word* word = readWord();
        Sequence<char>* sequence;
        if (data_type_ == DataType::ArraySequence)
            sequence = new ArraySequence<char>(word->items, word->length);
        else
            sequence = new ListSequence<char>(word->items, word->length);
        free(word->items);
        Sequence<char>* tmp = sequence_;
        if (dir == 'r') {
            sequence_ = sequence_->Concat(sequence);
            delete(tmp);
        }
        else if (dir == 'l') {
            sequence_ = sequence->Concat(sequence_);
            delete(tmp);
        }
        else
            printf("Error: Unknown direction. Should be \'r\' or \'l\'.\n");
        delete(sequence);
    }
    else if (!std::strcmp(command, "GetSubsequence")) {
        int start_index, end_index;
        scanf_s(" %d", &start_index);
        scanf_s(" %d", &end_index);

        if (start_index < 0 || start_index >= sequence_->GetLength() ||
            end_index < 0 || end_index >= sequence_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }

        Sequence<char>* tmp = sequence_;
        sequence_ = sequence_->GetSubsequence(start_index, end_index);
        delete(tmp);
    }
    else if (!std::strcmp(command, "Help")) {
        PrintHelpSequence();
    }
    else
        printf("Error: Unknown command. Try help for a list of commands.\n");
}

void SimpleInterpreter::ProcessDequeCommand(char* command)
{
    if (!std::strcmp(command, "PushBack")) {
        char item;
        scanf_s(" %c", &item);
        deque_->PushBack(item);
    }
    else if (!std::strcmp(command, "PushFront")) {
        char item;
        scanf_s(" %c", &item);
        deque_->PushFront(item);
    }
    else if (!std::strcmp(command, "PopBack")) {
        if (deque_->IsEmpty()) {
            printf("Error: Deque is empty.\n");
            return;
        }
        printf("Output: %c\n", deque_->PopBack());
    }
    else if (!std::strcmp(command, "PopFront")) {
        if (deque_->IsEmpty()) {
            printf("Error: Deque is empty.\n");
            return;
        }
        printf("Output: %c\n", deque_->PopFront());
    }
    else if (!std::strcmp(command, "Get")) {
        int index;
        scanf_s(" %d", &index);
        if (index < 0 || index >= deque_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }
        printf("Output: %c\n", deque_->Get(index));
    }
    else if (!std::strcmp(command, "GetLength")) {
        printf("Output: %d\n", (int)deque_->GetLength());
    }
    else if (!std::strcmp(command, "GetSequenceType")) {
        printf("Output: %d\n", (int)deque_->GetSequenceType());
    }
    else if (!std::strcmp(command, "IsEmpty")) {
        if (deque_->IsEmpty())
            printf("Output: YES\n");
        else
            printf("Output: NO\n");
    }
    else if (!std::strcmp(command, "Find")) {
        Word* word = readWord();
        Sequence<char>* sequence = new ListSequence<char>(word->items, word->length);
        free(word->items);
        printf("Output: %d\n", (int)deque_->Find(sequence));
    }
    else if (!std::strcmp(command, "Concat")) {
        char dir;
        scanf_s(" %c", &dir);
        Word* word = readWord();
        Deque<char>* deque = new Deque<char>(word->items, word->length);
        free(word->items);
        Deque<char>* tmp = deque_;
        if (dir == 'r') {
            deque_ = deque_->Concat(deque);
            delete(tmp);
        }
        else if (dir == 'l'){
            deque_ = deque->Concat(deque_);
            delete(tmp);
        }
        else
            printf("Error: Unknown direction. Should be \'r\' or \'l\'.\n");
        delete(deque);
    }
    else if (!std::strcmp(command, "GetSubsequence")) {
        int start_index, end_index;
        scanf_s(" %d", &start_index);
        scanf_s(" %d", &end_index);

        if (start_index < 0 || start_index >= deque_->GetLength() ||
            end_index < 0 || end_index >= deque_->GetLength()) {
            printf("Error: Index out of range.\n");
            return;
        }

        Deque<char>* tmp = deque_;
        deque_ = deque_->GetSubsequence(start_index, end_index);
        delete(tmp);
    }
    else if (!std::strcmp(command, "Sort")) {
        deque_->Sort(compare_char);
    }
    else if (!std::strcmp(command, "Map")) {
        char f_name[16];
        scanf_s("%s", f_name, 16);
        f_name[15] = 0;

        Deque<char>* deque = NULL;
        if (!std::strcmp(f_name, "Snake"))
            deque = deque_->Map(MakeSnakeCase);
        else if (!std::strcmp(f_name, "Upper"))
            deque = deque_->Map(MakeUppercase);
        else if (!std::strcmp(f_name, "Lower"))
            deque = deque_->Map(MakeLowercase);
        else
            printf("Error: Unknown function. Should be Snake, Upper or Lower\n");
        if (deque) {
            delete(deque_);
            deque_ = deque;
        }
    }
    else if (!std::strcmp(command, "Where")) {
        char f_name[16];
        scanf_s("%s", f_name, 16);
        f_name[15] = 0;

        Deque<char>* deque = NULL;
        if (!std::strcmp(f_name, "NotSpace"))
            deque = deque_->Where(IsNotSpace);
        else if (!std::strcmp(f_name, "Upper"))
            deque = deque_->Where(IsUppercase);
        else if (!std::strcmp(f_name, "Lower"))
            deque = deque_->Where(IsLowercase);
        else
            printf("Error: Unknown function. Should be NotSpace, Upper or Lower\n");
        if (deque) {
            delete(deque_);
            deque_ = deque;
        }
    }
    else if (!std::strcmp(command, "Reduce")) {
        char f_name[16];
        scanf_s("%s", f_name, 16);
        f_name[15] = 0;

        char result = 0;
        if (!std::strcmp(f_name, "Spaces"))
            result = deque_->Reduce(CountSpaces, '0');
        else if (!std::strcmp(f_name, "Upper"))
            result = deque_->Reduce(CountUppercase, '0');
        else if (!std::strcmp(f_name, "Lower"))
            result = deque_->Reduce(CountLowercase, '0');
        else
            printf("Error: Unknown function. Should be NotSpace, Upper or Lower\n");
        if (result)
            printf("Output: %c\n", result);
    }
    else if (!std::strcmp(command, "Split")) {
        char item;
        scanf_s(" %c", &item);
        Deque<Deque<char>*>* splitted = deque_->Split(item);
        for (int i = 0; i < splitted->GetLength(); i++) {
            printf("Output: ");
            Deque<char>* part = splitted->Get(i);
            for (int j = 0; j < part->GetLength(); j++) {
                printf("%c", part->Get(j));
            }
            if (part->Get(part->GetLength() - 1) == ' ')
                printf("<");
            printf("\n");
        }
    }
    else if (!std::strcmp(command, "Help")) {
        PrintHelpDeque();
    }
    else
        printf("Error: Unknown command. Try help for a list of commands.\n");
}

SimpleInterpreter::SimpleInterpreter(char* items, size_t length, DataType data_type)
{
    data_type_ = DataType::LinkedList;
    linked_list_ = new LinkedList<char>(items, length);
    SwitchDataType(data_type);
}

SimpleInterpreter::~SimpleInterpreter()
{
    switch (data_type_)
    {
    case DataType::DynamicArray:
        delete(dynamic_array_);
        break;
    case DataType::LinkedList:
        delete(linked_list_);
        break;
    case DataType::ListSequence:
        delete(sequence_);
        break;
    case DataType::ArraySequence:
        delete(sequence_);
    case DataType::Deque:
        delete(deque_);
        break;
    }
}

void SimpleInterpreter::Start()
{
    while (true) {
        PrintStatus();

        char command[32];
        printf("(User): ");
        scanf_s("%s", command, 32);
        command[31] = 0;

        if (!strcmp(command, "Quit"))
            break;
        
        ProcessCommand(command);
    }
}
