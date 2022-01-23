Grafo - Matriz de Adjacência

N celas.

Vértices são números de 0 a N-1, representando cada cela.
Cada número refere-se ao indice de um vetor com o nome e os atributos da cela.

Como cada jogador que iniciar uma rodada terá os atributos da cela, então a seta que liga duas celas representará
que quem estiver naquela cela tem os niveis de atributos necessarios para que ao jogar o dado e adicionar um ponto em um atributo  conseguir passar para a outra cela.

Com isso, trata-se de um digrafo com vertices sendo as celas e as setas (U,V) que ligam uma cela a outra indica que quem estiver na cela U consegue ir para cela V, devido aos niveis dos atributos da cela de partida.

Na Matriz de Adjacência, se a seta existir da cela U para V, então a entrada [u][v] = 1, do contrario 0;
Por ser um digrafo [u][v] não necessariamente é igual a [v][u].
