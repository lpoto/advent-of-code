#include "../utils.h"
#include <sstream>

class Day18 {
	long part_one(line* ln)
	{
		if (ln == NULL) return 0;
		string s = spaces_to_paranthesees(ln->content);
		stringstream ss = stringstream(s);
		long number = 0;
		evaluate(&ss, &number, 0, '+', 1);
		return number + part_one(ln->next);
	}
	long part_two(line* ln)
	{
		if (ln == NULL) return 0;
		string s = spaces_to_paranthesees(ln->content);
		stringstream ss = stringstream(s);
		long number = 0;
		evaluate(&ss, &number, 0, '+', 2);
		return number + part_two(ln->next);
	}
	void evaluate(stringstream* ss, long* number, int prev, char op, int part)
	{
		string token;
		long x = 0;
		if (!getline(*ss, token, ' ') || token == ")" || token == "\0") {
			if (part == 2)
				(*number) = ((*number) == 0) ? prev : (*number) * prev;
			return;
		};
		if (token == "*") return evaluate(ss, number, prev, '*', part);
		if (token == "+") return evaluate(ss, number, prev, '+', part);
		if (token == "(")
			evaluate(ss, &x, 0, '+', part);
		else
			x = stoi(token);
		if (part == 1)
			(*number) = (op == '*') ? (*number) * x : (*number) + x;
		else if (op == '*' && prev == 0)
			prev = x;
		else if (op == '*')
			(*number) = ((*number) == 0) ? prev : (*number) * prev, prev = x;
		else
			prev += x;
		evaluate(ss, number, prev, op, part);
	}
	string spaces_to_paranthesees(string s)
	{
		int idx = s.find("(", 0);
		while (idx != -1) s.insert(idx + 1, " "), idx = s.find("(", idx + 1);
		idx = s.find(")", 0);
		while (idx != -1) s.insert(idx, " "), idx = s.find(")", idx + 2);
		return s;
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day18\n";
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
	Day18 x = Day18();
	x.print_results(argv[1]);
	return 0;
}
#endif
