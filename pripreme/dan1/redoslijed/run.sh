for i in {1..3}
do
  ./redoslijed_minmax < test/redoslijed.dummy.in.$i > test/redoslijed.dummy.out.$i
done

for i in {a..d}
do
  ./redoslijed_minmax < test/redoslijed.in.1$i > test/redoslijed.out.1$i
done

for i in {a..f}
do
  ./redoslijed_minmax < test/redoslijed.in.2$i > test/redoslijed.out.2$i
done

for i in {a..o}
do
  ./redoslijed_minmax < test/redoslijed.in.3$i > test/redoslijed.out.3$i
done

for i in {a..h}
do
  ./redoslijed_minmax < test/redoslijed.in.4$i > test/redoslijed.out.4$i
done

for i in {a..l}
do
  ./redoslijed_minmax < test/redoslijed.in.5$i > test/redoslijed.out.5$i
done

for i in {a..r}
do
  ./redoslijed_minmax < test/redoslijed.in.6$i > test/redoslijed.out.6$i
done
