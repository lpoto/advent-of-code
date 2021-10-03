#include "../utils.h"
#include <algorithm>
#include <sstream>

class Day13 {
	int part_one(line* ln)
	{
		int earliest = stoi(ln->content);
		stringstream ss = stringstream(ln->next->content);
		string token;
		int earliest_bus_time = 0, earliest_bus_id = 0;
		while (getline(ss, token, ',')) {
			if (token == "x") continue;
			int bus = stoi(token);
			if (earliest % bus == 0) return bus;
			int bus_time = earliest - (earliest % bus) + bus;
			if (earliest_bus_time == 0 || bus_time < earliest_bus_time)
				earliest_bus_time = bus_time, earliest_bus_id = bus;
		}
		return earliest_bus_id * (earliest_bus_time - earliest);
	}
	long part_two(line* ln)
	{
		string s = ln->next->content;
		int x = count(s.begin(), s.end(), ',') + 2;
		int* busses = (int*)malloc(x * sizeof(int));
		busses[x - 1] = -1;
		stringstream ss = stringstream(s);
		string token;
		int i = 0;
		while (getline(ss, token, ','))
			busses[i++] = (token == "x") ? 0 : stoi(token);
		long time = find_time(busses, 0, 0, 1);
		free(busses);
		return time;
	}
	long find_time(int* bus, long time, int idx, long x)
	{
		if (*bus == -1) return time;
		if (*bus == 0) return find_time(bus + 1, time, ++idx, x);
		while ((time + idx) % *bus != 0) time += x;
		return find_time(bus + 1, time, ++idx, (x * (*bus)));
	}

  public:
	void print_results(char* file_name)
	{
		line* first = read_lines(file_name);
		cout << "Day13\n";
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
	Day13 x = Day13();
	x.print_results(argv[1]);
	return 0;
}
#endif
