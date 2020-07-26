import string
import sys

from fractions import Fraction

sys.setrecursionlimit(1000010)

def print_to_stderr(*a): 
  print(*a, file = sys.stderr) 
  
perm = []
m, n = 0, 0
bio = []
graf = []

def unesi():
  global perm
  global m, n
  global graf
  m, n = map(int, input().split())
  for i in range(m):
    niz = list(map(int, input().split()))
    for i in range(n):
      niz[i] = niz[i] - 1
    perm.append(niz)
    
  for i in range(n):
    graf.append([])
    bio.append([])
    for j in range(n):
      graf[i].append([])
      bio[i].append(0)
      for k in range(m):
        graf[i][j].append([perm[k][i], perm[k][j]])
 
velicine_orbita = []
broj_inverznih = 0
broj_ukupnih = 0
brojac = 0
rj = Fraction()

def dfs(x, y):
  global bio, graf
  global broj_inverznih, broj_ukupnih, brojac  
  assert bio[x][y] == 0 or bio[x][y] == brojac, "zar graf nije scc?"
  if bio[x][y] != 0:
    return
  bio[x][y] = brojac
  broj_ukupnih = broj_ukupnih + 1
  if x > y:
    broj_inverznih = broj_inverznih + 1
  for i in range(m):
    dfs(graf[x][y][i][0], graf[x][y][i][1])
    

def obradi_komponentu(x, y):
  global broj_inverznih, broj_ukupnih, brojac, rj
  global velicine_orbita
  broj_inverznih, broj_ukupnih = 0, 0
  brojac = brojac + 1
  dfs(x, y)
  rj = rj + Fraction((broj_ukupnih - broj_inverznih) * broj_inverznih, broj_ukupnih)
  velicine_orbita.append(broj_ukupnih)

def rijesi():
  for i in range(n):
    for j in range(n):
      if bio[i][j] == 0:
        obradi_komponentu(i, j)

### ovaj dio je za analizu grupe iz inputa ###

klasicni_graf = []
klasicni_bio = []
klasicni_brojac = 0
klasicni_velicine_orbita = []
klasicni_velicina_komponente = 0

def klasicni_dfs(x): 
  global klasicni_graf, klasicni_bio, klasicni_brojac, klasicni_velicina_komponente
  assert klasicni_bio[x] == 0 or klasicni_bio[x] == klasicni_brojac, "zar klasicni graf nije scc?"
  if klasicni_bio[x] != 0:
    return
  klasicni_velicina_komponente = klasicni_velicina_komponente + 1
  klasicni_bio[x] = klasicni_brojac
  for i in range(m):
    klasicni_dfs(klasicni_graf[x][i])

def obradi_klasicnu_komponentu(x):
  global klasicni_brojac, klasicni_velicina_komponente, klasicni_velicine_orbita
  klasicni_brojac = klasicni_brojac + 1
  klasicni_velicina_komponente = 0
  klasicni_dfs(x)
  klasicni_velicine_orbita.append(klasicni_velicina_komponente)

def analiziraj_klasicnu_grupu():
  global perm, klasicni_graf, klasicni_bio
  for i in range(n):
    klasicni_graf.append([])
    klasicni_bio.append(0)
    for k in range(m):
      klasicni_graf[i].append(perm[k][i])

  for i in range(n):
    if klasicni_bio[i] == 0:
      obradi_klasicnu_komponentu(i)
  print_to_stderr("broj obita grupe iz inputa:", klasicni_brojac)
  print_to_stderr("velicine orbita grupe iz inputa:", klasicni_velicine_orbita) 

### -------------------------------------- ###

if __name__ == "__main__":
  unesi() 
  print_to_stderr("m, n:", m, n)
  analiziraj_klasicnu_grupu()
  rijesi()
  mod = int(1e9 + 7)
  if rj.numerator == 0:
    print(0)
  else:
    inverz = pow(rj.denominator, mod-2, mod)
    ispis = (rj.numerator * inverz) % mod
    print(ispis)
  print_to_stderr("rj kao razlomak:", rj)
  print_to_stderr("rj kao float:", float(rj))
  print_to_stderr("vjerojatnost jedne inverzije:", float(rj) / (n * (n - 1) / 2))
  print_to_stderr("broj orbita:", brojac)
  print_to_stderr("velicine orbita:", velicine_orbita)
