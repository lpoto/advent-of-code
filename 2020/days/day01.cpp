#include "../utils.h"
#include <unordered_map>
#define SUM 2020

class Day01 {
    int part_one(line* ln)
    {
        unordered_map<int, int> sums;
        while (ln != NULL) {
            int x = stoi(ln->content);
            if (sums.count(SUM - x) > 0) return (SUM - x) * x;
            sums[x] = 1;
            ln = ln->next;
        }
        return 0;
    }
    int part_two(line* ln)
    {
        while (ln != NULL) {
            line* ln2 = ln;
            int x = stoi(ln->content);
            unordered_map<int, int> sums;
            while (ln2 != NULL) {
                int y = stoi(ln2->content);
                if (sums.count(SUM - x - y) > 0) return (SUM - x - y) * x * y;
                sums[y] = 1;
                ln2 = ln2->next;
            }
            ln = ln->next;
        }
        return 0;
    }

  public:
    Results* results(line* first)
    {
        return new_results(to_string(part_one(first)),
                           to_string(part_two(first)));
    }
};
