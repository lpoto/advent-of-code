#include "utils.h"
#define MAIN
#include <iomanip>
#include <string.h>
#include <string>
#include <unistd.h>
#include "days/day01.cpp"
#define INPUT_FILE "/inputs/dayXX.txt"

void print_day(int d, char* inp, int inp_len);
void print_all_days(char* inp, int inp_len);
int get_day_idx(int argc, char** argv);

int main(int argc, char** argv)
{
    // cout << "--- Advent of code 2020 --- " << endl;
    get_day_idx(argc, argv);
    char inp[256] = __FILE__, f[] = INPUT_FILE;
    int x = strlen(inp) - 8;
    strcpy(&(inp[x]), f);
    x += (strlen(INPUT_FILE) - 6);
    int d = get_day_idx(argc, argv);
    if (d != -1)
        print_day(d, inp, x);
    else
        print_all_days(inp, x);
    return 0;
}
line* get_input(int i, char* input, int s_len)
{
    if (i < 10)
        input[s_len] = '0';
    else
        input[s_len] = i / 10 + '0';
    input[s_len + 1] = i % 10 + '0';
    return read_lines(input);
}

int get_day_idx(int argc, char** argv)
{
    if (argc < 2) return -1;
    string s = argv[1];
    if (s.substr(0, 3) == "day") s = s.substr(3);
    try {
        int idx = stoi(s);
        if (idx > 0 && idx <= 25) return idx;
    } catch (exception&) {
        return -1;
    }
    return -1;
}
void print_results(Results* results, int day)
{
    cout << "Day" << setw(2) << setfill('0') << day << endl;
    clock_t begin = clock();
    cout << "  Part one: " << results->p1 << endl;
    cout << "  Part two: " << results->p2 << endl;
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "  time spent: " << time_spent << 's' << endl;
    free(results);
}

void print_day(int d, char* inp, int inp_len)
{
    line* ln = get_input(d, inp, inp_len);
    switch (d) {
    case 1:
#include "days/day01.cpp"
        print_results(Day01().results(ln), d);
        break;
    case 2:
#include "days/day02.cpp"
        print_results(Day02().results(ln), d);
        break;
    case 3:
#include "days/day03.cpp"
        print_results(Day03().results(ln), d);
        break;
    case 4:
#include "days/day04.cpp"
        print_results(Day04().results(ln), d);
        break;
    case 5:
#include "days/day05.cpp"
        print_results(Day05().results(ln), d);
        break;
    case 6:
#include "days/day06.cpp"
        print_results(Day06().results(ln), d);
        break;
    case 7:
#include "days/day07.cpp"
        print_results(Day07().results(ln), d);
        break;
    case 8:
#include "days/day08.cpp"
        print_results(Day08().results(ln), d);
        break;
    case 9:
#include "days/day09.cpp"
        print_results(Day09().results(ln), d);
        break;
    case 10:
#include "days/day10.cpp"
        print_results(Day10().results(ln), d);
        break;
    case 11:
#include "days/day11.cpp"
        print_results(Day11().results(ln), d);
        break;
    case 12:
#include "days/day12.cpp"
        print_results(Day12().results(ln), d);
        break;
    case 13:
#include "days/day13.cpp"
        print_results(Day13().results(ln), d);
        break;
    case 14:
#include "days/day14.cpp"
        print_results(Day14().results(ln), d);
        break;
    case 15:
#include "days/day15.cpp"
        print_results(Day15().results(ln), d);
        break;
    case 16:
#include "days/day16.cpp"
        print_results(Day16().results(ln), d);
        break;
    case 17:
#include "days/day17.cpp"
        print_results(Day17().results(ln), d);
        break;
    case 18:
#include "days/day18.cpp"
        print_results(Day18().results(ln), d);
        break;
    /*case 19:
#include "days/day19.cpp"
        print_results(Day19().results(ln), d);
        break;
    case 20:
#include "days/day20.cpp"
        print_results(Day20().results(ln), d);
        break;*/
    case 21:
#include "days/day21.cpp"
        print_results(Day21().results(ln), d);
        break;
    case 22:
#include "days/day22.cpp"
        print_results(Day22().results(ln), d);
        break;
    case 23:
#include "days/day23.cpp"
        print_results(Day23().results(ln), d);
        break;
    case 24:
#include "days/day24.cpp"
        print_results(Day24().results(ln), d);
        break;
    case 25:
#include "days/day25.cpp"
        print_results(Day25().results(ln), d);
        break;
    }
    if (ln != NULL) clean_lines(ln);
}
void print_all_days(char* inp, int inp_len)
{
    cout << "--- Advent of code 2020 ---" << endl << endl;
    ;
    clock_t begin = clock();
    for (int i = 1; i <= 25; i++) {
        print_day(i, inp, inp_len);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Total time spent: " << time_spent << 's' << endl;
}
