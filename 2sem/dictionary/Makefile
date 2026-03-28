all:
	g++ dict.cpp stroka.cpp -o dict
	g++ -DNOMOVESEMANTICS dict.cpp stroka.cpp -o dict-no-ms
	g++ dict-with-tree.cpp stroka.cpp -o dict-with-tree
clean:
	rm dict dict-no-ms

