from advent_day import AdventDay


class Day02(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.directions = tuple((i[0], int(i.split()[1]))
                                    for i in f.readlines())

    def results(self):
        return tuple(self.calculate_position(i == 1) for i in range(2))

    def calculate_position(self, multiply_aim=False):
        forward, down, aim = 0, 0, 0
        for direction in self.directions:
            if direction[0] == 'f':
                forward += direction[1]
                down += aim * direction[1]
            else:
                aim += direction[1] if direction[0] == 'd' else -direction[1]
        return forward * (down if multiply_aim else aim)
