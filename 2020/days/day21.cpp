#include "../utils.h"
#include <map>
#include <sstream>

class Day21 {
    int part_one(map<string, int>* ingredient_count,
                 map<string, unordered_set<string>>* ingredients)
    {
        int c = 0;
        for (auto& it : *ingredients) {
            if (it.second.size() == 0) c += ingredient_count->at(it.first);
        }
        return c;
    }
    string part_two(map<string, vector<unordered_set<string>>>* alergens)
    {
        string s;
        for (auto& it : *alergens) {
            for (const unordered_set<string>& it2 : it.second) {
                s.append(*it2.begin());
                s.append(",");
            }
        }
        s.pop_back();
        return s;
    }
    int trim_extracted_unordered_sets(
        map<string, unordered_set<string>>* ingredients,
        map<string, vector<unordered_set<string>>>* alergens)
    {
        int c = 0;
        for (auto& it : *alergens) {
            if (it.second.size() == 1) {
                const unordered_set<string>& s = *it.second.begin();
                if (s.size() > 1) {
                    c = 1;
                    continue;
                }
                const string& i = *s.begin();
                for (auto& it2 : *ingredients) {
                    if (it2.first == i)
                        it2.second.clear(), it2.second.insert(it.first);
                    else
                        it2.second.erase(it.first);
                }
                for (auto& it2 : *alergens) {
                    if (it2 == it) continue;
                    for (unordered_set<string>& it3 : it2.second) {
                        it3.erase(i);
                        if (it3.size() == 1) {
                            for (vector<unordered_set<string>>::iterator k =
                                     it2.second.begin();
                                 k != it2.second.end();)
                                k = (k->size() == 1) ? (next(k))
                                                     : it2.second.erase(k);
                        } else
                            c = 1;
                    }
                }
            }
        }
        return c;
    }
    void
    extract_ingredients(line* ln,
                        map<string, unordered_set<string>>* ingredients,
                        map<string, int>* ingredients_count,
                        map<string, vector<unordered_set<string>>>* alergens)
    {
        if (ln == NULL) return;
        string s = ln->content;
        int alergens_idx = s.find("(");
        string s1 = s.substr(0, alergens_idx - 1);
        string s2 = s.substr(alergens_idx + 10, s.size() - alergens_idx - 11);
        stringstream ss1 = stringstream(s1), ss2 = stringstream(s2);
        string token1, token2;
        unordered_set<string> alg, ing;
        while (getline(ss2, token2, ' ')) {
            if (token2.back() == ',') token2.pop_back();
            alg.insert(token2);
        }
        while (getline(ss1, token1, ' ')) {
            if (ingredients_count->count(token1) == 0)
                (*ingredients_count)[token1] = 0, (*ingredients)[token1];
            (*ingredients_count)[token1]++;
            for (const string& it : alg) (*ingredients)[token1].insert(it);
            ing.insert(token1);
        }
        for (const string& it : alg) {
            if (alergens->count(it) == 0) (*alergens)[it];
            unordered_set<string> ing2;
            for (const string& i : ing) {
                int found = 1;
                for (const unordered_set<string>& s : alergens->at(it)) {
                    unordered_set<string>::const_iterator x = s.find(i);
                    if (x == s.end()) {
                        found = 0;
                        break;
                    }
                }
                if (found) ing2.insert(i);
            }
            if (ing2.size() == 1) (*alergens)[it].clear();
            (*alergens)[it].push_back(ing2);
        }
        extract_ingredients(ln->next, ingredients, ingredients_count, alergens);
    }

  public:
    Results* results(line* first)
    {
        map<string, unordered_set<string>> ingredients;
        map<string, int> ingredients_count;
        map<string, vector<unordered_set<string>>> alergens;
        extract_ingredients(first, &ingredients, &ingredients_count, &alergens);
        while (trim_extracted_unordered_sets(&ingredients, &alergens))
            ;
        return new_results(
            to_string(part_one(&ingredients_count, &ingredients)),
            part_two(&alergens));
    }
};
