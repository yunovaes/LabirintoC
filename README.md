# Labirinto

Um algoritmo na linguagem C que calcula a distância entre dois pontos dentro de uma matriz. Sendo uma variação da busca em largura, calcula a distância de um ponto inicial a partir dos seus vizinhos (acima, abaixo, a esquerda e a direita). Para esse algoritmo considera-se que alguns vizinhos não existem ou existem alguns obstáculos no labirinto.

### Entrada

O tipo de entrada consiste em dois números indicando a dimensão da matriz, tendo em vista que ‘0’ é uma posição livre e ‘-1’ é um obstáculo, como observado abaixo:

``` 
7 7
0 0 –1 0 0 0 0
0 0 –1 –1 0 0 0
0 0 0 0 0 0 0
0 0 0 –1 –1 0 0
–1 0 0 0 –1 0 0
–1 –1 –1 0 0 0 0
–1 –1 –1 0 0 0 0 
```
Após a entrada, o programa solicita as duas coordenadas (final e inicial)


### Passo a passo
  
  Para esse algoritmo seguimos uma sequência de eventos: 
  
	1. Numerar todos os vizinhos do ponto inicial com 1. 
	2. Colocar os vizinhos em uma fila.
	3. Enquanto a fila não estiver vazia: 
		*Retirar um ponto da fila; 
		*Numerar os seus vizinhos livres com o número do ponto acrescido de 1; e
		*Colocar os novos pontos (vizinhos livres) na fila.
	4. Se a fila estiver vazia e não se tiver atingido o ponto de destino, não existe percurso. Caso contrário, imprimir o percurso.
  
### Resultado
  
Ao final do programa é apresentado o menor caminho com todas as coordenadas. 
