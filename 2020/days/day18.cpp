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
    Results* results(line* first)
    {
        return new_results(to_string(part_one(first)),
                           to_string(part_two(first)));
    }
};
