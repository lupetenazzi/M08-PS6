# Ponderada 1 e 2 — ROS2, Navegação em Labirinto e Algoritmos de Busca


Vídeo de apresentação da ponderada: https://youtu.be/r959nu6dlZQ

Essa ponderada envolve a implementação de dois sistemas independentes de navegação robótica utilizando ROS2. Cada parte aborda um cenário distinto de navegação em labirinto.

A Parte 1 assume conhecimento total do ambiente, enquanto a Parte 2 simula um robô explorador com sensores limitados que precisa construir o mapa sozinho. Ambas as partes utilizam algoritmos fundamentais de grafos (BFS e DFS), integração via ROS2 e comunicação baseada em serviços.

---

# Parte 1 — Navegação com Mapa Completo

## Objetivo

O objetivo da Parte 1 é permitir que o robô:

1. Obtenha o mapa completo do labirinto através do serviço `get_map`;
2. Converta esse mapa em uma matriz manipulável;
3. Localize sua posição inicial e a posição do alvo;
4. Calcule o caminho mais curto entre esses dois pontos utilizando um algoritmo de busca apropriado;
5. Execute o caminho movendo-se passo a passo através do serviço `move_command`.

A meta final é que o robô chegue ao alvo utilizando o menor caminho possível.

## Algoritmo: BFS (Breadth-First Search)

Na Parte 1 foi implementado o algoritmo BFS para encontrar o caminho mais curto. 
O BFS percorre o labirinto camada por camada, explorando todos os vizinhos de uma posição antes de avançar para o próximo nível da busca. Quando o alvo é encontrado, o caminho é reconstruído de trás para frente.

## Como executar a parte 1

```
ros2 run ponderada solution
```

## Maiores Dificuldades da Parte 1

- Garantir compatibilidade com o simulador no uso de services.
- Integrar o algoritmo de grafos com chamadas reais ao robô através do serviço `move_command`.


---

# Parte 2 — Exploração, Mapeamento e Busca Cega

## Objetivo

A Parte 2 simula um robô real com sensores limitados. O objetivo é:

1. Explorar o ambiente sem possuir o mapa completo.
2. Construir o mapa gradualmente enquanto se move.
3. Utilizar sensores que indicam apenas a presença de paredes ao redor.
4. Encontrar o alvo durante a exploração, mesmo sem saber previamente onde ele está.
5. Realizar backtracking para garantir que todas as regiões acessíveis sejam exploradas.



## Algoritmo: DFS (Depth-First Search) com Backtracking

Na Parte 2 o algoritmo central é o DFS. O DFS é adequado para exploração completa porque segue sempre adiante e retrocede apenas quando necessário.

## Como executar a parte 1

```
ros2 run ponderada2 main_solver
```


## Maiores Dificuldades da Parte 2

- Implementação de um mapa incremental consistente.
- Evitar loops durante a exploração.
- Sincronizar o backtracking com movimentação real via serviços.
- Representar corretamente as paredes percebidas pelos sensores.
- Criar uma estrutura robusta de visitação para o DFS.

## Limitações da Parte 2

- O algoritmo não escolhe o melhor caminho até o alvo.

---

# Conclusão

As duas partes da atividade abordam problemas de navegação com níveis crescentes de complexidade:

- A Parte 1 apresenta um cenário com informações completas, ideal para o uso de algoritmos ótimos como BFS.
- A Parte 2 se aproxima mais de um robô real, que precisa explorar, construir um mapa e tomar decisões com base em informações incompletas.

Este projeto demonstra o uso de ROS2 integrado a algoritmos clássicos de grafos em dois cenários com níveis diferentes de autonomia e informação disponível.

