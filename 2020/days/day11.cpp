#include "../utils.h"
#include <string.h>

class Day11 {
    int part_one(line* ln)
    {
        int changed = 1, count = 0, max = strlen(ln->content) - 1;
        while (changed)
            changed = 0, count = round_of_moving(ln, &changed, max, 1);
        return count;
    }
    int part_two(line* ln)
    {
        int changed = 1, count = 0, max = strlen(ln->content) - 1;
        while (changed)
            changed = 0, count = round_of_moving(ln, &changed, max, 2);
        return count;
    }
    int round_of_moving(line* ln, int* changed, int max, int part)
    {
        if (ln == NULL) return 0;
        int count = 0, occupied_to_change = (part == 1) ? 4 : 5;
        char* change = (char*)malloc((max + 2) * sizeof(char));
        for (int i = 0; i <= max; i++)
            if (ln->content[i] == '.') {
                change[i] = '.';
            } else if (ln->content[i] == 'L') {
                if (occupied_adj(ln, i, max, part) == 0)
                    change[i] = '#', (*changed) = 1, count++;
                else
                    change[i] = 'L';
            } else if (ln->content[i] == '#') {
                if (occupied_adj(ln, i, max, part) >= occupied_to_change)
                    change[i] = 'L', (*changed) = 1;
                else
                    change[i] = '#', count++;
            }
        count += round_of_moving(ln->next, changed, max, part);
        change[max + 1] = '\0';
        strcpy(ln->content, change);
        free(change);
        return count;
    }
    int occupied_adj(line* ln, int idx, int max, int part)
    {
        int count = 0;
        for (int i = 0; i < 8; i++) count += in_sight(ln, idx, i, max, 0, part);
        return count;
    }
    int in_sight(line* ln, int idx, int dir, int max, int changed, int part)
    {
        if (ln == NULL ||
            (changed && (idx < 0 || idx > max || ln->content[idx] == 'L')))
            return 0;
        if (changed && ln->content[idx] == '#') return 1;
        if (changed && part == 1 && ln->content[idx] == '.') return 0;
        if (dir < 3)
            idx++;
        else if (dir > 4)
            idx--;
        if (dir < 7 && dir % 2 != 0)
            ln = ln->next;
        else if (dir > 0 && dir % 2 == 0)
            ln = ln->prev;
        return in_sight(ln, idx, dir, max, 1, part);
    }

  public:
    Results* results(line* first)
    {
        line* copy = copy_lines(first);
        int p1 = part_one(first);
        int p2 = part_two(copy);
        clean_lines(copy);
        return new_results(to_string(p1), to_string(p2));
    }
};
