#ifndef UTILS
#define UTILS
#include <iostream>
#include <unordered_map>
using namespace std;
struct line {
	char* content;
	line *next, *prev;
};
line* read_lines(const char* file);
line* copy_lines(line* ln);
void clean_lines(line* head);
void merge_sort(line** head_ref);
#endif
