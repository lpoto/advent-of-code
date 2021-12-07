from advent_day import AdventDay


class Day06(AdventDay):
    def __init__(self, filename):
        self.timers = tuple(map(int, self.read_input(filename)[0].split(',')))

    def results(self):
        return tuple(self.count_fishes(d) for d in (80, 256))

    def count_fishes(self, days):
        t = list(map(self.timers.count, range(9)))
        for _ in range(days):
            t.extend((t.pop(7) + t[0], t.pop(7), t.pop(0)))
        return sum(t)
