generator="../../input"
dirs=("../in/basic" "../in/secret")
for dir in "${dirs[@]}"; do
    rm $dir/*.desc
    rm $dir/*.in
done

f=../in/basic/00_sample1.in; echo "generated " $f
echo "3" >> $f
echo "3 1 5" >> $f

f=../in/basic/00_sample2.in; echo "generated " $f
echo "8" >> $f
echo "1 43 6 2 7 83 2 6" >> $f

f=../in/secret/00_sample1.in; echo "generated " $f
echo "3" >> $f
echo "8 1 5" >> $f

f=../in/secret/00_sample2.in; echo "generated " $f
echo "8" >> $f
echo "1 43 645 2 7 83 2 6" >> $f


for dir in "${dirs[@]}"; do
    for i in `seq 4`; do
        casename=10_small$i; base=${dir}/${casename}$i; ${generator} 10 10 > ${base}.in 2> ${base}.desc; echo "generated " $casename
    done
    for i in `seq 4`; do
        casename=20_medium$i; base=${dir}/${casename}$i; ${generator} 1000 100000 > ${base}.in 2> ${base}.desc; echo "generated " $casename
    done
    for i in `seq 4`; do
        casename=30_large$i; base=${dir}/${casename}$i; ${generator} 100000 1000000000 > ${base}.in 2> ${base}.desc; echo "generated " $casename
    done
    for i in `seq 8`; do
        casename=40_unbalanced$i; base=${dir}/${casename}$i; ${generator} 100000 3 > ${base}.in 2> ${base}.desc; echo "generated " $casename
    done
done
