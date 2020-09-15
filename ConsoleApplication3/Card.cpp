#define _CRT_SECURE_NO_WARNINGS
#include <cstring> 
#include "Card.h"

char* const Card::GetSuit()
{
	return _suit;
}
char* const Card::GetRank()
{
	return _rank;
}
void Card::SetSuit(char suit[])
{
	strcpy(_suit, suit);
}
void Card::SetRank(char rank[])
{
	strcpy(_rank, rank);
}