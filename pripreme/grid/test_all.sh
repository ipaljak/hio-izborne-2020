for (( n=1; n<=$1; n++ )); do
    for (( m=n; m<=$1; m++ )); do
        echo $n $m > inp
        ./$2 < inp > out
        ./checker inp out out > verdict
         if [[ 1 != $(head -n 1 verdict) ]]; then
             echo n=$n m=$m
             cat verdict
         fi
    done
done
