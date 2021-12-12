from advent_day import AdventDay


class Day12(AdventDay):
    def __init__(self, filename):
        self.paths = dict()
        with open(filename) as f:
            for a, b in {tuple(ln.split('-')) for ln in f.read().splitlines()}:
                self.paths.setdefault(a, set()).add(b)
                if a != 'start':
                    self.paths.setdefault(b, set()).add(a)

    def results(self):
        memo = set()
        return tuple(self.paths_count('start', memo, i == 1) for i in range(2))

    def paths_count(self, cur, memo, twice=False):
        if cur == 'end':
            return 1
        t = not cur.islower()
        if not t:
            if cur in memo:
                if not twice:
                    return 0
                t, twice = True, False
            memo.add(cur)
        count = 0
        for i in self.paths[cur]:
            count += self.paths_count(i, memo, twice)
        if not t:
            memo.remove(cur)
        return count
