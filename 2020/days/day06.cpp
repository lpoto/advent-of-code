#include "../utils.h"
#include <unordered_map>

class Day06 {
	int part_one(line* ln, int p_two)
	{
		unordered_map<char, int> answers;
		string s;
		int people = 0;
		while (1) {
			if (ln == NULL || ln->content[0] == '\n') break;
			s.append(ln->content);
			people++;
			ln = ln->next;
		}
		unsigned int s_size = s.size();
		int r = 0;
		for (unsigned int i = 0; i < s_size; i++) {
			int x = answers.count(s[i]);
			if (x == 0) {
				answers[s[i]] = 1;
				if (!p_two) r++;
			} else {
				answers[s[i]]++;
			}
			if (p_two && answers.at(s[i]) == people) r++;
		}
		return ln == NULL ? r : r + part_one(ln->next, p_two);
	}
	int part_two(line* ln) { return part_one(ln, 1); }

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day06\n";
		clock_t begin = clock();
		cout << "  Part one: " << part_one(first, 0) << endl;
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
		cout << "Missing input file name!" << endl;
		return 1;
	}
	Day06 x = Day06();
	x.print_results(argv[1]);
	return 0;
}
#endif
