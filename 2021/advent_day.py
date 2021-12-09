import time


class AdventDay:
    def __init__(self, filename):
        with open(filename) as f:
            self.lines = f.readlines()

    def results(self):
        pass

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
