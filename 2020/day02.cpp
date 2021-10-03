#include "../utils.h"
#include <algorithm>

class Day02 {
	int part_one(line* ln)
	{
		if (ln == NULL) return 0;
		string s = ln->content;
		int x = s.find('-');
		int y = s.find(' ');
		int min = stoi(s.substr(0, x));
		int max = stoi(s.substr(x + 1, y - x));
		char letter = s[s.find(' ') + 1];
		string p = s.substr(s.find(": ") + 2);
		int c = count(p.begin(), p.end(), letter);
		return (c >= min && c <= max) + part_one(ln->next);
	}
	int part_two(line* ln)
	{
		if (ln == NULL) return 0;
		string s = ln->content;
		int x = s.find('-');
		int y = s.find(' ');
		int pos1 = stoi(s.substr(0, x)) - 1;
		int pos2 = stoi(s.substr(x + 1, y - x)) - 1;
		char letter = s[s.find(' ') + 1];
		string p = s.substr(s.find(": ") + 2);
		return ((p[pos1] == letter) ^ (p[pos2] == letter)) + part_two(ln->next);
	}
  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day02\n";
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
int _main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Missing input file name!";
		return 1;
	}
	Day02 x = Day02();
	x.print_results(argv[1]);
	return 0;
}
#endif
