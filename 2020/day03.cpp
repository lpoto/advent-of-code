#include "../utils.h"
#include <string.h>

class Day03 {
	int part_one(line* ln)
	{
		return count_trees(ln, strlen(ln->content), 0, 1, 3);
	}
	int part_two(line* ln)
	{
		int pos[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
		int size = strlen(ln->content);
		int result = 1;
		for (int i = 0; i < 5; i++) {
			result *= count_trees(ln, size, 0, pos[i][1], pos[i][0]);
		}
		return result;
	}
	int count_trees(line* ln, int size, int cur, int y, int x)
	{
		int n = (cur + x) % size;
		line* ln2 = ln;
		for (int i = 0; i < y; i++) {
			if (ln2 == NULL || ln2->next == NULL) return 0;
			ln2 = ln2->next;
		}
		return (ln2->content[n] == '#') + count_trees(ln2, size, n, y, x);
	}
  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day03\n";
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
	Day03 x = Day03();
	x.print_results(argv[1]);
	return 0;
}
#endif
