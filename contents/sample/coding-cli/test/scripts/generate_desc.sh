g++ -o desc description_generator.cpp
for dir in basic secret; do
    rm ../in/$dir/*.desc ../in/$dir/*.desc_en
    for i in `ls ../in/$dir/*.in`; do
        echo "description for" $dir $i "is being generated"
        ./desc < $i > ${i/.in/.desc} 2> ${i/.in/.desc_en}
    done
done
