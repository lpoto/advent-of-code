from advent_day import AdventDay
import heapq


class Day15(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            m = f.read().splitlines()
            self.H, self.W = len(m), len(m[0])
            self.input = {(i, j): int(m[i][j])
                          for i in range(self.H) for j in range(self.W)}

    def expand_input(self):
        expanded = dict()
        for x in range(5 * self.H):
            for y in range(5 * self.H):
                n = self.input.get((x % self.H, y % self.W))
                for i in range(x // self.H + y // self.W):
                    n = 1 if n == 9 else n + 1
                expanded[x, y] = n
        return expanded

    def find_low_risk_path(self, expand=False):
        input = self.input if not expand else self.expand_input()
        dp = [(0, 0, 0)]
        costs = {}
        while True:
            cost, x, y = heapq.heappop(dp)
            if (x + 1) * (y + 1) == len(input):
                return cost
            for nbr in {(x + 1, y), (x - 1, y), (x, y - 1), (x, y + 1)}:
                if nbr not in input:
                    continue
                new_cost = cost + input.get(nbr)
                if nbr in costs and costs[nbr] <= new_cost:
                    continue
                costs[nbr] = new_cost
                heapq.heappush(dp, (new_cost, *nbr))

    def results(self):
        return tuple(self.find_low_risk_path(i == 1) for i in range(2))
