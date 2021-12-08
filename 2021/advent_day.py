import time


class AdventDay:
    def __init__(self, filename):
        self.lines = self.read_input(filename)

    def results(self):
        pass

    def read_input(self, filename, *, to_int=False,
                   strip=None, split=None, lines=True):
        input = None
        with open(filename) as file:
            input = file.read()
        if strip:
            input = input.strip(strip)
        if split is None and lines:
            input = input.splitlines()
        if split is not None:
            input = input.split(split)
        if to_int:
            input = list(map(int, input))
        return input

    def print_results(self, linebreak=True) -> int:
        start_time = time.time()
        results = self.results()
        lb = '' if not linebreak else '\n'
        if not results:
            print(f'No results for {self.__class__.__name__}')
            return 0
        end_time = time.time() - start_time
        print(str.format(
            '{} ({}){} P1: [ {} ]{} P2: [ {} ]'.format(
                self.__class__.__name__,
                str.center('{0:.4f}s'.format(round(end_time, 4)), 9),
                lb,
                str.center(str(results[0]), 18),
                lb,
                str.center(str(results[1]), 18))))
        return end_time
