solution=../../a.out

rm ../out/basic/*.out
rm ../out/secret/*.out

rm tmp.sh

for i in `ls ../in/basic/*.in`; do 
    echo "echo processing" $i >> tmp.sh
    echo $solution $i " > " ../out/basic/$(basename $i .in).out >> tmp.sh
done
for i in `ls ../in/secret/*.in`; do 
    echo "echo processing" $i >> tmp.sh
    echo $solution $i " > " ../out/secret/$(basename $i .in).out >> tmp.sh
done

chmod 755 tmp.sh
./tmp.sh

echo "generated!"
