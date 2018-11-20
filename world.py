from itertools import combinations
import ctypes
import os

c_file_dir = 'individuals'
so_file_dir = 'society'


def _compile(file_name):
    output_name = file_name.rsplit('.', -1)[0] + '.so'

    try:
        os.system("gcc %s -fPIC -shared -o %s" % (os.path.join(c_file_dir, file_name),
                                                  os.path.join(so_file_dir, output_name)))
        result = file_name + ' compile successfully'
    except Exception as e:
        result = e

    return result


def _compile_all():
    in_files = os.listdir(c_file_dir)
    c_files = filter(lambda name: name.endswith('.c'), in_files)
    results = list(map(_compile, c_files))
    return results


def _run(ab):
    a, b = ab
    choices_a = ''
    choices_b = ''
    for i in range(20):
        c_a = a.decide(i, choices_a.encode(), choices_b.encode())
        c_b = b.decide(i, choices_b.encode(), choices_a.encode())
        choices_a += chr(c_a)
        choices_b += chr(c_b)
    sa, sb = _get_score(choices_a, choices_b)
    return choices_a, choices_b, sa, sb


# |             | COOPERATION | BETRAYAL |
# |-------------|-------------|----------|
# | COOPERATION | 3,3         | 0,5      |
# | BETRAYAL    | 5,0         | 1,1      |

def _get_score(a, b):
    sa = 0
    sb = 0
    for ac, bc in zip(a, b):
        if ac == 'c' and bc == 'c':
            sa += 3
            sb += 3
        elif ac == 'c' and bc == 'b':
            sa += 0
            sb += 5
        elif ac == 'b' and bc == 'c':
            sa += 5
            sb += 0
        else:
            sa += 1
            sb += 1
    return sa, sb


def _run_all():
    in_files = os.listdir(so_file_dir)
    so_files = filter(lambda name: name.endswith('.so'), in_files)
    so_files = list(map(lambda name: os.path.join(so_file_dir, name), so_files))
    runnable = list(map(ctypes.CDLL, so_files))
    results = list(map(_run, combinations(runnable, 2)))
    return results


if __name__ == '__main__':
    print(_compile_all())
    print(_run_all())

