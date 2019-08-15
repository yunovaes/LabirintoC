# Labirinto

Um algoritmo na linguagem C que calcula a distância entre dois pontos dentro de uma matriz. Sendo uma variação da busca em largura, calcula a distância de um ponto inicial a partir dos seus vizinhos (acima, abaixo, a esquerda e a direita). Para esse algoritmo considera-se que alguns vizinhos não existem ou existem alguns obstáculos no labirinto.

### Entrada

O tipo de entrada consiste em dois números indicando a dimensão da matriz, tendo em vista que ‘0’ é uma posição livre e ‘-1’ é um obstáculo, como observado abaixo:

``` 0 0 0 0 8 0 0 0 0
0 0 7 9 0 2 8 0 0
0 1 0 0 0 0 0 5 0
0 3 0 0 1 0 0 8 0
6 0 0 3 0 4 0 0 5
0 4 0 0 7 0 0 2 0
0 8 0 0 0 0 0 7 0
0 0 5 4 0 1 3 0 0
0 0 0 0 2 0 0 0 0 
```

### Passo a passo
  
  Para esse algoritmo seguimos uma sequência de eventos: 
  
	1. Numerar todos os vizinhos do ponto inicial com 1. 
	2. Colocar os vizinhos em uma fila.
	3. Enquanto a fila não estiver vazia: 
			* Retirar um ponto da fila; 
			* Numerar os seus vizinhos livres com o número do ponto acrescido de 1; e
			* Colocar os novos pontos (vizinhos livres) na fila.
	4. Se a fila estiver vazia e não se tiver atingido o ponto de destino, não existe percurso. Caso contrário, imprimir o percurso.
  
### Resultado
  
  Como resultado temos a saída no mesmo formato da entrada mas os elementos que estão em '0', agora estão preenchidos com os números corretos:
  
```9 5 4 1 8 6 2 3 7
3 6 7 9 5 2 8 4 1
8 1 2 7 4 3 6 5 9
7 3 9 2 1 5 4 8 6
6 2 8 3 9 4 7 1 5
5 4 1 6 7 8 9 2 3
4 8 6 5 3 9 1 7 2
2 7 5 4 6 1 3 9 8
1 9 3 8 2 7 5 6 4
```
