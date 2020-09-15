#include "Stack.h"
List::~List() //���������� ��� ������� ������
{
    Node* temp = head;                     //��������� ��������� �� ������ ������
    while (temp != NULL)                   //���� � ������ ���-�� ����
    {
        temp = head->next;                 //������ ������ �� ��������� ������� ������
        delete head;                       //������������ ������ �� ������ ��������� ��� �������� ������
        head = temp;                       //����� ������ �� ��������� �����, ������� ����� �� �������
    }
}


//������� ���������� �������������� ����� ��������� NODE � ���������� ���� ��������� � ������

void List::Add(Card card)
{
    Node* temp = new Node;              //��������� ������ ��� ������ ����� ������
    temp->card = card;                        //��������� ����������� ��������� ��������� 
    temp->next = NULL;                  //��������, ��� ��������� ����� ������������� ��������� ���� ������
    if (head != NULL)                   //���� ������ �� ����
    {
        tail->next = temp;              //��������, ��� ��������� ����� ������ ��� ������������� ���������
        tail = temp;
    }
    else
    {
        head = tail = temp;      //���� ������ �� ����, ���������� ������� ��������
    }
}

//������� ������� �������� �� �������
void List::Del()
{
    if (head != NULL)
    {
        Node* temp = head;              //���������� � ������ ������ � ������� ���������������� ���������
        head = head->next;              //����� ������ ������
        delete temp;                    //������������ ������ �� ����������� ����� ������
    }
}

Card List::Find_best()
{
    Card max;
    max = head->card;
    Node* temp = head;                  //��������� ��������� �� ������ ������
    while (temp != NULL)                //���� � ������ ���-�� �����������
    {
        if (temp->card.GetRank() > max.GetRank())
        {
            max = temp->card;
        }
        temp = temp->next;             //�������� ��������� �� ������ �� ����� ���������� ��������
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
