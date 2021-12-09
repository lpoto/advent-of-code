from advent_day import AdventDay


class Day05(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.coordinates = tuple(tuple(
                tuple(int(i) for i in line.split('->')[k].split(','))
                for k in range(2)) for line in f.readlines())

    def results(self):

        return tuple(self.find_overlaps(i == 1) for i in range(2))

    def find_overlaps(self, diagonal=True):
        overlaps = {}
        for c in self.coordinates:
            if not diagonal and c[0][0] != c[1][0] and c[0][1] != c[1][1]:
                continue
            x1, y1, x2, y2 = c[0][0], c[0][1], c[1][0], c[1][1]
            for i in ((x1 + (i if x1 < x2 else (-i if x1 > x2 else 0)),
                       y1 + (i if y1 < y2 else (-i if y1 > y2 else 0)),
                       ) for i in range(max(abs(x1 - x2), abs(y1 - y2)) + 1)):
                overlaps[i] = overlaps.setdefault(i, 0) + 1
        return sum(1 for i in overlaps.values() if i > 1)
