from advent_day import AdventDay


class Day11(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            m = f.read().splitlines()
            self.matrix = {(i, j): int(m[i][j])
                           for i in range(len(m)) for j in range(len(m))}

    def results(self):
        return self.octopus_flashes(100)

    def neighbours(self, i, j):
        return {(i + m, j + n) for m, n in {*zip(
            (-1, -1, -1, 0, 0, 1, 1, 1),
            (-1, 1, 0, -1, 1, 0, -1, 1)
        )} if (i + m, n + j) in self.matrix}

    def flash(self, i, j):
        c = 1
        for k in self.neighbours(i, j):
            if self.matrix[k] != 0:
                self.matrix[k] = (self.matrix[k] + 1) % 10
                c = c if self.matrix[k] != 0 else c + self.flash(*k)
        return c

    def octopus_flashes(self, count):
        flashes, step, sync_flash = 0, 0, None
        while (step < count or not sync_flash):
            self.matrix = {k: (v + 1) % 10 for k, v in self.matrix.items()}
            for k in {k for k, v in self.matrix.items() if v == 0}:
                cur_flashes = self.flash(*k)
                flashes = flashes if step >= count else flashes + cur_flashes
            if all(v == 0 for v in self.matrix.values()):
                sync_flash = step
            step += 1
        return (flashes, sync_flash)
