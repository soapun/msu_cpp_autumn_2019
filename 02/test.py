import subprocess

def check(expr, result):
    check.flag = True
    out = subprocess.run(['./alloc', *(expr.split())], stdout=subprocess.PIPE)

    if out.stdout.decode('ascii') != result:
        print('error {0}\n != \n{1}'.format(out.stdout.decode('ascii'), result))
        check.flag = False

print()
check('1 1', 'allocated 1 byte\n')
check('-1337 1 2 3', 'std::bad_alloc\n')
check('6 4 3', 'allocated 4 bytes\n'
               'not enough space\n')
check('6 4 3 r 3', 'allocated 4 bytes\n'
                   'not enough space\n'
                   'allocated 3 bytes\n')
check('3 -1', 'not enough space\n')
check('3 4 3', 'not enough space\n'
               'allocated 3 bytes\n')

if check.flag:
    print('All tests passed.')