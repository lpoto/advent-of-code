#include "../utils.h"
#include <deque>
#include <unordered_set>

class Day22 {
	int part_one(deque<int> deck1, deque<int> deck2)
	{
		while (deck1.size() > 0 && deck2.size() > 0) {
			int p1 = deck1.front(), p2 = deck2.front();
			deck1.pop_front(), deck2.pop_front();
			if (p1 > p2)
				deck1.push_back(p1), deck1.push_back(p2);
			else
				deck2.push_back(p2), deck2.push_back(p1);
		}
		return (deck1.size() > 0) ? deck_score(&deck1) : deck_score(&deck2);
	}
	int part_two(deque<int> deck1, deque<int> deck2)
	{
		unordered_set<string> memo;
		int winner = recursive_combat(&deck1, &deck2, &memo);
		if (winner == 1) return deck_score(&deck1);
		return deck_score(&deck2);
	}
	int recursive_combat(deque<int>* deck1, deque<int>* deck2,
						 unordered_set<string>* memo)
	{
		int s1 = 1, s2 = 1, p1, p2, rw;
		while (s1 > 0 && s2 > 0) {
			if (infinite_games_prevention(deck1, deck2, memo) == 1) break;
			p1 = deck1->front(), p2 = deck2->front();
			deck1->pop_front(), deck2->pop_front();
			rw = round_winner(*deck1, *deck2, p1, p2);
			if (rw == 1)
				deck1->push_back(p1), deck1->push_back(p2);
			else
				deck2->push_back(p2), deck2->push_back(p1);
			s1 = deck1->size(), s2 = deck2->size();
		}
		return (s1 == 0) ? 2 : 1;
	}
	int round_winner(deque<int> deck1, deque<int> deck2, int p1, int p2)
	{
		if (p1 > (int)deck1.size() || p2 > (int)deck2.size())
			return (p1 > p2) ? 1 : 2;
		unordered_set<string> memo;
		deck1.resize(p1), deck2.resize(p2);
		return recursive_combat(&deck1, &deck2, &memo);
	}
	int infinite_games_prevention(deque<int>* deck1, deque<int>* deck2,
								  unordered_set<string>* memo)
	{
		string s;
		for (deque<int>::iterator i = deck1->begin(); i != deck1->end(); i++)
			s.append(to_string(*i));
		s.append("|");
		for (deque<int>::iterator i = deck2->begin(); i != deck2->end(); i++)
			s.append(to_string(*i));
		if (memo->count(s) > 0) return 1;
		memo->insert(s);
		return 0;
	}
	int deck_score(deque<int>* deck)
	{
		int r = 0, x = 0;
		for (deque<int>::reverse_iterator i = deck->rbegin(); i != deck->rend();
			 i++)
			r += (*i) * (++x);
		return r;
	}
	void build_deck(line** ln, deque<int>* deck)
	{
		if (ln == NULL || (*ln)->content[0] == '\n') return;
		deck->push_back(stoi((*ln)->content));
		if ((*ln)->next == NULL) return;
		(*ln) = (*ln)->next;
		build_deck(ln, deck);
	}

  public:
    Results* results(line* first)
    {
		deque<int> deck1, deck2;
		first = first->next;
		build_deck(&first, &deck1);
		first = first->next->next;
		build_deck(&first, &deck2);
        return new_results(to_string(part_one(deck1, deck2)),
                           to_string(part_two(deck1, deck2)));
    }
};
