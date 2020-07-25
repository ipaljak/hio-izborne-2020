echo $1 $2 > inp
./$3 < inp > out
./checker inp out out
