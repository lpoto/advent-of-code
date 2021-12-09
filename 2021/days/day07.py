from advent_day import AdventDay
import numpy as np


class Day07(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.pos = np.array(list(map(int, f.read().split(','))))

    def results(self):
        return tuple(self.calculate_fuel_consumption(i == 0) for i in range(2))

    def calculate_fuel_consumption(self, constant=True):
        return min(np.sum(
            abs(self.pos - i) if constant else
            (abs(self.pos - i) * (abs(self.pos - i) + 1) // 2)
        ) for i in range(min(self.pos), max(self.pos)))
