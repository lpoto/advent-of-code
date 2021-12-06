from advent_day import AdventDay


class Day03(AdventDay):
    def __init__(self, filename):
        self.lines = self.read_input(filename)

    def results(self):
        return (self.part_one(), self.part_two())

    def part_one(self):
        lns = tuple(zip(*self.lines[::-1]))
        g_e = (int(''.join(str(i2 ^ int(i.count('1') >= len(self.lines) / 2))
                           for i in lns), 2) for i2 in range(2))
        return next(g_e) * next(g_e)

    def part_two(self):
        lns = [self.lines, self.lines]
        for i in range(len(self.lines[0])):
            if len(lns[0]) + len(lns[1]) == 2:
                break
            for i2 in range(2):
                if len(lns[i2]) > 1:
                    bit = i2 ^ (sum(int(ln[i])
                                for ln in lns[i2]) >= len(lns[i2]) / 2)
                    lns[i2] = list(filter(lambda a: int(a[i]) == bit, lns[i2]))
        return int(lns[1][0], 2) * int(lns[0][0], 2)
