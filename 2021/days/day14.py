from advent_day import AdventDay
from collections import Counter


class Day14(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.template, self.rules = f.read().split('\n\n')
            self.rules = {k: v for k, v in (
                x.split(' -> ') for x in self.rules.strip().split('\n'))}

    def results(self):
        return tuple(self.step(i) for i in (10, 40))

    def step(self, steps):
        pair_counter = Counter(
            (self.template[i: i + 2] for i in range(len(self.template) - 1)))
        for _ in range(steps):
            temp_pair_counter = Counter()
            for k, v in pair_counter.items():
                temp_pair_counter[k[0] + self.rules[k]] += v
                temp_pair_counter[self.rules[k] + k[1]] += v
            pair_counter = temp_pair_counter
        singles_counter = Counter((self.template[0]))
        for k, v in pair_counter.items():
            singles_counter[k[1]] += v
        return max(singles_counter.values()) - min(singles_counter.values())
