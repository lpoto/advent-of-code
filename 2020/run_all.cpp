#define MAIN
#include "day01.cpp"
#include "day02.cpp"
#include "day03.cpp"
#include "day04.cpp"
#include "day05.cpp"
#include "day06.cpp"
#include "day07.cpp"
#include "day08.cpp"
#include "day09.cpp"
#include "day10.cpp"
#include "day11.cpp"
#include "day12.cpp"
#include "day13.cpp"
#include "day14.cpp"
#include "day15.cpp"
#include "day16.cpp"
#include "day17.cpp"
#include "day18.cpp"
#include "day19.cpp"
#include "day20.cpp"
#include "day21.cpp"
#include "day22.cpp"
#include "day23.cpp"
#include "day24.cpp"
#include "day25.cpp"
#include <unistd.h>
#include <string.h>
#define INPUT_FILE "/inputs/dayXX.txt"

char* get_input(int i, char* input, int s_len) {
	if (i < 10) input[s_len] = '0';
	else input[s_len] = i / 10 + '0';
	input[s_len+1] = i % 10 + '0';
	return input;
}

int main(int argc, char** argv) {
	cout << "--- Advent of code 2020 --- "<< endl;
	char inp[256] = __FILE__, f[] = INPUT_FILE;
	int x = strlen(inp) - 11;
	strcpy(&(inp[x]), f); x+=(strlen(INPUT_FILE) - 6);
	clock_t begin = clock();
	Day01().print_results(get_input(1, inp, x));
	Day02().print_results(get_input(2, inp, x));
	Day03().print_results(get_input(3, inp, x));
	Day04().print_results(get_input(4, inp, x));
	Day05().print_results(get_input(5, inp, x));
	Day06().print_results(get_input(6, inp, x));
	Day07().print_results(get_input(7, inp, x));
	Day08().print_results(get_input(8, inp, x));
	Day09().print_results(get_input(9, inp, x));
	Day10().print_results(get_input(10, inp, x));
	Day11().print_results(get_input(11, inp, x));
	Day12().print_results(get_input(12, inp, x));
	Day13().print_results(get_input(13, inp, x));
	Day14().print_results(get_input(14, inp, x));
	Day15().print_results(get_input(15, inp, x));
	Day16().print_results(get_input(16, inp, x));
	Day17().print_results(get_input(17, inp, x));
	Day18().print_results(get_input(18, inp, x));
	Day19().print_results(get_input(19, inp, x));
	Day20().print_results(get_input(20, inp, x));
	Day21().print_results(get_input(21, inp, x));
	Day22().print_results(get_input(22, inp, x));
	Day23().print_results(get_input(23, inp, x));
	Day24().print_results(get_input(24, inp, x));
	Day25().print_results(get_input(25, inp, x));
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << endl << "Total time spent: " << time_spent << 's' << endl;
	return 0;
}
