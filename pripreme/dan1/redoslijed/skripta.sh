# Usage: bash skripta.sh N M L type sol1 sol2
# with executables {{checker}}, {{generator}} in path
cnt=0
while true; do
    echo Generating testcase with N=$1, M=$2...
    ./generator $1 $2 $3 $4 > inp
    echo Running $5...
    time ./$5 < inp > off
    echo Running $6...
    time ./$6 < inp > out
    ./checker inp off out > verdict
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

