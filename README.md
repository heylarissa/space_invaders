# space_invaders

Programação orientada a evento  

https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace

## Requisitos

#### Inimigos
Devem existir três tipos de inimigos: - OK  
    - Fracos, não atiram caso exista uma entidade à sua frente ou se já existir um projétil na coluna, causam um (1) de dano em obstáculos;  
    - Intermediários, não atiram caso exista um projétil na coluna, causam dois (2) de dano em obstáculos;  
    - Fortes, podem atirar mesmo se existir até um projétil na coluna, causam dois (2) de dano em obstáculos.  
- [x] A cada “rodada” apenas dois (2) inimigos podem atirar, dando preferência àqueles mais próximos à nave. - OK  
- [ ] Os inimigos têm apenas uma vida, sendo esta removida uma vez que o mesmo é acertado por um projétil da nave. - OK  

#### Nave
- A nave pode se mover a direita e à esquerda, até as bordas do mapa - OK  
- A nave pode atirar caso não exista um projétil seu na coluna - OK  
- O projétil da nave causa um (1) de dano em obstáculos  
- A nave inicia com três vidas, sendo que uma vida é removida cada vez que a mesma é acertada; - OK  
    e uma vida adicionada a cada fim de rodada (ao máximo de cinco vidas). - OK  

#### Obstáculos
- Obstáculos podem ser colocados entre a nave e os inimigos - OK  
    - Após receber dez (10) de dano, o obstáculo é removido  
    - Você pode definir o número de obstáculos a partir do tamanho do tabuleiro (seu critério) - OK  
    - Os obstáculos não são reiniciados no início das rodadas; - OK  

#### Rodadas
- Uma vez que todos os inimigos forem mortos, uma nova rodada deve ser iniciada, carregando novos inimigos. - OK  

#### ETC
- Deve existir um contador de pontos entre todas as rodadas (não reiniciado) - OK  
    - Um inimigo fraco morto atribui dez (10) pontos ao jogador; - OK  
    - Um inimigo intermediário morto garante vinte (20) pontos ao jogador; - OK  
    - Um inimigo forte morto garante quarenta (40) pontos ao jogador; - OK  
 
## Requisitos relacionados à interface que devem ser implementados

#### Menu
- Deve existir um menu principal com a funcionalidade de iniciar o jogo - OK  

#### Entidades e Animações
- Você deve utilizar uma imagem específica para...  
    - Nave; - OK  
    - Inimigo fraco (duas imagens alternantes); - OK  
    - Inimigo intermediário (duas imagens alternantes); - OK  
    - Inimigo forte (duas imagens alternantes) - OK  
- Cada tipo de inimigo deve ter um projétil diferente  
- Deve existir uma animação de explosão do inimigo e da nave, quando estes forem derrotados.  

#### Tela
- O placar e a quantidade de vidas do jogador devem estar explícitos na tela - OK  
- Todas as funcionalidades descritas devem estar acessíveis e/ou visualizáveis através da interface gráfica - OK  

## Lista de funcionalidades adicionais e opcionais
- Inimigos se movem em bloco, para a direita e esquerda (15 pts) - OK  
- Projéteis da nave podem se chocar com os dos inimigos e se anularem (10 pts) ***********  
- Inserção de colunas vazias entre os inimigos (5 pts)  
- Progressão de dificuldade a cada nível (pelo menos 4 progressões) (10 pts) ***********  
- Implementação de poderes bônus (dois tiros ou escudo) temporários para a nave (15 pts)  
- Implementação de novos tipos de inimigos, incluindo novo modelo de ataque e nova imagem (5 pts cada, no máximo 2 novos)  
- Implementação de um inimigo que atira projéteis em diagonal e que ricocheteiam na borda do mapa (15 pts)  
- Salvar e carregar jogo salvo (10 pts) *****************  
- Nave inimiga (vermelha) com pontuação extra atrás de todos os inimigos [10 PONTOS] - meio OK *************  