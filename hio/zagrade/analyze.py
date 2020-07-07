"""Vizualizacija primjera za Zagrade.

Uparene zagrade oboji zeleno, a ostale crveno.

"""

import termcolor

n = int(input())
s = input()

colored_s = [termcolor.colored(c, 'red') for c in s]

stack = []
for i in range(n):
    if s[i] == ')' and stack and s[stack[-1]] == '(':
        colored_s[i] = termcolor.colored(')', 'green')
        colored_s[stack.pop()] = termcolor.colored('(', 'green')
    else:
        stack.append(i)

print(''.join(colored_s))
