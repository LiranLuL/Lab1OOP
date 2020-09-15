#include "Stack.h"
List::~List() //ДЕСТРУКТОР ДЛЯ ОЧИСТКИ ПАМЯТИ
{
    Node* temp = head;                     //Временный указатель на начало списка
    while (temp != NULL)                   //Пока в списке что-то есть
    {
        temp = head->next;                 //Резерв адреса на следующий элемент списка
        delete head;                       //Освобождение памяти от первой структуры как элемента списка
        head = temp;                       //Сдвиг начала на следующий адрес, который берем из резерва
    }
}


//ФУНКЦИЯ ЗАПОЛНЕНИЯ ИНФОРМАЦИОННЫХ ПОЛЕЙ СТРУКТУРЫ NODE И ДОБАВЛЕНИЯ ЭТОЙ СТРУКТУРЫ В СПИСОК

void List::Add(Card card)
{
    Node* temp = new Node;              //Выделение памяти для нового звена списка
    temp->card = card;                        //Временное запоминание принятого параметра 
    temp->next = NULL;                  //Указание, что следующее звено новосозданной структуры пока пустое
    if (head != NULL)                   //Если список не пуст
    {
        tail->next = temp;              //Указание, что следующее звено списка это новосозданная структура
        tail = temp;
    }
    else
    {
        head = tail = temp;      //Если список не пуст, добавление первого элемента
    }
}

//ФУНКЦИЯ ИЗЪЯТИЯ ЭЛЕМЕНТА ИЗ ОЧЕРЕДИ
void List::Del()
{
    if (head != NULL)
    {
        Node* temp = head;              //Обращаемся к началу списка с помощью вспомогательного указателя
        head = head->next;              //Сдвиг начала списка
        delete temp;                    //Освобождение памяти от предыдущего звена списка
    }
}

Card List::Find_best()
{
    Card max;
    max = head->card;
    Node* temp = head;                  //Временный указатель на начало списка
    while (temp != NULL)                //Пока в списке что-то встречается
    {
        if (temp->card.GetRank() > max.GetRank())
        {
            max = temp->card;
        }
        temp = temp->next;             //Сдвигаем указатель на начало на адрес следующего элемента
    }
    return max;
}

Card List::Find_best(char suit[])
{
    Card max;
    bool flag = 0;
    Node* temp = head;
    while (temp != NULL)
    {
        if (strcmp(suit, temp->card.GetSuit()) == 0)
        {
            flag = 1;
            max = temp->card;
        }
        temp = temp->next;
    }
    if (!flag)
    {
        char a[3] = "0";
        char b[8] = "no suit";
        max.SetRank(a);
        max.SetSuit(b);
    }
    return max;
}
