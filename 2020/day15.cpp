#include "../utils.h"
#include <sstream>
#include <unordered_map>

class Day15 {
	int part_one(line* ln) { return memory_game(ln, 2020); }
	int part_two(line* ln) { return memory_game(ln, 30000000); }
	int memory_game(line* ln, int count)
	{
		unordered_map<int, int> spoken;
		stringstream ss = stringstream((string)ln->content);
		string token;
		int i = 0;
		int prev = -1;
		while (getline(ss, token, ',')) {
			int x = stoi(token);
			if (prev != -1) spoken[prev] = i;
			prev = x;
			i++;
		}
		for (int turn = i + 1; turn <= count; turn++) {
			int x = spoken.count(prev);
			if (x != 0) x = (turn - 1) - spoken.at(prev);
			spoken[prev] = turn - 1;
			prev = x;
		}
		return prev;
	}
	int spoken_number(int turn, int prev, unordered_map<int, int>* spoken)
	{
		int x = (*spoken).count(prev);
		if (x != 0) {
			x = (turn - 1) - (*spoken).at(prev);
		}
		(*spoken)[prev] = turn - 1;
		return x;
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day15\n";
		clock_t begin = clock();
		cout << "  Part one: " << part_one(first) << endl;
		cout << "  Part two: " << part_two(first) << endl;
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
	Day15 x = Day15();
	x.print_results(argv[1]);
	return 0;
}
#endif
