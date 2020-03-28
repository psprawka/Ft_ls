import os
import sys
import subprocess

NORMAL="\x1B[0m"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'

USAGE="usage: python3 tests.py [-c | -d | -l]\n  -c\tcompile the executable\n\
  -d\tshow diffs in failed tests\n  -l\teave compared files (ft_ls vs ls)\n"

test_cases =    ['author author', 
                'Libft/',
                'author Libft/ Libft/srcs/',
                'Libft/ author',
                ' ',
                '-a .',
                '.',
                '-i '
                '-A .',
                '-A',
                '-i .', 
                '-A Libft/ Makefile author .',
                '-r author /home/psprawka/Desktop/ Libft/',
                '-R .',
	            '-la Libft/ test',
                '-ltat -ta Libft/ test',
                '-ltat -ta Libft/',
                '-ltRat -ta -l Libft',
			    '-tr -R /opt',
                'Libft/ author Makefile ft_ls my_ls',
                '-r Libft/ author Makefile ft_ls my_ls ',
                '-rA Libft/ author Makefile ft_ls my_ls ',
                '-r Libft/ author /home/psprawka/Desktop/',
			    '-t author Libft/ ',
                '-t Libft/',
                '-tr Libft/srcs/ author Makefile Libft/',
                '-a Libft/',
                '-at -i /home/psprawka/',
                '-R Libft/srcs .',
                '-lRtar Libft',
                '-i -lR Libft',
                '-A -a -A -AA -a Libft/srcs/',
                '-Rrta -l Libft',
                '-lRrta Libft test Makefile',
                '-A /home/psprawka/Dreem-Embedded-Nano . Makefile',
			    '-t /home/',
                '-at Libft/srcs/',
                '-R -i -l Libft/srcs test Makefile Makefile',
                '-l test Libft',
                '-l -i -A test author Libft Makefile',
                '-l Libft',
                '..',
                '-r .',
                '-r Libft/',
                '-A Libft/',
                '-rA /home/psprawka/42',
                '-R /home/psprawka/42 srcs/',
                '-Rr /home/psprawka/42 srcs/',
                '-Rt /home/psprawka/Dreem-Embedded-Nano /data',
                '-Rrt /home/psprawka/Dreem-Embedded-Nano srcs/',
                '-RrtA /home/psprawka/Dreem-Embedded-Nano srcs/',
                '-t -t -t -t  Libft/',
                '-l -r includes',
                '-l includes',
                '-l -R -r /data']

                # Tests that are supposed to fail:
                #'-r Libft/ -y author /home/psprawka/Desktop/',
                #'-la Libft/ /invalid_dir/ no_file',

if "-c" in sys.argv:
    os.system("make")

if not os.path.exists("./ft_ls"):
    print("Executable ./ft_ls does not exist. Unable to compare the results.\n", USAGE, sep="")
    exit()

res_count = 0
for test in test_cases:
    print("Checking '%sls %s%s' testcase... " % (YELLOW, test, NORMAL), end="")

    os.system("./ft_ls " + test  + " > my_ls")
    os.system("ls " + test  + " > their_ls")

    my_ls = os.popen('cat my_ls').read()
    their_ls = os.popen('cat their_ls').read()

    if "-l" in test or "-i" in test:
        my_lines = my_ls.split('\n')
        
        for i in range(len(my_lines)):
            my_lines[i] = " ".join(my_lines[i].split(' '))
            #my_lines[i] = "".join([x for x in my_lines[i] if (x != '@')])
            if "total" in my_lines[i]:
                my_lines[i] = "total here"
        my_ls = "\n".join(my_lines)
        with open('my_ls', 'w+') as my_file:
            my_file.write(my_ls)

        their_lines = their_ls.split('\n')
        for i in range(len(their_lines)):
            their_lines[i] = " ".join(list(filter(lambda x: x != "", their_lines[i].split(' '))))
            #their_lines[i] = "".join([x for x in their_lines[i] if (x != '@')])
            if "total" in their_lines[i]: #just on linux because total differs
                their_lines[i] = "total here"
        their_ls = "\n".join(their_lines)
        with open('their_ls', 'w+') as their_file:
            their_file.write(their_ls)


    if my_ls == their_ls:
        print("%sPASS%s!" % (GREEN, NORMAL))
        res_count += 1
    else:
        print("%sFAIL%s!" % (RED, NORMAL))
        if "-d" in sys.argv:
            os.system("diff -y my_ls their_ls")
            print("")

dec = "============================="
print("\n%s\nRESULT | PASSED: %s%d%s FAILED: %s%d%s\n%s\n" % \
    (dec, GREEN, res_count, NORMAL, RED, len(test_cases) - res_count, NORMAL, dec))

if "-l" in sys.argv:
    os.system("rm my_ls their_ls")
    os.system("make fclean")