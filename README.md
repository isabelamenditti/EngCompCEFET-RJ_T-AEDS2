# EngCompCEFET-RJ_T-AEDS2
All the projects and assignments I completed during college.

Trabalho realizado em linguagem C para a disciplina de Estruturas e Algoritmos de Dados 2.

Objetivo: Este trabalho prático consiste na implementação de um Sistema de Atendimento utilizando Árvore Rubro Negra.

Fila de Atendimento: Em um sistema de atendimento via chat, existe uma fila de espera para o cliente ser atendido, dado que uma determinada empresa prioriza os clientes mais antigos no atendimento e não pela ordem de chegada. Você deve implementar uma árvore rubro-negra para fazer o gerenciamento da fila de atendimento.

A empresa distingue os clientes pelo número de identificação, que é um número crescente, quanto mais antigo menor o número. Quando um novo cliente chega para pedir atendimento, este é inserido na árvore, e quando um analista de suporte termina um atendimento o algoritmo deve rapidamente remover esse cliente da árvore e selecionar o próximo cliente a ser atendido. É fornecido um exemplo de entrada e sua respectiva saída. A implementação fornecida pelo aluno deve seguir o exemplo de saída fornecido. A entrada é composta por uma sequência de números inteiros ≥ -1, onde -1 indica o atendimento de um cliente (remoção da ARN) e os demais são a solicitação de atendimento (inserção na ARN). A saída do programa deve ser a impressão da ARN em pré-ordem, com o valor do nó, espaço e sua cor. O programa deve fornecer saída exatamente igual a pedida pois dada um determinado arquivo de entrada 1.in, a saída do seu programa será comparada com a saída esperada em 1.out.

Operações: As seguintes operações de ARN devem ser implementadas:

Inserção: permite inserir uma pessoa na fila do sistema de atendimento.
Remoção: permite atender uma pessoa, ou seja, removê-la da fila do sistema de atendimento. Implemente a remoção pelo antecessor.
Busca: Permite verificar se uma pessoa ainda se encontra na fila de atendimento (através de número de identificação).
Impressão: Permite imprimir a fila de atendimento (árvore RN em pré-ordem).

Exemplo:

Entrada

30 -1 41 17 34 43 -1 24 25 49 32 36 -1

Saída

41 BLACK

34 RED

25 BLACK

32 RED

36 BLACK

43 BLACK

49 RED
