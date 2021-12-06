#define _GLIBCXX_REGEX_STATE_LIMIT 850000
#include "../utils.h"
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>

struct rule {
	char match = '0';
	vector<vector<int>> rule_ids;
};

class Day19 {
	int part_one(line* ln, unordered_map<int, rule*> rules)
	{
		if (ln == NULL) return 0;
		regex rule_0(new_regex(&rules, 0, rules.size()));
		return match_strings(ln, rule_0);
	}
	int part_two(line* ln, unordered_map<int, rule*> rules)
	{
		if (ln == NULL) return 0;
		vector<int> v1_1 = {42}, v1_2 = {42, 8};
		vector<int> v2_1 = {42, 31}, v2_2 = {42, 11, 31};
		rules.at(8)->rule_ids = {v1_1, v1_2};
		rules.at(11)->rule_ids = {v2_1, v2_2};
		regex rule_0(new_regex(&rules, 0, rules.size()));
		return match_strings(ln, rule_0);
	}
	int match_strings(line* ln, regex rule)
	{
		if (ln == NULL) return 0;
		return regex_match(ln->content, rule) + match_strings(ln->next, rule);
	}
	string new_regex(unordered_map<int, rule*>* rules, int rule_id, int depth)
	{
		if (depth == 0) return "";
		rule* cur = rules->at(rule_id);
		if (cur->match != '0') return string(1, cur->match);
		string s = "(";
		for (const vector<int>& it : cur->rule_ids) {
			for (const int& it2 : it)
				s.append((new_regex(rules, it2, depth - 1)));
			s.append("|");
		}
		if (s.back() == '|') s.pop_back();
		s.append(")");
		return s;
	}
	void extract_rules(unordered_map<int, rule*>* rules, line** ln)
	{
		string s = (*ln)->content;
		if (s == "\n") return;
		int rule_id = stoi(s.substr(0, s.find(":")));
		string s1 = s.substr(s.find(" ") + 1);
		rule* r = new rule();
		r->match = '0';
		if (s1[0] == '"') {
			r->match = s1[1];
		} else {
			int pipe_idx = s1.find("|");
			if (pipe_idx != -1) {
				vector<int> r1, r2;
				stringstream ss1 = stringstream(s1.substr(0, pipe_idx - 1));
				stringstream ss2 = stringstream(s1.substr(pipe_idx + 2));
				string token1, token2;
				while (getline(ss1, token1, ' ')) r1.push_back(stoi(token1));
				while (getline(ss2, token2, ' ')) r2.push_back(stoi(token2));
				r->rule_ids.push_back(r1), r->rule_ids.push_back(r2);
			} else {
				vector<int> r1;
				stringstream ss = stringstream(s1);
				string token;
				while (getline(ss, token, ' ')) r1.push_back(stoi(token));
				r->rule_ids.push_back(r1);
			}
		}
		(*rules)[rule_id] = r;
		(*ln) = (*ln)->next;
		extract_rules(rules, ln);
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day19\n";
		unordered_map<int, rule*> rules;
		extract_rules(&rules, &first);
		clock_t begin = clock();
		cout << "  Part one: " << part_one(first->next, rules) << endl;
		cout << "  Part two: " << part_two(first->next, rules) << endl;
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
	Day19 x = Day19();
	x.print_results(argv[1]);
	return 0;
}
#endif
