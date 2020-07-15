for inp in test/pastiri.in.$2*; do
    echo Running on $inp...
    if timeout 3s ./$1 < $inp > out 2> /dev/null; then
        ./pastiri_checker $inp ${inp/in/out} out
    else
        echo TLE
    fi
done
