# Projeto Final

## Estação de Análise Eólica

### Sumário
1. [Introdução](#introdução)
2. [Requisitos de projeto](#requisitos-de-projeto)
3. [Design](#design)
4. [Implementação](#implementação)
5. [Resultados](#resultados)
6. [Considerações Finais](#considerações-finais)
7. [Referências](#referências)

### Introdução

O constante avanço de meios de produção de energia traz consigo 

### Requisitos de projeto

Dados de velocidade média, velocidade de rajadas e direção predominante do vento com base em uma análise a longo prazo do ambiente em que a estação está inserida. Os dados podem ser coletados pelo usuário por meio de conexão USB (posteriormente será interessante enviar automaticamente estes dados diariamente para um aplicativo)
...
A velocidade média deverá ser armazenada uma vez a cada dez minutos, resultando em 144 medições de velocidade diárias. A velocidade dos ventos durante tempestades pode chegar a 25,1 m/s, portanto este dado será de 8bits, resultando em 1,152kb por dia.
Por mais que seja armazenado apenas uma vez a cada dez minutos, os sinais estarão sendo recebidos em uma frequência maior para que seja possível identificar velocidade de rajadas, pontos fora da curva. Os valores de rajadas serão armazenados separadamente.
A direção dos ventos medida pela biruta deverá ter precisão entre 10 e 15°.
Com base na necessidade prevista de armazenamento de dados até que seja possível se comunicar com o usuário, o projeto deverá ter capacidade de armazenamento suficiente para cerca de um mês.
Os dados serão enviados em um modelo (dd;mm;aaaa;hh;mm-vel-dir)


### Design

Biruta - Será usado para medição de direção dos ventos. Oito sensores magnéticos já seriam viáveis para uma medição com precisão de 22.5°, porém para uma maior precisão sem ter que dobrar a quantidade de sensores. 

Anemômetro - Usado para medição da velocidade do vento. Apenas um sensor de efeito Hall é capaz de realizar a medição de velocidade necessária para o projeto. O cálculo por software deve também considerar o sentido do vento para avaliar a velocidade real do vento e não apenas a velocidade de giro do protótipo.

ESP32 - Possui suporte para conexão bluetooth que será utilizada no desenvolvimento do projeto. Além disso, atende todas as necessidades de processamento.

Bateria recarregável - Usada para alimentação dos circuitos. Preocupação com baixo consumo para que o circuito possa se manter por longo período de tempo (possivelmente meses). Seria possível usar uma placa fotovoltaica para recarregar bateria (circuito a parte).

Memória Flash - Armazenamento de dados fornecidos pelos sensores. Ao enviar os dados por bluetooth, os dados são apagados da memória flash. Uma memória de 32M já é o suficiente para suportar os dados gerados por mais de 1 mês.

### Implementação
### Resultados
### Considerações Finais
### Referências
Esta sessão será organizada e os documentos deverão ser referenciados corretamente

[A história da produção de energia](https://www.quantumengenharia.net.br/historia-da-producao-de-energia-sustentabilidade/)

[Estação meteorológica](http://wiki.foz.ifpr.edu.br/wiki/index.php/Estacao_Meteorologica)

[Variáveis Meteorologicas](https://content.meteoblue.com/pt/especificacoes/variaveis-meteorologicas/vento#:~:text=Para%20a%20velocidade%20do%20vento,1%20kn%20%3D%201.852%20km%2Fh)

[Medição de Velocidade do vento](https://www.climadeensinar.com.br/post/2016/09/08/como-%C3%A9-medida-a-velocidade-do-vento)

[Windytips](https://www.windytips.com/)

[Brazilian extreme wind climate](https://lume.ufrgs.br/bitstream/handle/10183/198303/001099204.pdf?sequence=1&isAllowed=y)

[Projeto Conceitual e Análise de Viabilidade Econômica de Unidade de Geração de Energia Elétrica Eólica na Lagoa dos Patos](https://ecen.com/eee83/eee83p/viabilidade_energia_eolica.htm)

[ENERGIA EÓLICA: análise da viabilidade econômico-financeira dos leilões de energia da Agência Nacional de Energia Elétrica](https://engemausp.submissao.com.br/22/arquivos/559.pdf)

[Energia Eólica: Viabilidade Técnica e Econômico-Financeira](https://www.monografias.ufop.br/bitstream/35400000/208/1/MONOGRAFIA_EnergiaE%C3%B3licaViabilidade.pdf)

[Estudo de viabilidade Econômica para a implantação de uma fonte de energia renovável em uma grande consumidore de grande porte](http://repositorio.utfpr.edu.br/jspui/bitstream/1/12581/1/viabilidadeimplanta%C3%A7%C3%A3oenergiarenov%C3%A1vel.pdf)

https://capsistema.com.br/index.php/2020/06/02/conectando-o-esp8266-ao-stm32f103c8-criando-um-servidor-da-web/
