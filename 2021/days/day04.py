from advent_day import AdventDay


class Day04(AdventDay):
    def __init__(self, filename):
        with open(filename) as f:
            self.input = f.read().strip('\n').split('\n\n')
        self.input = (tuple(map(int, self.input[0].split(','))),
                      tuple(tuple(tuple(map(int, i.split()))
                                  for i in b.split('\n'))
                            for b in self.input[1:]))

    def results(self):
        return tuple(self.completed_board_sum(*self.input, i) for i in (0, -1))

    def completed_board_sum(self, drawn, boards, count=0):
        completed_board = sorted(((min(
            min(max(drawn.index(i) for i in row) for row in board),
            min(max(drawn.index(board[row][col]) for row in range(len(board)))
                for col in range(len(board[0])))), board)
            for board in boards), key=lambda k: k[0])[count]
        return sum(sum(i for i in r if drawn.index(i) > completed_board[0])
                   for r in completed_board[1]) * drawn[completed_board[0]]
