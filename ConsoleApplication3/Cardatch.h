#pragma once
#include <iostream>
#include <ctime> 
#include <exception>
#include "Card.h"
#include "Stack.h"

struct Table_for_playing
{
	List first_player;
	List second_player;
	List third_player;
	List fourth_player;
};

class Cardatch
{
public:
	void Console();
private:
	const static int _deck_size = 32;
	Card deck[_deck_size];
	void Delete_table(Table_for_playing* table) const;
	void Print_one_card(Card card) const;
	void Ask_card(char* rank, char* suit, Card* new_card) const;
	//Return 1 - first card win, 2 - second win, 3 - diffrent suits
	int Ñomparison_couple_cards() const;
	void Read_all();
	void Print_all();
	void Shuffle_deck();
	Card Identify_winner(const int how, Table_for_playing* table, const Card* all_cards) const;
	Table_for_playing* Create_four_places(const int how_much_cards, const Card* all_cards) const;
	int Calculate_sum(char* rank) const;
};