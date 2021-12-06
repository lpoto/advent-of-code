#include "../utils.h"
#include <algorithm>
#include <sstream>
#include <unordered_map>

enum fields { byr, iyr, eyr, hgt, hcl, ecl, pid, cid };

class Day04 {
	int part_one(line* ln, unordered_map<string, int> fields)
	{
		string s;
		while (ln != NULL && ln->content[0] != '\n') {
			s.append(ln->content);
			ln = ln->next;
		}
		for (auto& it : fields)
			if (it.second != cid && s.find(it.first) == string::npos)
				return ln == NULL ? 0 : part_one(ln->next, fields);
		return ln == NULL ? 1 : 1 + part_one(ln->next, fields);
	}
	int part_two(line* ln, unordered_map<string, int> fields)
	{
		string s;
		while (ln != NULL && ln->content[0] != '\n') {
			s.append(ln->content), s.append(" ");
			ln = ln->next;
		}
		for (auto& it : fields)
			if (it.second != cid && s.find(it.first) == string::npos)
				return ln == NULL ? 0 : part_two(ln->next, fields);
		string token;
		stringstream ss = stringstream(s);
		while (getline(ss, token, ' ')) {
			string field = token.substr(0, token.find(':'));
			string data = token.substr(token.find(':') + 1);
			if (!test_field(field, data, fields))
				return ln == NULL ? 0 : part_two(ln->next, fields);
		}
		return ln == NULL ? 1 : 1 + part_two(ln->next, fields);
	}
	int test_field(string field, string data, unordered_map<string, int> fields)
	{
		switch (fields.at(field)) {
		case cid:
			return 1;
		case byr: {
			try {
				int x = stoi(data);
				if (x > 2002 || x < 1920) return 0;
				return 1;
			} catch (...) {
				return 0;
			}
		}
		case eyr: {
			try {
				int x = stoi(data);
				if (x > 2030 || x < 2020) return 0;
				return 1;
			} catch (...) {
				return 0;
			}
		}
		case iyr: {
			try {
				int x = stoi(data);
				if (x > 2020 || x < 2010) return 0;
				return 1;
			} catch (...) {
				return 0;
			}
		}
		case hgt: {
			int i = data.find("in"), cm = 0;
			if (i == -1) i = data.find("cm"), cm = 1;
			if (i == -1) return 0;
			try {
				int x = stoi(data.substr(0, i));
				if ((!cm && (x < 59 || x > 76)) || (cm && (x < 150 || x > 193)))
					return 0;
				return 1;
			} catch (...) {
				return 0;
			}
		}
		case hcl: {
			if (data.size() != 7 or data[0] != '#') return 0;
			for (int i = 1; i < 8; i++)
				if (data[i] < 'a' && data[i] > 'f' && data[i] < '0' &&
					data[i] > '9')
					return 0;
			return 1;
		}
		case ecl: {
			string vals[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
			string* x = find(begin(vals), end(vals), data);
			if (x == end(vals)) return 0;
			return 1;
		}
		case pid: {
			if (data.size() != 9) return 0;
			try {
				stoi(data);
				return 1;
			} catch (...) {
				return 0;
			}
		}
		}
		return 0;
	}
  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day04\n";
		clock_t begin = clock();
		const unordered_map<string, int> fields{
			{"byr", byr}, {"iyr", iyr}, {"eyr", eyr}, {"hgt", hgt},
			{"hcl", hcl}, {"ecl", ecl}, {"pid", pid}, {"cid", cid}};
		cout << "  Part one: " << part_one(first, fields) << endl;
		cout << "  Part two: " << part_two(first, fields) << endl;
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
	Day04 x = Day04();
	x.print_results(argv[1]);
	return 0;
}
#endif
