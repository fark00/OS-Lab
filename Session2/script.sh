mkdir $1
for i in `seq $3 $4`; do
	touch $1/$i.$2
done
