#include "../utils.h"
#include <unordered_map>

class Day08 {
	int part_one(line* ln)
	{
		int idx = 0, f = 0;
		unordered_map<int, int> i;
		return run_acucmulator(ln, i, &idx, &f);
	}
	int part_two(line* ln)
	{
		line* l = ln;
		while (l != NULL) {
			string s = l->content;
			string instruction = s.substr(0, s.find(' '));
			if (instruction == "acc") {
				l = l->next;
				continue;
			}
			int idx = 0, f = 0, acc = 0;
			unordered_map<int, int> i;
			if (instruction == "jmp") {
				l->content[0] = 'n', l->content[1] = 'o';
				acc = run_acucmulator(ln, i, &idx, &f);
				l->content[0] = 'j', l->content[1] = 'm';
			} else if (instruction == "nop") {
				l->content[0] = 'j', l->content[1] = 'm';
				acc = run_acucmulator(ln, i, &idx, &f);
				l->content[0] = 'n', l->content[1] = 'o';
			}
			if (!f) return acc;
			l = l->next;
		}
		return 0;
	}
	int run_acucmulator(line* ln, unordered_map<int, int> i, int* idx, int* f)
	{
		if (ln == NULL) return 0;
		string s = ln->content;
		string instruction = s.substr(0, s.find(' '));
		int count = stoi(s.substr(s.find(' ') + 1));
		if (i.count(*idx) > 0) {
			(*f) = 1;
			return 0;
		}
		i[*idx] = 1;
		if (instruction == "jmp")
			return run_acucmulator(change_line(ln, count, idx), i, idx, f);
		(*idx) += 1;
		if (instruction == "nop") return run_acucmulator(ln->next, i, idx, f);
		if (instruction == "acc")
			return count + run_acucmulator(ln->next, i, idx, f);
		return 0;
	}
	line* change_line(line* ln, int count, int* idx)
	{
		int x = count >= 0 ? count : -count;
		for (int i = 0; i < x; i++) {
			if (count > 0)
				ln = ln->next, (*idx) += 1;
			else if (count < 0)
				ln = ln->prev, (*idx) -= 1;
		}
		return ln;
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day08\n";
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
	Day08 x = Day08();
	x.print_results(argv[1]);
	return 0;
}
#endif
