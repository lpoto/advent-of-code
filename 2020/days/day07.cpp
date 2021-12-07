#include "../utils.h"
#include <sstream>
#include <unordered_map>

class Day07 {
    int part_one(unordered_map<string, unordered_map<string, int>>* bags)
    {
        int x = 0;
        for (auto& it : *bags) x += check_gold(&(*bags)[it.first], bags);
        return x;
    }
    int part_two(unordered_map<string, int>* cur_bag,
                 unordered_map<string, unordered_map<string, int>>* bags)
    {
        int x = 0;
        for (auto& it : *cur_bag)
            x += it.second * (part_two(&(*bags)[it.first], bags) + 1);
        return x;
    }
    int check_gold(unordered_map<string, int>* cur_bag,
                   unordered_map<string, unordered_map<string, int>>* bags)
    {
        if ((*cur_bag).count("shiny gold") > 0) return 1;
        for (auto& it : *cur_bag) {
            if (check_gold(&(*bags)[it.first], bags)) return 1;
        }
        return 0;
    }
    void map_bags(line* ln,
                  unordered_map<string, unordered_map<string, int>>* bags)
    {
        if (ln == NULL) return;
        string s = ln->content;
        int x = s.find('.');
        if (x != -1) s.erase(x, 1);
        string bag = s.substr(0, s.find(" bags"));
        string contained = s.substr(s.find("bags ") + 13);
        stringstream ss = stringstream(contained);
        string token;
        (*bags)[bag];
        while (getline(ss, token, ',')) {
            if (token[0] == ' ') token.erase(0, 1);
            token = token.substr(0, token.find(" bag"));
            string n = token.substr(0, token.find(" "));
            if (n == "no") continue;
            string contained_bag = token.substr(token.find(' ') + 1);
            (*bags)[bag][contained_bag] = stoi(n);
        }
        map_bags(ln->next, bags);
    }

  public:
    Results* results(line* first)
    {
        unordered_map<string, unordered_map<string, int>> bags;
        map_bags(first, &bags);
        return new_results(
            to_string(part_one(&bags)),
            to_string(part_two(&(bags.at("shiny gold")), &bags)));
    }
};
