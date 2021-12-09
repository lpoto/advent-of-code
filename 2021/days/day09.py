from advent_day import AdventDay


class Day09(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.input = tuple(tuple(map(int, k))
                               for k in f.read().splitlines())

    def results(self):
        return tuple(self.find_low_points(i == 1) for i in range(2))

    def neighbours(self, i, j, matrix):
        return {(m, n) for m, n in
                {(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)}
                if (0 <= m < (len(matrix))) and (0 <= n < (len(matrix)))}

    def basin(self, i, j, memo):
        for k, l in self.neighbours(i, j, self.input):
            if ((k, l) in memo or self.input[k][l] == 9 or
                    self.input[k][l] <= self.input[i][j]):
                continue
            memo.add((k, l))
            self.basin(k, l, memo)

    def find_low_points(self, basin_size=False):
        s = []
        for i in range(len(self.input)):
            for j in range(len(self.input[0])):
                if all(self.input[m][n] > self.input[i][j]
                       for m, n in self.neighbours(i, j, self.input)):
                    if basin_size:
                        memo = {(i, j)}
                        self.basin(i, j, memo)
                        s.append(len(memo))
                    else:
                        s.append(self.input[i][j] + 1)
        if basin_size:
            s = sorted(s, reverse=True)[:3]
            return s[0] * s[1] * s[2]
        return sum(s)
