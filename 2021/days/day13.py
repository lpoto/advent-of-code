from advent_day import AdventDay


class Day13(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            i = f.read().strip().split('\n\n')
            self.dots = set((tuple(map(int, k.split(',')))
                             for k in i[0].split('\n')))
            self.folds = tuple((i, int(j)) for i, j in tuple(k.replace(
                'fold along ', '').split('=') for k in i[-1].split('\n')))

    def results(self):
        return (self.part_one(), self.part_two())

    def fold(self, d, x):
        d1 = set(filter(lambda i: i[(x[0] == 'y')] > x[1], d))
        d2 = set((i[0], x[1] - (i[1] - x[1])) if x[0] ==
                 'y' else (x[1] - (i[0] - x[1]), i[1]) for i in d1)
        return(d - d1 | d2)

    def part_one(self):
        return len(self.fold(self.dots, self.folds[0]))

    def part_two(self):
        d = self.dots
        for x in self.folds:
            d = self.fold(d, x)
        l1, l2 = max(i[1] for i in d) + 1, max(i[0] for i in d) + 1
        x = [[' ' for _ in range(max(l1, l2))] for _ in range(min(l1, l2))]
        for i in d:
            x[i[l1 < l2]][i[(l1 >= l2)]] = 'X'
        # print('\n'.join(''.join(i) for i in x)) # determine letters from this
        return 'too large to print'
