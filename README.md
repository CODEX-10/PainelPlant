# PainelPlant

O projeto tem como objetivo a automatização de uma estufa de plantas de pequeno porte, na qual através dos sensores de luminosidade e distância, obter o controle do desenvolvimento da planta.

## Condições

- Com o sensor de luminosidade atingindo 900 lux, acenderá a iluminação artificial da estufa, simbolizada com o LED da placa (hardware) e o "quadrado" amarelo (software).
- A hidratação da planta é ativada por 10s a cada 30s, simbolizada com LED azul do RGB (hardware) e o "quadrado" azul (software).
- Quando a planta atingir 30cm, acenderá o LED verde do RGB (hardware) e o "quadrado" verde (software), se a planta não atingir os 30cm acenderá o LED vermelho do RGB (hardware) e o "quadrado" verde estará desabilitado (software).
- A leitura dos sensores serão atualizados na tela a cada 1s, na qual os valores aparecem nos seus respectivos blocos.

## Informações relevantes

- A planta deve ser hidratada em média a cada 4h, porém para melhor visualização, programei para hidratar a cada 30s.
- A pesquisa sobre a altura ideal da planta foi feita com base no alface, que atinge em média de 25cm à 30cm.
- Cada planta deve ter seus respectivos ajustes de altura, iluminação e hidratação.
