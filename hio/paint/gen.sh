TASK=paint

# Subtask 1
./gen 101 20 40 40 10 > test/$TASK.in.1a
./gen 102 40 37 100 4 > test/$TASK.in.1b
./gen 103 10 1000 5000 1000 > test/$TASK.in.1c
./gen 104 101 99 9999 5 > test/$TASK.in.1d
./gen_spec 105 97 99 10000 > test/$TASK.in.1e
./gen_spec 106 88 110 10000 3 2 10 > test/$TASK.in.1f

# Subtask 2
./gen 201 1 50000 100000 5 > test/$TASK.in.2a
./gen 202 1 100000 100000 3 > test/$TASK.in.2b
./gen_line 203 200000 100000 > test/$TASK.in.2c

# Subtask 3
./gen_2col 301 100 1999 17000 50 > test/$TASK.in.3a
./gen_2col 302 100 1999 22000 1 > test/$TASK.in.3b
./gen_2col 303 3001 66 20050 30 > test/$TASK.in.3c
./gen_2col 304 11 17777 42700 15 > test/$TASK.in.3d
./gen_2col 305 6 31444 50000 60 > test/$TASK.in.3e

# Subtask 4
./gen 401 300 488 59500 10 > test/$TASK.in.4a
./gen_spec 402 399 499 89999 > test/$TASK.in.4b
./gen_spec 403 100 1887 77999 2 1 > test/$TASK.in.4c
./gen_spec 404 333 444 92999 3 2 > test/$TASK.in.4d
./gen_spec 405 50 3333 98888 4 4 > test/$TASK.in.4e
./gen_spec2 406 300 600 100000 10 12 > test/$TASK.in.4f
./gen_spec2 407 300 600 100000 20 12 > test/$TASK.in.4g
./gen_spec2 408 300 600 100000 35 12 > test/$TASK.in.4h

for t in {1..4}; do
  for i in {a..h}; do
    ./paint_tonko < test/$TASK.in.$t$i > test/$TASK.out.$t$i
  done
done

