#include "../utils.h"
#include <array>
#include <string.h>
#define CYCLES 6

class Day17 {
    int part_one(set<array<int, 4>> coords)
    {
        for (int i = 0; i < CYCLES; i++) coords = cycle(coords, 3);
        return coords.size();
    }
    int part_two(set<array<int, 4>> coords)
    {
        for (int i = 0; i < CYCLES; i++) coords = cycle(coords, 4);
        return coords.size();
    }
    set<array<int, 4>> cycle(set<array<int, 4>> coords, int d)
    {
        set<array<int, 4>> new_coords;
        set<array<int, 4>> memo;
        for (array<int, 4> it : coords)
            edit_cube_state(&coords, &new_coords, &memo, &it, 1, d);
        return new_coords;
    }
    void edit_cube_state(set<array<int, 4>>* old_c, set<array<int, 4>>* new_c,
                         set<array<int, 4>>* memo, array<int, 4>* c,
                         int check_nbrs, int dim)
    {
        if (memo->count(*c) > 0) return;
        int cur_state = old_c->count(*c) > 0;
        memo->insert(*c);
        int active_nbrs =
            neighbours(old_c, new_c, memo, c, check_nbrs, dim, dim);
        active_nbrs -= cur_state;
        if ((cur_state == 0 && active_nbrs == 3) ||
            (cur_state == 1 && (active_nbrs == 2 || active_nbrs == 3)))
            new_c->insert(*c);
    }
    int neighbours(set<array<int, 4>>* old_c, set<array<int, 4>>* new_c,
                   set<array<int, 4>>* memo, array<int, 4>* c, int check,
                   int dim, int tot_dim)
    {
        if (dim == 0) {
            int k = (old_c->count(*c) > 0);
            if (check && !k) edit_cube_state(old_c, new_c, memo, c, 0, tot_dim);
            return k;
        };
        int r = 0;
        for (int i = -1; i < 2; i++) {
            array<int, 4> c2 = *c;
            c2[4 - dim] += i;
            r += neighbours(old_c, new_c, memo, &c2, check, dim - 1, tot_dim);
        }
        return r;
    }
    set<array<int, 4>> starting_active_coordinates(line* ln)
    {
        int len = strlen(ln->content);
        int z = CYCLES, y = z, x = y, w = x;
        set<array<int, 4>> coords;
        while (ln != NULL) {
            for (int i = 0; i < len; i++) {
                if (ln->content[i] == '.') continue;
                array<int, 4> c = {w, z, y, i + x};
                coords.insert(c);
            }
            y++;
            ln = ln->next;
        }
        return coords;
    }

  public:
    Results* results(line* first)
    {
        set<array<int, 4>> coords = starting_active_coordinates(first);
        return new_results(to_string(part_one(coords)),
                           to_string(part_two(coords)));
    }
};
