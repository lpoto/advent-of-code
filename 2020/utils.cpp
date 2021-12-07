#include "utils.h"
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

line* file_reader(ifstream* f);
line* new_line(ifstream* f, string s)
{
	line* ln = (line*)malloc(sizeof(line));
	int x = s.size() + 1;
	ln->content = (char*)malloc(x * sizeof(char));
	strcpy(ln->content, s.c_str());
	ln->prev = NULL;
	ln->next = file_reader(f);
	if (ln->next != NULL) ln->next->prev = ln;
	return ln;
}
line* file_reader(ifstream* f)
{
	string s;
	if (!getline(*f, s)) return NULL;
	if (s.size() == 0) s = "\n";
	return new_line(f, s);
}
line* read_lines(const char* file_name)
{
	ifstream f(file_name);
	line* head = file_reader(&f);
	f.close();
	return head;
}
line* copy_lines(line* ln)
{
	if (ln == NULL) return NULL;
	line* copy = (line*)malloc(sizeof(line));
	copy->content = (char*)malloc((strlen(ln->content) + 1) * sizeof(char));
	strcpy(copy->content, ln->content);
	copy->prev = NULL;
	copy->next = copy_lines(ln->next);
	if (copy->next != NULL) copy->next->prev = copy;
	return copy;
}
void clean_lines(line* head)
{
	if (head == NULL) return;
	clean_lines(head->next);
	free(head->content);
	free(head);
}
line* sorted_merge(line* a, line* b)
{
	line* result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (atoi(a->content) <= atoi(b->content))
		result = a, result->next = sorted_merge(a->next, b);
	else
		result = b, result->next = sorted_merge(a, b->next);
	return (result);
}
void front_back_split(line* source, line** front_ref, line** back_ref)
{
	line* fast;
	line* slow;
	slow = source, fast = source->next;
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) slow = slow->next, fast = fast->next;
	}
	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
}
void merge_sort(line** head_ref)
{
	line* head = *head_ref;
	line* a;
	line* b;
	if ((head == NULL) || (head->next == NULL)) return;
	front_back_split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*head_ref = sorted_merge(a, b);
}

Results* new_results(string p1, string p2) {
    Results* x = new Results();
    x->p1 = p1;
    x->p2 = p2;
    return x;
}
