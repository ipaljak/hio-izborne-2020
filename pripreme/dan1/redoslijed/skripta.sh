# Usage: bash skripta.sh gen seed N M L type distinct sol1 sol2
# with executable {{checker}} in path
cnt=0
while true; do
    echo Generating testcase with N=$3, M=$4...
    ./$1 $2 $3 $4 $5 $6 $7 > inp
    echo Running $8...
    time ./$8 < inp > off
    echo Running $9...
    time ./$9 < inp > out
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
