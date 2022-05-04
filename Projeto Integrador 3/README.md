# Projeto Final

## Estação de Análise Eólica

### Introdução

Dados de velocidade média, velocidade de rajadas e direção predominante do vento com base em uma análise a longo prazo do ambiente em que a estação está inserida. Os dados podem ser coletados pelo usuário por meio de conexão USB (posteriormente será interessante enviar automaticamente estes dados diariamente para um aplicativo)
...

Envio de dados (dd;mm;aaaa;hh;mm) - 16bytes

Velocidade média poderá ser armazenada uma vez a cada dez minutos (144 vezes por dia) - uint8_t ou uint16_t
Por mais que seja armazenado apenas uma vez a cada dez minutos, os sinais estarão sendo recebidos em uma frequência maior para que seja possível identificar velocidade de rajadas, pontos fora da curva. Os valores de rajadas serão armazenados separadamente.

Direção dos ventos deve ter precisão entre 1 e 10°.

32 bytes 144 vezes por dia - 4.6kb por dia

### Componentes

Biruta - Direção do vento. Oito chaves, resistores variados para resultado de 16 resistências diferentes. Divisor de tensão para o recebimento do sinal no microcontrolador e medição por conversor analógico-digital. Reed Switch?

![image](https://user-images.githubusercontent.com/53865196/166604822-087266a0-b52b-4337-af3c-d1fbd82a1ba4.png)

Anemômetro - Medição da velocidade do vento. Pode ser calculado com um sensor indutivo ou com ímãs que irão gerar interrupções para cada giro do anemômetro. Problemas: Medição para baixas velocidades. Os picos de velocidade (rajadas) podem ser observados e separados por software. Tacômetro?

![image](https://user-images.githubusercontent.com/53865196/166604865-da31f7aa-95f9-4a9e-924b-1afea0b5e065.png)

Blue Pill (STM32F103) - Familiaridade com o micro, utilização em outra disciplina, possui ADC para a biruta, não terá problemas com o número de interrupções que o anemômetro irá gerar para velocidades elevadas. O baixo consumo do micro também ajudará a manter o circuito funcionando por longos períodos de tempo.

![image](https://user-images.githubusercontent.com/53865196/166605127-648ea539-50ae-4466-bd5a-064f075be871.png)

Bateria recarregável - Alimentar circuitos. Preocupação com baixo consumo para que o circuito possa se manter por longo período de tempo (possivelmente meses). Seria possível usar uma placa fotovoltaica para recarregar bateria (circuito a parte).

![image](https://user-images.githubusercontent.com/53865196/166605095-5a4deab4-6c92-440b-b298-d513ee7bb9cc.png)

Módulo Usb Host CH376 Serial - Comunicação. Arquiva os dados recebidos pelos sensores em arquivo CSV em uma mídia removível que pode ser facilmente acessada pelo usuário para avaliação dos dados.

![image](https://user-images.githubusercontent.com/53865196/166669733-8ed16903-c4da-438c-8fbb-41092166b848.png)

ESP8266 ESP01 (Opcional) - Comunicação. Envia diariamente os dados recebidos pelos sensores para um servidor.

![image](https://user-images.githubusercontent.com/53865196/166670863-807d234b-e54c-42fd-8791-b237bbb9558b.png)

### Apresentação de Resultados
Apresentação de gráficos para facilitar a visibilidade dos dados. Arquivo em CSV facilita a construção destes gráficos.

### Viabilidade Econômica
Estudar documentos em referências.

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
