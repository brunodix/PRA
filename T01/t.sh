for i in {100 1000 10000 100000}
do
	for j in {1..5}
	do
		PAGE=$i
		SIZE=`echo $j*100 | bc`
		echo "============"
		./a.out $PAGE $SIZE
	done
done
