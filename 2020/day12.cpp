#include "../utils.h"
#define abs(x) ((x >= 0) ? x : -x)

class Day12 {
	int part_one(line* ln)
	{
		int waypoint[2] = {0, 1}, coords[2] = {0, 0};
		return move_ship(ln, coords, waypoint, 1);
	}
	int part_two(line* ln)
	{
		int waypoint[2] = {1, 10}, coords[2] = {0, 0};
		return move_ship(ln, coords, waypoint, 2);
	}
	int move_ship(line* ln, int* coords, int* wp, int part)
	{
		if (ln == NULL) return abs(coords[0]) + abs(coords[1]);
		char next_d = ln->content[0];
		int count = stoi(((string)ln->content).substr(1));
		if (next_d == 'R' || next_d == 'L')
			rotate_waypoint(wp, next_d, count / 90);
		else if (next_d == 'F')
			coords[0] += count * wp[0], coords[1] += count * wp[1];
		else {
			int wp2[2] = {
				(next_d == 'N') ? 1 : (next_d == 'S' ? -1 : 0),
				(next_d == 'E') ? 1 : (next_d == 'W' ? -1 : 0),
			};
			if (part == 2)
				wp[0] += count * wp2[0], wp[1] += count * wp2[1];
			else
				coords[0] += count * wp2[0], coords[1] += count * wp2[1];
		}
		return move_ship(ln->next, coords, wp, part);
	}
	void rotate_waypoint(int* waypoint, int direction, int count)
	{
		int x;
		for (int i = 0; i < count; i++)
			if (direction == 'R')
				x = waypoint[0], waypoint[0] = -waypoint[1], waypoint[1] = x;
			else if (direction == 'L')
				x = waypoint[0], waypoint[0] = waypoint[1], waypoint[1] = -x;
	}
  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day12\n";
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
	Day12 x = Day12();
	x.print_results(argv[1]);
	return 0;
}
#endif
