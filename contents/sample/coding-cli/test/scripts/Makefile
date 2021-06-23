all: out json

solution: ../../solution.cpp
	g++-9 -std=c++11 -o $@ $^

out: ../in/basic/*.in ../in/secret/*.in solution
	./generate_output.sh

json: 
	node generate_json.js

clean: 
	rm -f solution
	rm -f description
	rm -f description_en
	rm -f ../out/basic/*.out
	rm -f ../out/secret/*.out
	rm -f ../in/basic/*.desc
	rm -f ../in/basic/*.desc_en
	rm -f ../in/secret/*.desc
	rm -f ../in/secret/*.desc_en
