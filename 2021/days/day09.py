from advent_day import AdventDay


class Day09(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            m = f.read().splitlines()
            self.matrix = {(i, j): int(m[i][j])
                           for i in range(len(m)) for j in range(len(m))}
            self.input = tuple(tuple(map(int, k))
                               for k in f.read().splitlines())

    def results(self):
        return tuple(self.find_low_points(i == 1) for i in range(2))

    def neighbours(self, i, j):
        return {(m, n) for m, n in
                {(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)}
                if (m, n) in self.matrix}

    def basin(self, k, memo):
        for nbr in self.neighbours(*k):
            if (nbr not in memo and self.matrix[nbr] != 9 and
                    self.matrix[nbr] > self.matrix[k]):
                memo.add(nbr)
                self.basin(nbr, memo)

    def find_low_points(self, basin_size=False):
        s = []
        for k, v in self.matrix.items():
            if all(self.matrix[n] > v for n in self.neighbours(*k)):
                if basin_size:
                    memo = {k}
                    self.basin(k, memo)
                    s.append(len(memo))
                else:
                    s.append(self.matrix[k] + 1)
        if basin_size:
            s = sorted(s, reverse=True)[:3]
            return s[0] * s[1] * s[2]
        return sum(s)
