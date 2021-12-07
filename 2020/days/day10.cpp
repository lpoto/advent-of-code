#include "../utils.h"
#include <unordered_map>

class Day10 {
    int part_one(line* ln, int ones, int threes, int prev)
    {
        if (ln == NULL) return ones * (threes + 1);
        int x = stoi(ln->content);
        if (x - prev == 1)
            ones++;
        else if (x - prev == 3)
            threes++;
        return part_one(ln->next, ones, threes, x);
    }

    long long part_two(line* ln, unordered_map<int, long>* memo, int idx)
    {
        if (ln == NULL) return 1;
        if ((*memo).count(idx) > 0) return (*memo).at(idx);
        line* l = (idx == 0) ? ln : ln->next;
        int x = (idx == 0) ? 0 : stoi(ln->content);
        int i2 = idx, prev = x;
        (*memo)[idx] = 0;
        while (1) {
            int y = (l == NULL) ? prev + 3 : stoi(l->content);
            (*memo)[idx] += (y - x <= 3) ? part_two(l, memo, ++i2) : 0;
            if (y - x > 3 || l == NULL) break;
            prev = y;
            l = l->next;
        }
        return (*memo)[idx];
    }

  public:
    Results* results(line* first)
    {
        unordered_map<int, long> memo;
        return new_results(to_string(part_one(first, 0, 0, 0)),
                           to_string(part_two(first, &memo, 0)));
    }
};
