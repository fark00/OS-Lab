if [ "-r" == $1 ]; then
        cat $2
fi
if [ $1 == "-m" ]; then
        for (( i = $5 ; i <= $6 ; i++))
        do
                touch $2$3$i.$4
        done
fi

