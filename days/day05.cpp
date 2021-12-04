#include "../utils.h"
#include <unordered_map>

class Day05 {
	int part_one(line* ln, int prev_id, unordered_map<int, int>* seats)
	{
		if (ln == NULL) return prev_id;
		int min = 0, max = 127;
		for (unsigned int i = 0; i < 7; i++) {
			if (ln->content[i] == 'F')
				max = min + (max - min) / 2;
			else if (ln->content[i] == 'B')
				min = min + (max - min) / 2 + 1;
		}
		int id = min * 8;
		min = 0;
		max = 7;
		for (unsigned int i = 7; i < 10; i++) {
			if (ln->content[i] == 'L')
				max = min + (max - min) / 2;
			else if (ln->content[i] == 'R')
				min = min + (max - min) / 2 + 1;
		}
		id += min;
		(*seats)[id] = 1;
		return part_one(ln->next, id > prev_id ? id : prev_id, seats);
	}
	int part_two(unordered_map<int, int>* seats)
	{
		for (auto& it : *seats) {
			if ((*seats).count(it.first + 1) == 0 &&
				(*seats).count(it.first + 2) > 0)
				return it.first + 1;
		}
		return 0;
	}
  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day05\n";
		clock_t begin = clock();
		unordered_map<int, int> seats;
		cout << "  Part one: " << part_one(first, 0, &seats) << endl;
		cout << "  Part two: " << part_two(&seats) << endl;
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
		cout << "Missing input file name!" << endl;
		return 1;
	}
	Day05 x = Day05();
	x.print_results(argv[1]);
	return 0;
}
#endif
