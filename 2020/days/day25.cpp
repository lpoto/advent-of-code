#include "../utils.h"

class Day25 {
    long part_one(int c_public, int d_public)
    {
        int i = 0, val = 1, divisor = 20201227;
        while (val != c_public && val != d_public)
            val = transform_subject_number(7, 1, divisor, val), i++;
        if (val == c_public)
            return transform_subject_number(d_public, i, divisor, 1);
        return transform_subject_number(c_public, i, divisor, 1);
    }
    long transform_subject_number(int subject_number, int loop_size,
                                  int divisor, long val)
    {
        for (int i = 0; i < loop_size; i++)
            val = (val * subject_number) % divisor;
        return val;
    }

  public:
    Results* results(line* first)
    {
        int c_public = stoi(first->content);
        int d_public = stoi(first->next->content);
        return new_results(to_string(part_one(c_public, d_public)),
                           "--- end ---");
    }
};
