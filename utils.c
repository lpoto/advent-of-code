#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

line* file_reader(FILE* f, int max_len, char* s);
line* new_line(FILE* f, int max_len, char* s)
{
	line* ln = (line*)malloc(sizeof(line));
	ln->content = (char*)malloc((max_len - 1) * sizeof(char));
	strcpy(ln->content, s);
	ln->prev = NULL;
	ln->next = file_reader(f, max_len, s);
	if (ln->next != NULL)
		ln->next->prev = ln;
	return ln;
}
line* file_reader(FILE* f, int max_len, char* s)
{
	if (!fgets(s, max_len, f)) return NULL;
	strtok(s, "\n");
	return new_line(f,  max_len, s);
}
line* read_lines(char* file, int max_len)
{
	char* s = (char*)malloc((max_len + 1) * sizeof(char));
	FILE* f = fopen(file, "r");
	line* head = file_reader(f, max_len + 1, s);
	free(s);
	fclose(f);
	return head;
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
void front_back_split(line* source,
                    line** front_ref, line** back_ref)
{
    line* fast;
    line* slow;
    slow = source, fast = source->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL)
            slow = slow->next, fast = fast->next;
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
    if ((head == NULL) || (head->next == NULL))
        return;
    front_back_split(head, &a, &b);
    merge_sort(&a);
    merge_sort(&b);
    *head_ref = sorted_merge(a, b);
}
