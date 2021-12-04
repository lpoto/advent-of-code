#define MAIN
#include "days/day01.cpp"
#include "days/day02.cpp"
#include "days/day03.cpp"
#include "days/day04.cpp"
#include "days/day05.cpp"
#include "days/day06.cpp"
#include "days/day07.cpp"
#include "days/day08.cpp"
#include "days/day09.cpp"
#include "days/day10.cpp"
#include "days/day11.cpp"
#include "days/day12.cpp"
#include "days/day13.cpp"
#include "days/day14.cpp"
#include "days/day15.cpp"
#include "days/day16.cpp"
#include "days/day17.cpp"
#include "days/day18.cpp"
#include "days/day19.cpp"
#include "days/day20.cpp"
#include "days/day21.cpp"
#include "days/day22.cpp"
#include "days/day23.cpp"
#include "days/day24.cpp"
#include "days/day25.cpp"
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
