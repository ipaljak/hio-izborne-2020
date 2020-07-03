N = int(input())
if N <= 2:    
    str = "10"
elif N <= 4:
    str = "1100"
elif N <= 8:
    str = "11101000"
else:
    str = "110100"*N # triba dat lufta

print(str[:N])

