TASK=kraljevstvo

rm test/$TASK.{in,out}.*

# Subtask 1
./gen 101 19 7 999 > test/$TASK.in.1a
./gen 102 19 11 1000 > test/$TASK.in.1b
./gen 103 19 17 101 > test/$TASK.in.1c
./gen 104 20 10 666 0 80 > test/$TASK.in.1d
./gen 105 20 14 907 10 25 > test/$TASK.in.1e
./gen 106 20 8 778 0 100 > test/$TASK.in.1f
./gen 107 18 18 200 > test/$TASK.in.1g
./gen 108 20 7 889 100 > test/$TASK.in.1h
./gen 109 17 3 880 > test/$TASK.in.1i
./gen 110 17 4 880 > test/$TASK.in.1j
./gen 111 5 3 100000 100 > test/$TASK.in.1k

# Subtask 2
./gen 201 97 30 10090 > test/$TASK.in.2a
./gen 202 99 13 19009 > test/$TASK.in.2b
./gen 203 99 74 9092 > test/$TASK.in.2c
./gen 204 100 5 18008 > test/$TASK.in.2d
./gen 205 98 55 10099 10 30 > test/$TASK.in.2e
./gen 206 98 90 11910 5 80 > test/$TASK.in.2f
./gen 207 99 60 9993 5 0 > test/$TASK.in.2g
./gen 208 100 17 8090 100 > test/$TASK.in.2h
./gen 209 100 79 8909 100 > test/$TASK.in.2i
./gen 210 99 3 9009009 100 > test/$TASK.in.2j

# Subtask 3
./gen 301 494 55 1000000 > test/$TASK.in.3a
./gen 302 499 249 1000001 > test/$TASK.in.3b
./gen 303 500 381 1000000 > test/$TASK.in.3c
./gen 304 499 449 1000001 3 85 > test/$TASK.in.3d
./gen 305 498 3 1000000 100 > test/$TASK.in.3e
./gen 306 499 496 1000001 0 20 > test/$TASK.in.3f
./gen 307 500 300 1000000 10 35 > test/$TASK.in.3g
./gen 308 499 299 1000001 0 0 > test/$TASK.in.3h
./gen_spec 309 497 120 600 700 700000000 > test/$TASK.in.3i
./gen_spec 310 500 98 600 700 670000000 85 70 > test/$TASK.in.3j
./gen_spec 311 499 180 700 800 800000000 75 90 > test/$TASK.in.3k
./gen_spec 312 498 270 600 700 777777777 > test/$TASK.in.3l
./gen_spec 313 492 333 600 700 700000000 85 40 > test/$TASK.in.3m
./gen_spec 314 500 110 500 600 700000000 > test/$TASK.in.3n

# Subtask 4
./gen 401 2999 89 1010101 > test/$TASK.in.4a
./gen 402 3000 1112 121212 > test/$TASK.in.4b
./gen 403 2889 1900 1010101 > test/$TASK.in.4c
./gen 404 3000 1977 10010101 0 100 > test/$TASK.in.4d
./gen 405 2999 2888 10010002 10 20 > test/$TASK.in.4e
./gen 406 2998 7 1010010 > test/$TASK.in.4f
./gen 407 3000 2911 100010001 20 85 > test/$TASK.in.4g
./gen 408 3000 2981 10100102 0 38 > test/$TASK.in.4h
./gen_spec 409 3000 1100 600 700 777777777 > test/$TASK.in.4i
./gen_spec 410 3000 1001 700 800 777777777 > test/$TASK.in.4j
./gen_spec 411 3000 1200 650 800 444444444 > test/$TASK.in.4k
./gen_spec 412 3000 1800 600 700 777777777 90 65 > test/$TASK.in.4l
./gen_spec 413 3000 2001 800 900 888888888 > test/$TASK.in.4m
./gen_spec 414 3000 1200 800 900 888888888 70 90 > test/$TASK.in.4n
./gen_spec 415 3000 800 600 700 777777777 80 60 > test/$TASK.in.4o

for i in {1..4}; do
  for j in {a..z}; do
    IN=test/$TASK.in.$i$j
    OUT=test/$TASK.out.$i$j
    if [ -f "$IN" ]; then
      echo $i$j
      ./tonko < $IN > $OUT
    fi
  done
done
