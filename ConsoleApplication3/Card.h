#pragma once
class Card
{
public:
	char* const GetSuit();
	char* const GetRank();
	void SetSuit(char suit[]);
	void SetRank(char rank[]);
private:
	char _suit[8];
	char _rank[3];
};