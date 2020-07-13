while true; do
    python gen_random.py $1 $2 > inp
    ./$3 < inp > off
    ./$4 < inp > out
    ./pastiri_checker inp off out > verdict
    if [[ 1 == $(head -n 1 verdict) ]]; then
        echo AC
    else
        break
    fi
done

