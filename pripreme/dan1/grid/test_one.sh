echo $2 $3 > inp
./$1 < inp > out
./checker inp out out
