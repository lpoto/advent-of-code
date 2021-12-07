#include "../utils.h"
#include <unordered_map>

class Day05 {
    int part_one(line* ln, int prev_id, unordered_map<int, int>* seats)
    {
        if (ln == NULL) return prev_id;
        int min = 0, max = 127;
        for (unsigned int i = 0; i < 7; i++) {
            if (ln->content[i] == 'F')
                max = min + (max - min) / 2;
            else if (ln->content[i] == 'B')
                min = min + (max - min) / 2 + 1;
        }
        int id = min * 8;
        min = 0;
        max = 7;
        for (unsigned int i = 7; i < 10; i++) {
            if (ln->content[i] == 'L')
                max = min + (max - min) / 2;
            else if (ln->content[i] == 'R')
                min = min + (max - min) / 2 + 1;
        }
        id += min;
        (*seats)[id] = 1;
        return part_one(ln->next, id > prev_id ? id : prev_id, seats);
    }
    int part_two(unordered_map<int, int>* seats)
    {
        for (auto& it : *seats) {
            if ((*seats).count(it.first + 1) == 0 &&
                (*seats).count(it.first + 2) > 0)
                return it.first + 1;
        }
        return 0;
    }

  public:
    Results* results(line* first)
    {
        unordered_map<int, int> seats;
        return new_results(to_string(part_one(first, 0, &seats)),
                           to_string(part_two(&seats)));
    }
};
