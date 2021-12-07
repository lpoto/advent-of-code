#include "../utils.h"
#include <unordered_map>

class Day06 {
    int part_one(line* ln, int p_two)
    {
        unordered_map<char, int> answers;
        string s;
        int people = 0;
        while (1) {
            if (ln == NULL || ln->content[0] == '\n') break;
            s.append(ln->content);
            people++;
            ln = ln->next;
        }
        unsigned int s_size = s.size();
        int r = 0;
        for (unsigned int i = 0; i < s_size; i++) {
            int x = answers.count(s[i]);
            if (x == 0) {
                answers[s[i]] = 1;
                if (!p_two) r++;
            } else {
                answers[s[i]]++;
            }
            if (p_two && answers.at(s[i]) == people) r++;
        }
        return ln == NULL ? r : r + part_one(ln->next, p_two);
    }
    int part_two(line* ln) { return part_one(ln, 1); }

  public:
    Results* results(line* first)
    {
        return new_results(to_string(part_one(first, 0)),
                           to_string(part_two(first)));
    }
};
