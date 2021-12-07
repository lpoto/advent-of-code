#include "../utils.h"
#include <unordered_map>

class Day16 {
    int
    part_one(unordered_map<int, int*>* tickets,
             unordered_map<string, int[2][2]>* restrictions,
             unordered_map<int, unordered_map<int, unordered_map<string, int>>>*
                 pot_fields,
             int c)
    {
        int sum = 0;
        unordered_map<int, int*>::const_iterator it = tickets->begin();
        while (it != tickets->end()) {
            int v = 1;
            for (int i = 0; i < c; i++) {
                int v2 = 0;
                for (auto& it2 : *restrictions)
                    if (ticket_position_in_field(it->second[i], it2.second)) {
                        v2 = 1;
                        (*pot_fields)[it->first][i][it2.first] = 1;
                    } else {
                        (*pot_fields)[it->first][i][it2.first] = 0;
                    }
                if (v2 == 0 && it->first != 0) {
                    sum += it->second[i];
                    v = 0;
                    break;
                }
            }
            it = (v == 0) ? tickets->erase(it) : ++it;
        }
        return sum;
    }
    long
    part_two(unordered_map<int, int*>* tickets,
             unordered_map<string, int[2][2]>* restrictions,
             unordered_map<int, unordered_map<int, unordered_map<string, int>>>*
                 pot_fields,
             int c)
    {
        unordered_map<int, vector<string>> fields;
        for (auto& it : *restrictions)
            for (int i = 1; i < c; i++) {
                int v = 1;
                for (auto& it2 : *tickets)
                    if ((*pot_fields)[it2.first][i][it.first] == 0) {
                        v = 0;
                        for (auto& it3 : *tickets)
                            (*pot_fields)[it3.first][i][it.first] = 0;
                        break;
                    }
                if (v == 1) fields[i].push_back(it.first);
            }
        for (int k = 0; k < (int)(*restrictions).size(); k++)
            for (auto& i : fields)
                if (i.second.size() <= 1)
                    for (auto& i2 : fields)
                        if (i2.first != i.first) {
                            auto bg = i2.second.begin();
                            auto end = i2.second.end();
                            i2.second.erase(remove(bg, end, i.second[0]), end);
                        }
        long r = 1;
        for (auto& it : fields)
            if (it.second[0].substr(0, it.second[0].find(" ")) == "departure")
                r *= (*tickets)[0][it.first];
        return r;
    }
    int ticket_position_in_field(int t_p, int field[2][2])
    {
        return ((t_p >= field[0][0] && t_p <= field[0][1]) ||
                (t_p >= field[1][0] && t_p <= field[1][1]));
    }
    line* extract_restrictions(line* ln, unordered_map<string, int[2][2]>* rest)
    {
        if (ln->content[0] == '\n') return ln->next;
        string s = ln->content;
        string key = s.substr(0, s.find(":"));
        int x = s.find(":"), y = s.find(" or");
        string s1 = s.substr(x + 2, y - (x + 2)), s2 = s.substr(y + 4);
        (*rest)[key];
        (*rest)[key][0][0] = stoi(s1.substr(0, s1.find("-")));
        (*rest)[key][0][1] = stoi(s1.substr(s1.find("-") + 1));
        (*rest)[key][1][0] = stoi(s2.substr(0, s2.find("-")));
        (*rest)[key][1][1] = stoi(s2.substr(s2.find("-") + 1));
        return extract_restrictions(ln->next, rest);
    }
    void extract_tickets(line* ln, unordered_map<int, int*>* t, int idx, int c)
    {
        if (ln == NULL || idx == 0) return;
        string s = ln->content;
        stringstream ss = stringstream(s);
        string token;
        int* x = (int*)malloc(c * sizeof(int));
        for (int i = 0; i < c; i++) {
            getline(ss, token, ',');
            x[i] = stoi(token);
        }
        (*t)[idx == -1 ? 0 : idx] = x;
        extract_tickets(ln->next, t, idx + 1, c);
    }

  public:
    Results* results(line* first)
    {
        unordered_map<string, int[2][2]> restrictions;
        first = extract_restrictions(first, &restrictions)->next;
        string s = first->content;
        int c = count(s.begin(), s.end(), ',') + 1;
        unordered_map<int, int*> tickets;
        unordered_map<int, unordered_map<int, unordered_map<string, int>>>
            pot_fields;
        extract_tickets(first, &tickets, -1, c);
        extract_tickets(first->next->next->next, &tickets, 1, c);
        long p1 = part_one(&tickets, &restrictions, &pot_fields, c);
        long p2 = part_two(&tickets, &restrictions, &pot_fields, c);
        for (auto& it : tickets) free(it.second);
        return new_results(to_string(p1), to_string(p2));
    }
};
