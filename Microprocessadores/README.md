## Projeto Final

### Genius
Genius ou simon (como é conhecido em inglês) é um jogo que consiste em memorizar uma sequência apresentada por um brinquedo em forma de disco com botões coloridos que acendem e tocam sons. Após apresentar uma sequência aleatória, o brinquedo aguarda o jogador apertar os botões na mesma ordem. Caso ela seja incorreta, o genius dispara uma sequência de luzes e sons indicando que o jogador perdeu e, caso seja correta, o genius apresenta a mesma sequência porém desta vez com um botão aleatório a mais para ser memorizado. O jogo possui um número finito de repetições para que o jogador consiga vencer, resultando em uma sequência de luzes e sons que indicam a vitória.

### Requisitos e Informações
O jogo foi desenvolvido para a unidade curricular de microprocessadores, lecionada pelo professor Hugo Marcondes do Instituto Federal de Santa Catarina (IFSC) e utilizamos o simulador MARS e a linguagem MIPS. O jogo deveria ter a dificuldade configurável por dois parâmetros: o número de repetições para se vencer o jogo e a velocidade com que as repetições são apresentadas: o tempo de duração da luz e do som. A entrada de dados foi configurada para funcionar com as teclas 7, 9, 1 e 3 do teclado numérico, que correspondem às cores verde, vermelho, amarelo e azul, respectivamente.

### Código
O código foi divido em diversos macros e procedimentos para que se tornasse mais limpo e compreensível. Alguns dados como o tempo de repetição base de cada pulso luminoso em caso de vitória e derrota e as cores de cada pulso foram colocados no início do código para que se tornem mais facilmente editáveis. O código possui também o tratamento de erros em seu final para que, no pior dos casos, encerre o programa e apresente o código do erro que iniciou o processo.
