geneticomake:
	g++ Principal.cpp funcao.cpp gerador_numeros.cpp ag.cpp -o saida.out -lm

clean:
	rm saida.out
