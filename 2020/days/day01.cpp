#include "../utils.h"
#include <unordered_map>
#define SUM 2020

class Day01 {
	int part_one(line* ln)
	{
		unordered_map<int, int> sums;
		while (ln != NULL) {
			int x = stoi(ln->content);
			if (sums.count(SUM - x) > 0) return (SUM - x) * x;
			sums[x] = 1;
			ln = ln->next;
		}
		return 0;
	}
	int part_two(line* ln)
	{
		while (ln != NULL) {
			line* ln2 = ln;
			int x = stoi(ln->content);
			unordered_map<int, int> sums;
			while (ln2 != NULL) {
				int y = stoi(ln2->content);
				if (sums.count(SUM - x - y) > 0) return (SUM - x - y) * x * y;
				sums[y] = 1;
				ln2 = ln2->next;
			}
			ln = ln->next;
		}
		return 0;
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day01" << endl;
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
	Day01 x = Day01();
	x.print_results(argv[1]);
	return 0;
}
#endif
