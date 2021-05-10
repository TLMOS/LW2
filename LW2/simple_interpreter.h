#include "dynamic_array.h"
#include "linked_list.h"
#include "sequence.h"
#include "list_sequence.h"
#include "array_sequence.h"
#include "deque.h"
#pragma once

class SimpleInterpreter
{
private:
    DynamicArray<char>* dynamic_array_;
    LinkedList<char>* linked_list_;
    Sequence<char>* sequence_;
    Deque<char>* deque_;

    enum class DataType
    {
        None = 1,
        DynamicArray,
        LinkedList,
        ListSequence,
        ArraySequence,
        Deque
    };
    DataType data_type_;

    struct Word
    {
        size_t length{};
        char* items{};
    };

    Word* readWord();
    void SwitchDataType(DataType data_type);
    void SetItems(char* items, size_t length);
    void PrintStatus();
    void ProcessCommand(char* command);
    void ProcessDynamicArrayCommand(char* command);
    void ProcessLinkedListCommand(char* command);
    void ProcessSequenceCommand(char* command);
    void ProcessDequeCommand(char* command);

public:
    SimpleInterpreter(char* items = (char*)"Hello world!", size_t length = 12, 
        DataType data_type = DataType::Deque);
    ~SimpleInterpreter();
    void Start();
};

/*
void printCharString(struct String* s) {
    size_t size = getSize(s);
    for (int i = 0; i < size; i++) {
        printf("%c", getChar(s, i));
    }
}

void* makeItSnake(void* x) {
    char* y = malloc(sizeof(char));
    if (*(char*)x == ' ')
        *y = '_';
    else
        *y = *(char*)x;
    return (void*)y;
}

void* makeItCaps(void* x) {
    char* y = malloc(sizeof(char));
    if (*(char*)x <= 122 && *(char*)x >= 97)
        *y = *(char*)x - 32;
    else
        *y = *(char*)x;
    return (void*)y;
}

void launchInterpreter() {
    struct String* s = createZerosChar(0);
    while (1) {
        printf("String: ");
        printCharString(s);
        if (getChar(s, getSize(s) - 1) == ' ')
            printf("<");
        printf("\n");

        char command[32];
        printf("(user): ");
        scanf_s("%s", command, 32);

        if (!strcmp(command, "createFromValues") || !strcmp(command, "=")) { // createFromValues
            char values[256];
            for (int i = 0; i < 256; i++)
                values[i] = 0;
            scanf_s(" %[^\n]s", values, 256);
            size_t size = 0;
            for (int i = 0; i < 256; i++)
                if (values[i] != 0)
                    size += 1;
                else
                    break;

            freeString(s);
            s = createFromValuesChar(size, values);
        }
        else if (!strcmp(command, "createZeros") || !strcmp(command, "=0")) { // createZeros
            size_t size = 0;
            scanf_s(" %d", &size);
            freeString(s);
            s = createZerosChar(size);
        }
        else if (!strcmp(command, "set")) { // setChar
            int idx = 0;
            char x = 0;
            scanf_s(" %d", &idx);
            scanf_s(" %c", &x, 1);
            if (idx < getSize(s) && idx >= 0)
                setChar(s, idx, x);
            else
                printf("Error:  %d is out of bounds of string.\n", idx);
        }
        else if (!strcmp(command, "get")) { // getChar
            int idx = 0;
            scanf_s(" %d", &idx);
            if (idx < getSize(s) && idx >= 0)
                printf("Info:   %c\n", getChar(s, idx));
            else
                printf("Error:  %d is out of bounds of string.\n", idx);
        }
        else if (!strcmp(command, "size")) {
            printf("Info:   %d\n", getSize(s));
        }
        else if (!strcmp(command, "equals")) { // equals
            char values[256];
            for (int i = 0; i < 256; i++)
                values[i] = 0;
            scanf_s(" %[^\n]s", values, 256);
            size_t size = 0;
            for (int i = 0; i < 256; i++)
                if (values[i] != 0)
                    size += 1;
                else
                    break;

            struct String* s2 = createFromValuesChar(size, values);
            if (equals(s, s2))
                printf("Info: True\n");
            else
                printf("Info: False\n");
            freeString(s2);
        }
        else if (!strcmp(command, "fill")) { // fill
            char x = 0;
            scanf_s(" %c", &x, 1);
            fillChar(s, x);
        }
        else if (!strcmp(command, "swap")) { // swap
            int a = 0;
            int b = 0;
            scanf_s(" %d", &a);
            scanf_s(" %d", &b);
            if (a < getSize(s) && b < getSize(s) && a >= 0 && b >= 0)
                swap(s, a, b);
            else
                printf("Error:  %d is out of bounds of string.\n", max(a, b));
        }
        else if (!strcmp(command, "reverse")) { // reverse
            reverse(s);
        }
        else if (!strcmp(command, "concat") || !strcmp(command, "concatenate")) { // concatenate
            char dir = 0;
            scanf_s(" %c", &dir, 1);
            char values[256];
            for (int i = 0; i < 256; i++)
                values[i] = 0;
            scanf_s(" %[^\n]s", values, 256);
            size_t size = 0;
            for (int i = 0; i < 256; i++)
                if (values[i] != 0)
                    size += 1;
                else
                    break;

            struct String* tmp;
            struct String* s2 = createFromValuesChar(size, values);
            if (dir == 'l') {
                tmp = concatenate(s2, s);
                freeString(s);
                s = tmp;
            }
            else if (dir == 'r') {
                tmp = concatenate(s, s2);
                freeString(s);
                s = tmp;
            }
            else
                printf("Error:  Dir variable should be 'r' or 'l', got %c.\n", dir);
            freeString(s2);

        }
        else if (!strcmp(command, "sub") || !strcmp(command, "subString")) { // subString
            int a = 0;
            int b = 0;
            scanf_s(" %d", &a);
            scanf_s(" %d", &b);
            struct String* tmp;
            if (a < getSize(s) && b < getSize(s) && a >= 0 && b >= 0) {
                tmp = subString(s, a, b);
                freeString(s);
                s = tmp;
            }
            else
                printf("Error:  %d is out of bounds of string.\n", max(a, b));
        }
        else if (!strcmp(command, "snake")) { // encode + makeItSnake
            encode(s, makeItSnake);
        }
        else if (!strcmp(command, "caps")) { // encode + makeItCaps
            encode(s, makeItCaps);
        }
        else if (!strcmp(command, "del")) {
            int a = 0;
            int b = 0;
            scanf_s(" %d", &a);
            scanf_s(" %d", &b);
            if (a < getSize(s) && b < getSize(s) && a >= 0 && b >= 0)
                deleteSubString(s, a, b);
            else
                printf("Error:  %d is out of bounds of string.\n", max(a, b));
        }



    }
}
*/