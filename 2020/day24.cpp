#include "../utils.h"
#include <array>
#include <set>
#include <string.h>
#include <unordered_map>

class Day24 {
	int part_one(line* ln, unordered_map<string, array<int, 3>>* directions,
				 set<array<int, 3>>* black_tiles)
	{
		if (ln == NULL) return 0;
		int s_len = strlen(ln->content);
		array<int, 3> reference = {0, 0, 0};
		for (int i = 0; i < s_len; i++) {
			string s = string(1, ln->content[i]);
			if (s == "n" || s == "s")
				s.append(string(1, ln->content[i + 1])), i++;
			reference = update_coords(reference, &directions->at(s));
		}
		if (black_tiles->count(reference) > 0) {
			black_tiles->erase(reference);
			return -1 + part_one(ln->next, directions, black_tiles);
		};
		black_tiles->insert(reference);
		return 1 + part_one(ln->next, directions, black_tiles);
	}
	int part_two(line* ln, unordered_map<string, array<int, 3>>* directions,
				 set<array<int, 3>>* black_tiles)
	{
		for (int i = 0; i < 100; i++) {
			set<array<int, 3>> new_black_tiles, all_tiles;
			for (const array<int, 3>& v : *black_tiles) {
				all_tiles.insert(v);
				for (auto& it : *directions)
					all_tiles.insert(update_coords(v, &it.second));
			}
			for (const array<int, 3>& v : all_tiles) {
				int neighbours = 0;
				int black = black_tiles->count(v);
				for (auto& it : *directions)
					if (black_tiles->count(update_coords(v, &it.second)) > 0)
						neighbours++;
				if ((black && !(neighbours == 0 || neighbours > 2)) ||
					(!black && neighbours == 2))
					new_black_tiles.insert(v);
			}
			*black_tiles = new_black_tiles;
		}
		return black_tiles->size();
	}
	array<int, 3> update_coords(array<int, 3> v1, array<int, 3>* v2)
	{
		for (int i = 0; i < 3; i++) (v1)[i] += (*v2)[i];
		return v1;
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day24\n";
		clock_t begin = clock();
		set<array<int, 3>> black_tiles;
		unordered_map<string, array<int, 3>> directions = {
			{"ne", {1, 0, -1}}, {"nw", {0, 1, -1}}, {"w", {-1, 1, 0}},
			{"e", {1, -1, 0}},	{"se", {0, -1, 1}}, {"sw", {-1, 0, 1}}};
		cout << "  Part one: " << part_one(first, &directions, &black_tiles)
			 << endl;
		cout << "  Part two: " << part_two(first, &directions, &black_tiles)
			 << endl;
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		cout << "  time spent: " << time_spent << 's' << endl;
		clean_lines(first);
	}
};
#ifndef MAIN
int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Missing input file name!";
		return 1;
	}
	Day24 x = Day24();
	x.print_results(argv[1]);
	return 0;
}
#endif
