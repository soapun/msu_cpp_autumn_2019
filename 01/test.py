import subprocess


def check(expr, result):
    out = subprocess.run(['./calc', expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error {0} != {1}, got {2}'.format(expr, result, out.stdout))
    else:
        print('ok')


check('2', '2')
check('2 + 2', '4')
check('3 * 3', '9')
check('2 + 2 * 3', '8')
check('2 + 2 * 3 * 4', '26')
check('2 + 2 * 3 + 2 * 5', '18')

check('2 - 2', '0')
check('-2 - 2', '-4')
check('--2 - 2', '0')
check('----2', '2')
check('-----2', '-2')

check('-2 * -3', '6')
check('2 * -3', '-6')

check('10 / 2', '5')
check('10 / 2 / 2', '2')
check('10 / -2', '-5')
check('10 / -2 / 2', '-3')

check('10 * -39 / 3 * 532 - -----666 / 101 + -1337 - 322 * 10----   ----123 ', '-73587')
