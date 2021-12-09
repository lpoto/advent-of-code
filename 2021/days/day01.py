from advent_day import AdventDay


class Day01(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.measurements = tuple(map(int, f.readlines()))

    def results(self):
        return tuple(self.count_larger_measurements(i) for i in (1, 3))

    def count_larger_measurements(self, n):
        return sum(1 for i in range(n, len(self.measurements))
                   if self.measurements[i] > self.measurements[i - n])
