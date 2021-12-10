from advent_day import AdventDay


class Day10(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.input = f.read().splitlines()

    def results(self):
        return (self.part_one(), self.part_two())

    def valid_paren_sequence(self, sequence):
        pairs = {'(': ')', '[': ']', '{': '}', '<': '>', }
        stack = list()
        for i in sequence:
            stack.append(i)
            if i not in pairs:
                if len(stack) == 1 or i != pairs[stack[-2]]:
                    return stack
                stack.pop()
                stack.pop()
        return stack

    def part_one(self):
        points = {')': 3, ']': 57, '}': 1197, '>': 25137}
        return sum(points[i] for i in (self.valid_paren_sequence(
            k)[-1] for k in self.input) if i in points)

    def part_two(self):
        points = {'(': 1, '[': 2, '{': 3, '<': 4}
        scores = list()
        for sequence in self.input:
            stack = self.valid_paren_sequence(sequence)
            if stack[-1] not in points:
                continue
            r = 0
            for i in range(len(stack) - 1, -1, -1):
                r = 5 * r + points.get(stack[i])
            if r != 0:
                scores.append(r)
        return sorted(scores)[len(scores) // 2]
