solution=../../a.out

rm ../out/basic/*.out
rm ../out/secret/*.out

rm tmp.sh

for i in `ls ../in/basic/*.in`; do 
    echo "echo processing" $i
    $solution $i
    cp answer.txt ../out/basic/$(basename $i .in).out
done
for i in `ls ../in/secret/*.in`; do 
    echo "echo processing" $i
    $solution $i
    cp answer.txt ../out/secret/$(basename $i .in).out
done

echo "generated!"
