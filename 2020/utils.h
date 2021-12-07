#ifndef UTILS
#define UTILS
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <regex>
using namespace std;
struct line {
	char* content;
	line *next, *prev;
};
struct Results {
    string p1;
    string p2;
};
line* read_lines(const char* file);
line* copy_lines(line* ln);
void clean_lines(line* head);
void merge_sort(line** head_ref);
Results* new_results(string p1, string p2);
#endif
