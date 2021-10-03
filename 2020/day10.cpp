#include "../utils.h"
#include <unordered_map>

class Day10 {
	int part_one(line* ln, int ones, int threes, int prev)
	{
		if (ln == NULL) return ones * (threes + 1);
		int x = stoi(ln->content);
		if (x - prev == 1)
			ones++;
		else if (x - prev == 3)
			threes++;
		return part_one(ln->next, ones, threes, x);
	}
	long long part_two(line* ln, unordered_map<int, long>* memo, int idx)
	{
		if (ln == NULL) return 1;
		if ((*memo).count(idx) > 0) return (*memo).at(idx);
		line* l = (idx == 0) ? ln : ln->next;
		int x = (idx == 0) ? 0 : stoi(ln->content);
		int i2 = idx, prev = x;
		(*memo)[idx] = 0;
		while (1) {
			int y = (l == NULL) ? prev + 3 : stoi(l->content);
			(*memo)[idx] += (y - x <= 3) ? part_two(l, memo, ++i2) : 0;
			if (y - x > 3 || l == NULL) break;
			prev = y;
			l = l->next;
		}
		return (*memo)[idx];
	}
  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day10" << endl;
		clock_t begin = clock();
		merge_sort(&first);
		cout << "  Part one: " << part_one(first, 0, 0, 0) << endl;
		unordered_map<int, long> memo;
		cout << "  Part two: " << part_two(first, &memo, 0) << endl;
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
	Day10 x = Day10();
	x.print_results(argv[1]);
	return 0;
}
#endif
