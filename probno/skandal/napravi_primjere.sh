f() {
  echo $1 $2 $3
  ./generator $3 > test/skandal.in.$1$2
  ./skandal < test/skandal.in.$1$2 > test/skandal.out.$1$2
}

dummy() {
  echo dummy $1 $2
  ./generator $2 > test/skandal.dummy.in.$1
  ./skandal < test/skandal.dummy.in.$1 > test/skandal.dummy.out.$1
}

dummy 1 prvi
dummy 2 prvi
dummy 3 prvi

f 1 a prvi
f 1 b prvi
f 1 c prvi
f 1 d prvi
f 1 e prvi

f 2 a prvi
f 2 b drugi
f 2 c drugi
f 2 d drugi
f 2 e drugi

f 3 a prvi
f 3 b drugi
f 3 c treci
f 3 d treci
f 3 e treci

f 4 a drugi
f 4 b cetvrti
f 4 c cetvrti
f 4 d cetvrti
f 4 e cetvrti
