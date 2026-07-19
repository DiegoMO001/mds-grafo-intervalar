# Conjunto Dominante Mínimo em Grafos de Intervalos (Parque Linear)

## Sobre o Problema

Considere um parque longo e estreito mapeado por uma única trilha principal (unidimensional). 
*   **Postos de Monitoramento:** Cada posto $v$ é responsável por monitorar um trecho contínuo que vai da posição física $l_v$ até $r_v$ ($[l_v, r_v]$).
*   **Adjacência/Comunicação:** Dois postos comunicam-se diretamente se, e somente se, houver interseção ou sobreposição entre suas áreas de cobertura física ($[l_a, r_a] \cap [l_b, r_b] \neq \emptyset$).
*   **Objetivo:** Escolher o menor número possível de postos (centrais) para que todos os demais postos do parque estejam cobertos ou consigam se comunicar diretamente com pelo menos uma central.

Este projeto é uma aplicação em C  eficiente para resolver o problema do **Conjunto Dominante Mínimo (Minimum Dominating Set)** aplicado a um cenário geométrico unidimensional: a cobertura de uma trilha linear por postos de monitoramento com intervalos de alcance.

Ao contrário de grafos arbitrários, a estrutura topológica de um parque linear permite modelar o problema como um **Grafo de Intervalos**, tornando possível encontrar a solução ótima global de forma exata utilizando um algoritmo guloso acoplado a uma ordenação geométrica.

## Detalhes Técnicos

O programa lê dados de um arquivo de texto plano (`.txt`) onde cada linha representa um posto e suas coordenadas espaciais na trilha.

O algoritmo atinge a otimalidade comprovada explorando a ordenação natural dos intervalos na reta real:

1.  **Ordenação dos Extremos Direitos:** Os intervalos são ordenados prioritariamente de forma crescente pelo ponto de término ($r_i$). Se houver empate, utiliza-se o ponto de início ($l_i$). Essa ordenação é feita em tempo $O(N \log N)$ usando a função `qsort`.
2.  **Escolha Estratégica da Central:** Varrendo os intervalos ordenados, ao encontrar o primeiro posto que ainda não foi dominado (coberto), o algoritmo busca de forma gulosa, entre todos os seus vizinhos adjacentes, aquele que estende o monitoramento o mais à direita possível (`maior_dir`). 
3.  **Dominação:** O posto escolhido é promovido a central e todos os intervalos adjacentes a ele são marcados instantaneamente como dominados.

## Tecnologias Utilizadas

* **Linguagem:** C
* **IDE:** CodeBlocks 20.03
* **Compilador:** MinGW-w64

## Como Compilar e Executar

**Certifique-se de ter um compilador C (como o GCC) devidamente instalado em seu ambiente.**

## Saída do Programa

Ao término (por provar a otimalidade ou por exceder o limite de tempo), a ferramenta exibe no terminal:
*   A cardinalidade (tamanho) da melhor solução encontrada.
*   Os identificadores exatos dos vértices (postos/centrais) selecionados.
*   A indicação booleana de que a otimalidade foi **comprovada** ou **não** (se a árvore foi explorada por completo).
*   O tempo total de processamento em segundos.
