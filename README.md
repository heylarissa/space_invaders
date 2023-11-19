# Space Invaders

## Requisitos

#### Inimigos
- [x] Devem existir três tipos de inimigos: 
    - [x] Fracos, não atiram caso exista uma entidade à sua frente ou se já existir um projétil na coluna, 
        - [x] causam um (1) de dano em obstáculos;  
    - [x] Intermediários, não atiram caso exista um projétil na coluna, 
        - [x] causam dois (2) de dano em obstáculos;  
    - [x] Fortes, podem atirar mesmo se existir até um projétil na coluna, 
        - [x] causam dois (2) de dano em obstáculos.  
- [x] A cada “rodada” apenas dois (2) inimigos podem atirar, dando preferência àqueles mais próximos à nave.
- [x] Os inimigos têm apenas uma vida, sendo esta removida uma vez que o mesmo é acertado por um projétil da nave. 

#### Nave
- [x] A nave pode se mover a direita e à esquerda, até as bordas do mapa 
- [x] A nave pode atirar caso não exista um projétil seu na coluna 
- [x] O projétil da nave causa um (1) de dano em obstáculos  
- [x] A nave inicia com três vidas, sendo que uma vida é removida cada vez que a mesma é acertada; 
- [x] e uma vida adicionada a cada fim de rodada (ao máximo de cinco vidas). 

#### Obstáculos
- [x] Obstáculos podem ser colocados entre a nave e os inimigos 
    - [x] Após receber dez (10) de dano, o obstáculo é removido 
    - [x] Você pode definir o número de obstáculos a partir do tamanho do tabuleiro (seu critério) 
    - [x] Os obstáculos não são reiniciados no início das rodadas; 

#### Rodadas
- [x] Uma vez que todos os inimigos forem mortos, uma nova rodada deve ser iniciada, carregando novos inimigos.

#### ETC
- [x] Deve existir um contador de pontos entre todas as rodadas (não reiniciado) 
    - [x] Um inimigo fraco morto atribui dez (10) pontos ao jogador; 
    - [x] Um inimigo intermediário morto garante vinte (20) pontos ao jogador; 
    - [x] Um inimigo forte morto garante quarenta (40) pontos ao jogador; 
 
## Requisitos relacionados à interface que devem ser implementados

#### Menu
- [x] Deve existir um menu principal com a funcionalidade de iniciar o jogo 

#### Entidades e Animações
- [x] Você deve utilizar uma imagem específica para...  
    - Nave; 
    - Inimigo fraco (duas imagens alternantes); 
    - Inimigo intermediário (duas imagens alternantes); 
    - Inimigo forte (duas imagens alternantes) 
- [x] Cada tipo de inimigo deve ter um projétil diferente  
- [x] Deve existir uma animação de explosão do inimigo e da nave, quando estes forem derrotados.  

#### Tela
- [x] O placar e a quantidade de vidas do jogador devem estar explícitos na tela 
- [x] Todas as funcionalidades descritas devem estar acessíveis e/ou visualizáveis através da interface gráfica 

## Lista de funcionalidades adicionais e opcionais
- [x] Inimigos se movem em bloco, para a direita e esquerda (15 pts) 
- [x] Projéteis da nave podem se chocar com os dos inimigos e se anularem (10 pts)   
- [ ] Inserção de colunas vazias entre os inimigos (5 pts)  
- [x] Progressão de dificuldade a cada nível (pelo menos 4 progressões) (10 pts) 
- [ ] Implementação de poderes bônus (dois tiros ou escudo) temporários para a nave (15 pts) ******* A cada x frames, dá os poderes
- [ ] Implementação de novos tipos de inimigos, incluindo novo modelo de ataque e nova imagem (5 pts cada, no máximo 2 novos)  
- [ ] Implementação de um inimigo que atira projéteis em diagonal e que ricocheteiam na borda do mapa (15 pts)  
- [ ] Salvar e carregar jogo salvo (10 pts)  
- [x] Nave inimiga (vermelha) com pontuação extra atrás de todos os inimigos [10 PONTOS] 
