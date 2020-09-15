#define _CRT_SECURE_NO_WARNINGS

#include "Cardatch.h"

	void Cardatch::Console()
	{
		try											  //just check file
		{											  //just check file
			Read_all();								  //just check file
		}											  //just check file
		catch (std::exception& e)					  //just check file
		{											  //just check file
			std::cout << e.what();					  //just check file
		}											  //just check file
		int command = 1;
		std::cout << "1 - Shuffle\n";
		std::cout << "2 - Comparison couple cards\n";
		std::cout << "3 - Simulation game\n";
		std::cout << "4 - Print all cards\n";
		std::cout << "0 - Exit.\n";
		while (command)
		{
			std::cout << "Enter a command: ";
			std::cin >> command;

			switch (command)
			{
			case 0:
				break;
			case 1:
				Shuffle_deck();
				std::cout << "The deck is shuffled" << std::endl;
				break;
			case 2:
			{
				std::cout << "Type two cards: rank and suit (Rank max 2 symbols and capital letter, Suit max 7 symbols and lowercase letter):\n";
				int out = Ñomparison_couple_cards();
				if (out == 1)
				{
					std::cout << "First player WIN!\n";
				}
				if (out == 2)
				{
					std::cout << "Second player WIN!\n";
				}
				if (out == 3)
				{
					std::cout << "Different suits\n";
				}
				break;
			}
			case 3:
				std::fprintf(stdout, "How much cards for one player? (1-8)\n");
				int how;
				std::cin >> how;
				if (how >= 1 && how <= 8)
				{
					std::fprintf(stdout, "1 - automode\n2 - handmode\n");
					int as;
					std::cin >> as;
					Card* all_cards = new Card[how * 4];
					if (as == 2)
					{
						char rank[3], suit[8];
						for (int i = 0; i < how * 4; i++)
						{
							Ask_card(rank, suit, &all_cards[i]);
						}
					}
					if (as == 1)
					{
						for (int i = 0; i < how * 4; i++)
						{
							all_cards[i] = deck[i];
						}
					}
					Table_for_playing* table = Create_four_places(how, all_cards);
					Card max = Identify_winner(how, table, all_cards);
					Print_one_card(max);
					//int* a = new int[222]; //òåñò íà óòå÷êó ïàìÿòè
					delete[] all_cards;
					Delete_table(table);
				}
				else
				{
					std::cout << "Impossible\n";
				}
				break;
			case 4:
				Print_all();
				break;
			default:
				std::cout << "Invalid command. Try again.\n";
				break;
			}
		}
	}

	const static int _deck_size = 32;

	Card deck[_deck_size];

	void Cardatch::Delete_table(Table_for_playing* table) const
	{
		table->first_player.~List();
		table->second_player.~List();
		table->third_player.~List();
		table->fourth_player.~List();
		delete table;
	}

	void Cardatch::Print_one_card(Card card) const
	{
		std::fprintf(stdout, "|------------|\n|%2s          |\n|            |\n|            |\n|  %8s  |\n|            | <----WIN\n|            |\n|            |\n|------------|\n\n", card.GetRank(), card.GetSuit());
	}

	void Cardatch::Ask_card(char* rank, char* suit, Card* new_card) const
	{
		std::cout << "Type card: rank and suit (Rank max 2 symbols and capital letter, Suit max 7 symbols and lowercase letter):\n";
		std::cin >> rank >> suit;
		while (Calculate_sum(rank) == 0)
		{
			std::cout << "Incorrect data. Please try again.\n";
			std::cout << "Type card: rank and suit (Rank max 2 symbols and capital letter, Suit max 7 symbols and lowercase letter):\n";
			std::cin >> rank >> suit;
		}
		new_card->SetRank(rank);
		new_card->SetSuit(suit);
	}
	//Return 1 - first card win, 2 - second win, 3 - diffrent suits
	int Cardatch::Ñomparison_couple_cards() const
	{
		//Card first = deck[rand() % 32];				//automode
		//Card second = deck[rand() % 32];				//automode
		Card first, second;
		char rank[3], suit[8];
		Ask_card(rank, suit, &first);
		Ask_card(rank, suit, &second);
		if (strcmp(first.GetSuit(), second.GetSuit()) == 0)
		{
			if (Calculate_sum(first.GetRank()) < Calculate_sum(second.GetRank()))
			{
				return 1;
			}
			else
			{
				return 2;
			}
		}
		else
		{
			return 3;
		}
	}

	void Cardatch::Read_all()
	{
		const char* path = "OriginDeck.txt";
		char rank[3], suit[8];
		FILE* Input;
		if ((Input = fopen(path, "r")) == NULL)
		{
			throw "File not found.";
		}
		else
		{
			for (int i = 0; i < _deck_size; i++)
			{
				fscanf(Input, "%s %s\n", rank, suit);
				deck[i].SetRank(rank);
				deck[i].SetSuit(suit);
			}
			fclose(Input);
		}
	}

	void Cardatch::Print_all()
	{
		for (int i = 0; i < _deck_size; i++)
		{
			std::fprintf(stdout, "|------------|\n|%2s          |\n|            |\n|            |\n|  %8s  |\n|            |\n|            |\n|            |\n|------------|\n\n", deck[i].GetRank(), deck[i].GetSuit());
		}
	}

	void Cardatch::Shuffle_deck()
	{
		srand(time(0));
		int n = _deck_size;
		while (n > 1)
		{
			int ind = rand() % _deck_size;
			n--;
			Card temp = deck[n];
			deck[n] = deck[ind];
			deck[ind] = temp;
		}
	}

	Card Cardatch::Identify_winner(const int how, Table_for_playing* table, const Card* all_cards) const
	{
		Card temp = table->first_player.Find_best();
		char* suit = temp.GetSuit();
		Card four_best_cards[4] =
		{
			table->first_player.Find_best(),
			table->second_player.Find_best(suit),
			table->third_player.Find_best(suit),
			table->fourth_player.Find_best(suit)
		};
		suit = nullptr;
		delete suit;
		Card max = four_best_cards[0];
		for (int i = 1; i < 4; i++)
		{
			if (Calculate_sum(max.GetRank()) < Calculate_sum(four_best_cards[i].GetRank()))
			{
				max = four_best_cards[i];
			}
		}
		return max;
	}

	Table_for_playing* Cardatch::Create_four_places(const int how_much_cards, const Card* all_cards) const
	{
		Table_for_playing* table = new Table_for_playing;
		for (int j = 0; j < how_much_cards; j += 4)
		{
			table->first_player.Add(all_cards[j]);
			table->second_player.Add(all_cards[j + 1]);
			table->third_player.Add(all_cards[j + 2]);
			table->fourth_player.Add(all_cards[j + 3]);
		}
		return table;
	}

	int Cardatch::Calculate_sum(char* rank) const
	{
		int sum = 0;
		switch (*rank)
		{
		case 54:
			sum += 6;
			break;          //seven = 7,
		case 55: 			//eight = 8,
			sum += 7;		//nine = 9,
			break;			//ten = 10,
		case 56: 			//jack = 11,
			sum += 8;		//queen = 12,
			break; 			//king = 13,
		case 57:			//ace = 14
			sum += 9;
			break;
		case 49:
			sum += 10;
			break;
		case 74:
			sum += 11;
			break;
		case 81:
			sum += 12;
			break;
		case 75:
			sum += 13;
			break;
		case 65:
			sum += 14;
			break;
		}
		return sum;
	}