from advent_day import AdventDay


class Day07(AdventDay):
    def __init__(self, filename):
        self.pos = tuple(
            map(int, self.read_input(filename, lines=False).split(',')))

    def results(self):
        return tuple(self.calculate_fuel_consumption(i == 0) for i in range(2))

    def calculate_fuel_consumption(self, constant=True):
        return min(sum(
            abs(k - i) if constant else (abs(k - i) * (abs(k - i) + 1) // 2)
            for k in self.pos) for i in range(min(self.pos), max(self.pos)))
