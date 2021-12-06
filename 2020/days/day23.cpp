#include "../utils.h"
#include <string.h>
#include <unordered_map>

struct cup {
	long val;
	cup* next;
};

class Day23 {
	string part_one(int* vals, int vals_len)
	{
		cup* head = NULL;
		unordered_map<long, cup*> cups;
		head = circular_linked_list(vals, vals_len, vals_len, &cups);
		string s;
		turn(head, vals_len, 100, &cups);
		while (head->val != 1) head = head->next;
		for (int i = 0; i < vals_len - 1; i++) {
			head = head->next;
			s.append(to_string(head->val));
		}
		free_list(head);
		return s;
	}
	long part_two(int* vals, int vals_len)
	{
		unordered_map<long, cup*> cups;
		cup* head = circular_linked_list(vals, vals_len, 1000000, &cups);
		turn(head, 1000000, 10000000, &cups);
		cup* w = cups.at(1);
		long result = w->next->next->val * w->next->val;
		free_list(w);
		return result;
	}
	void turn(cup* head, int size, int moves, unordered_map<long, cup*>* cups)
	{
		for (int i = 0; i < moves; i++) {
			if (moves == 0) return;
			cup *c1 = head->next, *c2 = c1->next, *c3 = c2->next;
			int s = (head->val - 1 > 0) ? head->val - 1 : size;
			while (s == c1->val || s == c2->val || s == c3->val)
				s = (s - 1 > 0) ? s - 1 : size;
			cup *t = cups->at(s), *temp = t->next, *temp2 = c3->next;
			c3->next = temp, t->next = c1;
			head->next = temp2, head = head->next;
		}
	}
	cup* circular_linked_list(int* v, int v_len, int size,
							  unordered_map<long, cup*>* cups)
	{
		(*cups)[v[0]] = (cup*)malloc(sizeof(cup));
		(*cups)[v[0]]->next = NULL;
		(*cups)[v[0]]->val = v[0];
		cup* c = (*cups)[v[0]];
		for (int i = 1; i < size; i++) {
			int x = (i < v_len) ? v[i] : (i + 1);
			(*cups)[x] = (cup*)malloc(sizeof(cup));
			(*cups)[x]->val = x;
			(*cups)[x]->next = NULL;
			c->next = (*cups)[x];
			c = (*cups)[x];
		}
		c->next = (*cups)[v[0]];
		return (*cups)[v[0]];
	}
	void free_list(cup* head)
	{
		cup* x = head->next;
		head->next = NULL;
		while (x != NULL) {
			cup* y = x;
			x = y->next;
			free(y);
		}
	}
	int get_cup_values(line* ln, int** vals)
	{
		int l = strlen(ln->content);
		*vals = (int*)malloc(l * sizeof(int));
		for (int i = 0; i < l; i++) (*vals)[i] = ln->content[i] - '0';
		return l;
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day23\n";
		clock_t begin = clock();
		int* vals;
		int vals_len = get_cup_values(first, &vals);
		cout << "  Part one: " << part_one(vals, vals_len) << endl;
		cout << "  Part two: " << part_two(vals, vals_len) << endl;
		free(vals);
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		cout << "  time spent: " << time_spent << 's' << endl;
	}
};
#ifndef MAIN
int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Missing input file name!";
		return 1;
	}
	Day23 x = Day23();
	x.print_results(argv[1]);
	return 0;
}
#endif
