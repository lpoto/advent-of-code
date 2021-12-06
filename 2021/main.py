import sys
import os

import days as days

path = os.path.dirname(os.path.abspath(__file__))
days_dict = {k: v for k, v in days.__dict__.items() if isinstance(v, type)}


def run_day(day_idx):
    name = f'Day{int(day_idx):02d}'
    if name not in days_dict:
        print(f'Solution for day {day_idx} not found')
        return
    day = days_dict.get(name)(path + '/inputs/' + name.lower() + '.txt')
    day.print_results()


def run_all():
    if len(days_dict) < 1:
        print('No solutions found')
        return
    print('--- Advent of code 2021 ---\n')
    total_time = 0
    for k, d in days_dict.items():
        day = d(path + '/inputs/' + k.lower() + '.txt')
        total_time += day.print_results(False)
    print('\nTotal time: {}s'.format(round(total_time, 4)))


try:
    if len(sys.argv) < 2:
        raise ValueError
    day_idx = int(sys.argv[1].replace('day', '', 1))
except ValueError:
    run_all()
else:
    run_day(day_idx)
