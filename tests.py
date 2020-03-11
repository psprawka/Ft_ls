import os
import sys
import subprocess

NORMAL="\x1B[0m"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'

USAGE="usage: python3 tests.py [-c | -d | -r]\n  -c\tcompile the executable\n\
  -d\tshow diffs in failed tests\n  -r\tremove makefile files\n"

test_cases =    ['author author', 
                'Libft/',
                'author Libft/ Libft/srcs/',
                'Libft/ author',
                ' ',
                '-a .',
                '.',
                '-A .',
                '-A',
                '-r author /home/psprawka/Desktop/ Libft/',
                '-R .',
	            #'-la Libft/ /Desktop',
                #'-ltRat -ta -l Libft/',
			    '-tr -R /opt',
                #'-r Libft/ -y author /home/psprawka/Desktop/',
                'Libft/ author Makefile ft_ls my_ls',
                '-r Libft/ author Makefile ft_ls my_ls ',
                '-rA Libft/ author Makefile ft_ls my_ls ',
                '-r Libft/ author /home/psprawka/Desktop/',
			    '-t author Libft/ ',
                '-t Libft/',
                '-tr Libft/srcs/ author Makefile Libft/',
                '-a Libft/',
                '-at /home/psprawka/',
                '-R Libft/srcs .',
                #'-lRtar Libft/',
                #'-ilR Libft/',
                '-A -a -A -AA -a Libft/srcs/',
                #'-Rrtla /etc/dev/',
                '-A /home/psprawka/Dreem-Embedded-Nano . Makefile',
			    '-t /home/',
                '-at Libft/srcs/',
                '..',
                '-r .',
                '-r Libft/',
                '-A Libft/',
                '-rA /home/psprawka/42',
                '-R /home/psprawka/42 srcs/',
                '-Rr /home/psprawka/42 srcs/',
                '-Rt /home/psprawka/Dreem-Embedded-Nano /data/',
                '-Rrt /home/psprawka/Dreem-Embedded-Nano srcs/',
                '-RrtA /home/psprawka/Dreem-Embedded-Nano srcs/',
                '-t -t -t -t  Libft/']
                #'-l -R -r /etc/dev/']

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

if "-r" in sys.argv:
    os.system("rm my_ls their_ls")
    os.system("make fclean")