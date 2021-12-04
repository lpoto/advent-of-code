#include "../utils.h"
#include <unordered_map>
#define MAX_BITS 36

class Day14 {
	long part_one(line* ln) { return run_bitmask_program(ln, 1); }
	long part_two(line* ln) { return run_bitmask_program(ln, 2); }
	long run_bitmask_program(line* ln, long part)
	{
		unordered_map<long, long> mem;
		string mask = string(MAX_BITS, 'X');
		string x = string(MAX_BITS, '0');
		run_instructions(ln, &mem, mask, part);
		long sum = 0;
		for (auto& it : mem) sum += it.second;
		return sum;
	}
	void run_instructions(line* ln, unordered_map<long, long>* mem, string mask,
						  int part)
	{
		if (ln == NULL) return;
		if (ln->content[1] == 'a')
			mask = ((string)ln->content).substr(7);
		else {
			string s = ln->content;
			long mem_idx = stoi(s.substr(4, s.find("]") - 3));
			long num = stoi(s.substr(s.find("=") + 2));
			if (part == 1) {
				string num_bin = apply_mask(dec_to_bin(num), mask, 0);
				(*mem)[mem_idx] = bin_to_dec(num_bin);
			} else if (part == 2) {
				string mem_idx_bin = apply_mask(dec_to_bin(mem_idx), mask, 1);
				multiple_val_mem(mem, mem_idx_bin, num);
			}
		}
		run_instructions(ln->next, mem, mask, part);
	}
	void multiple_val_mem(unordered_map<long, long>* mem, string mem_idx,
						  long num)
	{
		int idx = mem_idx.find('X');
		if (idx == -1)
			(*mem)[bin_to_dec(mem_idx)] = num;
		else {
			mem_idx[idx] = '0', multiple_val_mem(mem, mem_idx, num);
			mem_idx[idx] = '1', multiple_val_mem(mem, mem_idx, num);
		}
	}
	string dec_to_bin(long x)
	{
		string bin_x = string(MAX_BITS, '0');
		for (unsigned int i = 0; x > 0; i++) {
			bin_x[MAX_BITS - i - 1] = (x % 2) + '0';
			x /= 2;
		}
		return bin_x;
	}
	string apply_mask(string number, string mask, int apply_x)
	{
		for (unsigned int i = 0; i < MAX_BITS; i++) {
			if ((mask[i] == 'X' && !apply_x) || (mask[i] == '0' && apply_x))
				continue;
			number[i] = mask[i];
		}
		return number;
	}
	long bin_to_dec(string bin_x)
	{
		long x = 0;
		for (int i = 0; i < MAX_BITS; i++)
			if (bin_x[i] == '1') x += pow(2, MAX_BITS - (i + 1));
		return x;
	}
	long pow(long x, int r) { return (r == 0) ? 1 : x * pow(x, r - 1); }

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day14\n";
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
	Day14 x = Day14();
	x.print_results(argv[1]);
	return 0;
}
#endif
