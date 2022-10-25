geneticomake:
	g++ principal.cpp funcao.cpp gerador_numeros.cpp operacoes.cpp -o saida.out -lm

clean:
	rm saida.out
