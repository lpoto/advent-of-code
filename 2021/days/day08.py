from advent_day import AdventDay


class Day08(AdventDay):
    def __init__(self, filename):
        self.input = tuple(tuple(tuple(set(c for c in s) for s in c.split(
        )) for c in i.split(' | ')) for i in self.read_input(filename))
        self.unique = {1: 2, 4: 4, 7: 3, 8: 7}

    def results(self):
        return (self.part_one(), self.part_two())

    def part_one(self):
        return sum(sum(1 for d in i[1] if len(d) in self.unique.values())
                   for i in self.input)

    def predicates(self, D: dict) -> dict:
        return {
            9: lambda x: not (D[4] | D[7]) - x,
            6: lambda x: len(x) == 6 and not (D[9] - D[1] - x),
            5: lambda x: len(x) == 5 and not (D[9] - D[1] - x),
            3: lambda x: len(x) == 5 and len(x & D[4]) == 3,
            2: lambda x: len(x & D[4]) == 2,
            0: lambda x: x,
        }

    def part_two(self):
        output_values = 0
        for i, j in self.input:
            D = {k: next(filter(lambda m: len(m) == v, i))
                 for k, v in self.unique.items()}
            for k, v in self.predicates(D).items():
                D[k] = next(filter(lambda m: m not in D.values() and v(m), i))
            output_values += int(''.join(
                str(tuple(D.keys())[tuple(D.values()).index(m)]) for m in j))
        return output_values
