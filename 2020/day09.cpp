#include "../utils.h"
#include <unordered_map>

class Day09 {
	int part_one(line* ln, unordered_map<int, int>* preamble, int idx)
	{
		int x = stoi(ln->content);
		unordered_map<int, int> cur_values;
		for (unsigned int i = 0; i < 25; i++) {
			if (cur_values.count(x - (*preamble).at(i)) > 0) {
				(*preamble)[idx] = x;
				return part_one(ln->next, preamble, (idx + 1) % 25);
			}
			cur_values[(*preamble).at(i)] = 1;
		}
		return x;
	}
	int part_two(line* ln, int sum)
	{
		int x = find_sum(ln, 0, sum, -1, -1);
		return x != -1 ? x : part_two(ln->next, sum);
	}
	int find_sum(line* ln, int cur_sum, int sum, int min, int max)
	{
		if (cur_sum > sum) return -1;
		int x = stoi(ln->content);
		if (min == -1 || x < min) min = x;
		if (max == -1 || x > max) max = x;
		cur_sum += x;
		if (cur_sum == sum) return min + max;
		return find_sum(ln->next, cur_sum, sum, min, max);
	}
	line* set_preamble(line* ln, int idx, unordered_map<int, int>* preamble)
	{
		if (idx >= 25) return ln;
		(*preamble)[idx] = stoi(ln->content);
		return set_preamble(ln->next, idx + 1, preamble);
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day09\n";
		clock_t begin = clock();
		unordered_map<int, int> preamble;
		int x = part_one(set_preamble(first, 0, &preamble), &preamble, 0);
		cout << "  Part one: " << x << endl;
		cout << "  Part two: " << part_two(first, x) << endl;
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
	Day09 x = Day09();
	x.print_results(argv[1]);
	return 0;
}
#endif
