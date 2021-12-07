#include "../utils.h"

class Day02 {
    int part_one(line* ln)
    {
        if (ln == NULL) return 0;
        string s = ln->content;
        int x = s.find('-');
        int y = s.find(' ');
        int min = stoi(s.substr(0, x));
        int max = stoi(s.substr(x + 1, y - x));
        char letter = s[s.find(' ') + 1];
        string p = s.substr(s.find(": ") + 2);
        int c = count(p.begin(), p.end(), letter);
        return (c >= min && c <= max) + part_one(ln->next);
    }
    int part_two(line* ln)
    {
        if (ln == NULL) return 0;
        string s = ln->content;
        int x = s.find('-');
        int y = s.find(' ');
        int pos1 = stoi(s.substr(0, x)) - 1;
        int pos2 = stoi(s.substr(x + 1, y - x)) - 1;
        char letter = s[s.find(' ') + 1];
        string p = s.substr(s.find(": ") + 2);
        return ((p[pos1] == letter) ^ (p[pos2] == letter)) + part_two(ln->next);
    }

  public:
    Results* results(line* first)
    {
        return new_results(to_string(part_one(first)),
                           to_string(part_two(first)));
    }
};
