solution=../../a.out

rm -f ../out/basic/*.out
rm -f ../out/secret/*.out
rm -f tmp.sh

for i in `ls ../in/basic/*.in`; do 
    echo "echo processing" $i >> tmp.sh
    echo "cat $i | $solution"  " > " ../out/basic/$(basename $i .in).out >> tmp.sh
done
for i in `ls ../in/secret/*.in`; do 
    echo "echo processing" $i >> tmp.sh
    echo "cat $i | $solution"  " > " ../out/secret/$(basename $i .in).out >> tmp.sh
done

chmod 755 tmp.sh
./tmp.sh
rm -f tmp.sh

echo "generated!"
