# Usage: bash skripta.sh N M sol1 sol2
# with executables {{checker}}, {{gen_distinct}} in path
cnt=0
while true; do
    echo Generating testcase with N=$1, M=$2...
    ./gen_distinct $1 $2 > inp
    echo Running $3...
    time ./$3 < inp > off
    echo Running $4...
    time ./$4 < inp > out
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
