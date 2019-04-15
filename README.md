# Procura de melhor caminho

Este projeto visa aprimorar o projeto anterior que busca aplicar o caixeiro viajante em imagens.
Como a solução perfeita sequenciasl é de ordem fatorial O(N!), uma implementação usando recursos concorrentes nativos de go e uma solução usando busca de menor aresta foram implementados, tendo em vista que essas são soluções aproximadas....
O objetivo desse projeto é implementar as 3 soluções, fazer uma argumentação teórica para a eficiencia do algoritmo concorrente para grafos de tamnho arbitráio e apartir de análise empírica baseda na análise de 3 caracteristicas do grafo, usar o algoritmo k nearest neighbor para determinar qual dos 3 algoritmos será usado.


## Autor

| Nomde | github |
|:-----:|:------:|
| Ariel Vieira Lima Serafim | [@ArielSixwings](https://github.com/ArielSixwings/) |


## Instalação e Execução


```shell
$ git clone https://github.com/ArielSixwings/Divide-and-conquer

//para baixar e instalar o gocv(consequentemente o opencv, que lhe permite trabalhar com c++) para o uso de go+opencv, execute:
$ masterframebuild.sh
```
obs: Para executar a aplicação é necessário a instalação do [go](https://golang.org/doc/install) e [gocv](https://gocv.io/getting-started/).
