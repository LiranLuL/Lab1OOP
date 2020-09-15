#pragma once
#include "Card.h"
#include <cstring>

//—“–” “”–¿ ¡”ƒ≈“ ›À≈Ã≈Õ“ŒÃ —œ»— ¿

struct Node
{
    Card card;
    Node* next;
};

class List
{
    Node* head, * tail;               
public:
    List() :head(NULL), tail(NULL) {};
    ~List();                          
    void Add(Card card);              
    void Del();
    Card Find_best();
    Card Find_best(char suit[]);
};