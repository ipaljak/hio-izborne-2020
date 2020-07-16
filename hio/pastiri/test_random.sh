cnt=0
while true; do
    echo Generating testcase with n=$1 and k=$2...
    python gen_random.py $1 $2 > inp
    echo Running $3...
    time ./$3 < inp > off
    echo Running $4...
    time ./$4 < inp > out
    ./pastiri_checker inp off out > verdict
    cat verdict
    if [[ 1 == $(head -n 1 verdict) ]]; then
        echo "$(tput setaf 6)AC$(tput sgr0)"
        let cnt+=1
    else
        cat verdict
        echo "$(tput setaf 1)WA$(tput sgr0)"
        echo Successful tests: $cnt
        break
    fi
    echo --------------------
done
