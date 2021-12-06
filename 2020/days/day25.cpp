#include "../utils.h"

class Day25 {
	long part_one(int c_public, int d_public)
	{
		int i = 0, val = 1, divisor = 20201227;
		while (val != c_public && val != d_public)
			val = transform_subject_number(7, 1, divisor, val), i++;
		if (val == c_public)
			return transform_subject_number(d_public, i, divisor, 1);
		return transform_subject_number(c_public, i, divisor, 1);
	}
	long transform_subject_number(int subject_number, int loop_size,
								  int divisor, long val)
	{
		for (int i = 0; i < loop_size; i++)
			val = (val * subject_number) % divisor;
		return val;
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day25\n";
		clock_t begin = clock();
		int c_public = stoi(first->content);
		int d_public = stoi(first->next->content);
		cout << "  Part one: " << part_one(c_public, d_public) << endl;
		cout << "  --- end ---" << endl;
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
	Day25 x = Day25();
	x.print_results(argv[1]);
	return 0;
}
#endif
