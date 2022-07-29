# Projeto Final

## Estação de Análise Eólica

Discente: Victor Lompa Schwider

Docentes: Daniel Lohmann e Robinson Pizzio

Unidade Curricular: Projeto Integrador 3



------

### Sumário

1. [Introdução](#introdução)
2. [Requisitos de projeto](#requisitos-de-projeto)
3. [Design](#design)
4. [Implementação](#implementação)
5. [Resultados](#resultados)
6. [Considerações Finais](#considerações-finais)
7. [Referências](#referências)



------

### Introdução

A grande demanda energética das últimas décadas trás consigo a necessidade de constantes avanços nos meios de produção de energia. Sucessivas crises energéticas, como o apagão de 2001 no Brasil, ilustram esta necessidade e levantam algumas questões a serem discutidas. De acordo com uma [pesquisa](https://www.epe.gov.br/pt/abcdenergia/matriz-energetica-e-eletrica) de 2021 feito pela Empresa de Pesquisa Energética,  os combustíveis fósseis são responsáveis por cerca de 80% da matriz energética mundial, apesar dos grandes esforços dos últimos anos em pesquisa de meios de geração de energia com foco em energias renováveis.

Apesar do foco em sustentabilidade, esta modalidade de geração de energia está atrelada a um custo. Atualmente, a instalação de usinas eólicas é vantajosa? A ideia deste projeto é desenvolver uma estação para coleta de dados referentes a velocidade e direção do vento em determinado local para avaliar a possibilidade de instalação de usinas eólicas de pequeno ou grande porte tal como a expectativa de retorno financeiro para a mesma.



------

### Requisitos de projeto

Para que seja possível avaliar a viabilidade econômica do projeto de instalação de uma usina, é necessário avaliar o os dados de velocidade e direção e, com base em estudos previamente efetuados de aerogeradores reais, deverá ser possível mensurar seu retorno financeiro. Para tal, é necessário que seja desenvolvida uma aplicação capaz de receber dados, avaliá-los e apresentá-los ao usuário em forma de gráficos, por exemplo.

Os dados a seres avaliados pode estar em uma Database ou até mesmo em um arquivo .CSV salvo em diretório local, porém os dados coletados dos sensores que serão necessários devem ter como intermediador um microcontrolador pois precisarão ser tratados até que possam ser interpretados.

Como a ideia do projeto é uma estação que deve permanecer fixa em um local por um longo período de tempo, é ideal que esta possa suportar intemperes como calor, chuva e até mesmo o próprio vento. 

A capacidade de bateria do módulo deve ser suficiente para durar longos períodos de tempo. Para isso, pode ser usada uma bateria recarregável com uma placa fotovoltaica capaz de suportar o consumo energético do projeto. Caso a escolha seja de uma bateria, é necessário alertar o usuário caso o nível da bateria esteja abaixo do normal para que seja feita a manutenção ou, em último caso, alimentar o projeto com um longo cabo.



------

### Design

#### Anemômetro

Para a coleta de dados de velocidade, será utilizando um anemômetro e um sensor de efeito hall. Com alguns ímãs conectados ao anemômetro, que deve girar em velocidade similar à do vento, será possível obter uma certa quantidade de pulsos que varia conforme a velocidade. Esta quantidade pode ser lida por um microcontrolador e, com o valor construtivo de diâmetro do anemômetro, deve retornar o valor de velocidade.

O sensor hall escolhido foi o 3144, encontrado no módulo KY-003. A escolha se deve pela facilidade de obtenção no mercado nacional e simplicidade na utilização. Apesar disso, o sensor deve ser alimentação com tensão de 4.5V a 24V, o que impossibilita a utilização de um microcontrolado sem pinos de saída 5V sem que seja necessário uma fonte ou um conversor. Também é necessário tomar cuidado com o pino que irá receber o sinal de saída deste sensor visto que o mesmo pode não aceitar 5V.

#### Biruta

A coleta dos dados de direção do vento será feita com uma biruta, aparelho que deve rotacionar conforme a direção do vento. Inicialmente a medição seria feita com a utilização de Reed Switchs, chaves eletromecânicas que devem fechar na presença de um campo magnético. A leitura seria feita de forma similar à do anemômetro, o fechamento da chave gera um sinal positivo no pino de um microcontrolador e esta borda de subida é interpretada como um acréscimo no valor do ângulo. Observe que a precisão deste método depende do número de chaves, tornando-se uma solução que requer certo espaço físico e não possui uma confiabilidade adequada.

Um Encoder rotativo foi um segunda alternativa. Um disco com aberturas em ordem específica representando valores em binário pode ser utilizado em conjunto LED emissores e receptores de infravermelho para obter uma preciso baseada na ordem do valor em binário. Ao girar em torno do disco, os LEDs receptores são acionados conforme a sequência binária. O Encoder utilizado possui 8 linhas, traduzidas como 256 (2^8) valores possíveis de saída. É uma alternativa robusta e de simples aplicação porém pode possuir um tamanho elevado conforme se aumenta a precisão. Para que não fosse necessário realizar uma outra modelagem do protótipo levando em consideração o tamanho deste disco, buscou-se uma terceira alternativa.

Como última e definitiva alternativa, optou-se pela utilização de um módulo Encoder magnético de posição, o AS5600.  O módulo possuir cerca de 2cm² e resolução de 12bit, traduzido como uma precisão de 0.08°. Além disso,  pode simplificar o código por utilizar comunicação I2C. O módulo pode ser alimentado tanto em 3.3V quanto em 5V, o que não nos restringe quanto à escolha do microcontrolador a ser utilizado.

#### Análise de dados

Inicialmente, optou-se por salvar os dados obtidos pelos módulos mencionados acima em uma memória flash até que os dados sejam enviados por Bluetooth. Esta abordagem foi escolhida pensando-se na ideia de que a estação deverá ser fixada em algum local, preferencialmente de altitude elevada e, portanto, de difícil acesso. Neste caso, torna-se inviável a coleta dos dados por meio de cabos ou cartão SD.

O Bluetooth é uma alternativa simples que não exige necessariamente a utilização de banco de dados. A familiaridade com a ferramenta também foi um ponto a favor da escolha da mesma.

Com a escolha do microcontrolador que será discutido a seguir, a escolha da ferramenta passa a ser Bluetooth Low Energy (BLE). Os dados recebidos por um computador deveriam ser avaliados por software desenvolvido com a ferramenta QT Creator e apresentados ao usuário em forma de gráficos. Após uma série de pesquisas e erros recorrentes, a ferramenta deixou de ser uma opção pois possui pouca compatibilidade com o Windows e pouca documentação ou documentação descontinuada.

Com isso,  a escolha final para ferramenta de envio de dados para posterior análise passou a ser WiFi. Com isso, tornou-se necessário a utilização de um banco de dados, neste caso o Firebase DB.

#### Microcontrolador

Por possuir um módulo Bluetooth LE em sua própria placa de desenvolvimento, o ESP32-DevKit foi a primeira opção de microcontrolador, apesar da falta de familiaridade. A programação do mesmo foi feita com o Visual Studio Code e a extensão PlatformIO, que possui diversas bibliotecas próprias para ESP32, facilitando o processo de programação.

#### Consumo Energético

Para a alimentação das placas e módulos, optou-se pela utilização de uma bateria de 9V e uma módulo para converter a tensão da bateria em 5V e 3.3V, suficiente para resolver parcialmente problema do sensor de efeito hall e alimentar o ESP32. 



------

### Implementação

O protótipo foi feito com base em um [modelo](https://www.thingiverse.com/thing:5190383) encontrado [thingiverse](https://www.thingiverse.com/). Alguns ajustes foram necessários para encaixo dos módulos e melhor leitura dos ímãs. Para que consiga uma durabilidade melhor e resistência a intemperes, o protótipo deve ser impressão em ABS. Para uma prova de conceito, o protótipo impresso neste projeto foi em PLA, portanto não deverá ser testado em ambiente externo.

![WhatsApp Image 2022-07-27 at 01 19 46 (1)](https://user-images.githubusercontent.com/53865196/181165485-32a73740-831d-466e-b501-01485b0434cc.jpeg)


O projeto utiliza 4 rolamentos 624Z de 4mm x 13mm x 5mm e duas barras de metal. As barras de metal foram manufaturas com uma barra de diâmetro maior utilizando uma esmirilhadeira. A conexão das peças é feita com hachuras da própria peça. Algumas partes tiveram que ser coladas e/ou vedadas com epóxi para um melhor resultado.

Os footprints dos módulos utilizados no projeto não condizem com os da impressão, portanto tiveram de ser removidos para uma melhor fixação dos mesmos.

![WhatsApp Image 2022-07-27 at 01 19 45 (1)](https://user-images.githubusercontent.com/53865196/181165528-622bfb9f-0747-4227-a8df-2fb6849172e6.jpeg)


O circuito para utilização do sensor de efeito hall apresentado abaixo conta com um BC548 funcionando como chave. A saída possui um resistor de pull-up colocando o pino do ESP32 para 3.3V quando o transistor não está polarizado. Quando o sensor detecta um campo magnético forte o suficiente, apresenta 5V na sua saída, polarizando o transistor e, consequentemente, jogando GND na saída do pino do ESP.

A escolha dos ímãs é importante. Por mais que alguns deles funcionem ao testar o sensor dado a proximidade e a ausência de obstáculos, alguns deles podem não funcionar quando fixados no protótipo por serem fracos demais. Os ímas do dado projeto foram retirados de um fone de ouvido antigo e testados no protótipo para verificar sua usabilidade.

![Untitled Sketch 2_bb](https://user-images.githubusercontent.com/53865196/181165547-b9638bf8-c292-4eda-9352-11f571046838.jpg)


O módulo AS5600 pode ser conectado diretamente no ESP32 de maneira que SCL seja conectado ao pino GPIO22 e SDA seja conectado ao pino GPIO21. Os pinos DIR, GPO e OUT não foram necessários para esta aplicação. O pino OUT poderia ter sido utilizado para obter o valor por meio de um PWM. A alimentação utilizada em VCC foi de 3.3V, diretamente do pino de saída do ESP32.

![WhatsApp Image 2022-07-27 at 01 42 25](https://user-images.githubusercontent.com/53865196/181165562-1204e64a-5160-4a8f-bbc4-4cde04d7744a.jpeg)



------

### Código

O código do programa apresentado abaixo inclui a obtenção e tratamento dos dados provenientes dos sensores, obtenção do horário exato para referenciação dentro da Database e conexão e envio de dados para a Database. A biblioteca utilizada para leitura dos dados do módulo AS5600 podem ser encontradas nos arquivos do projeto.

O valor de velocidade é calculado a cada segundo e é acrescido num somatório para cálculo da média. Após 1 minuto, o somatório de velocidades resulta na média para o dado minuto e é enviado para o banco de dados junto do ângulo de direção da biruta e a velocidade de pico que é a maior velocidade adquirida no minuto.

O cálculo da velocidade do anemômetro é feito com base em suas características construtivas, resultando em um fator constante que pode ser utilizado para diminuir o tempo de processamento dos cálculos.

```C++
/* ESP32 Libraries */
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

/* C++ Libraries */
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

/* Firebase Libraries */
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

/* NTP Libraries */
#include <NTPClient.h>
#include <WiFiUdp.h>

/* Project Libraries */
#include "AS5600.h"

/* Firebase Defines */
#define DATABASE_URL "https://xxxxxxxxxxx.firebaseio.com/"
#define API_KEY "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define USER_EMAIL "xxxxxxxxx@gmail.com"
#define USER_PASSWORD "xxxxxxxxxxx"

/* NTP Defines */
#define dirstr  "Direction"
#define spdstr  "Speed"
#define peakstr "Peak"

/* Project Defines */
#define WIFI_SSID "xxxxxxx"            // Wifi Name
#define WIFI_PASSWORD "xxxxxxxxxxxxx"  // WiFi Password
#define LED 2                           // LED GPIO number
#define HALL 15                         // HAL GPIO number
#define USTOSEC 1000000                 // Convert timer factor to seconds 

/* Firebase DB Variables */
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;

/* NTP variables */
String formattedDate;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/* Project Variables */
AMS_5600 ams5600;
hw_timer_t *My_timer = NULL;
unsigned long int pulseCounter = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const float factor = 226.19467;
unsigned int avgCounter = 0;
float windDirection = 0;
float windSpeedAvg = 0;
float windSpeed = 0;
float windPeak = 0;
bool flag = 0;

// Anemometer speed calculus 
// Anemometer Radius = 3 cm
// Anemometer Circunference = 18.85 cm
// Anemometer Unitary pulse distance 6.283 cm (3 pulses per revolution)
// Anemometer Convertion to km/h = 36 -> ((cm / 100) / (miliseconds / 1000)) * 3.6
// Anemometer final factor = 226.19467

void IRAM_ATTR wifiTimer(){
  flag = 1;
}

void IRAM_ATTR pulseInterrupt(){
  pulseCounter++;
}

void setup()
{
  Serial.begin(115200);
  
  /* I2C Config*/
  Wire.begin();
  
  /* WIFI Config */
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);}

  /* Firebase DB Config*/
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5); 

  /* NTP Config */
  timeClient.begin();
  timeClient.setTimeOffset(-10800); // Brazil - GMT -3 
  while(!timeClient.update()){
    timeClient.forceUpdate();}

  /* Timers Config */
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &wifiTimer, true);
  timerAlarmWrite(My_timer, 60*USTOSEC, true); // Value in Seconds
  timerAlarmEnable(My_timer); 
  
  /* Sensor Hall Config */
  pinMode(HALL, INPUT);
  attachInterrupt(HALL, pulseInterrupt, FALLING);
}

void loop()
{ 
  
  // Get speed
  currentMillis = millis();
  if((currentMillis - previousMillis) > 1000){

    if (pulseCounter == 0){
      windSpeed = 0;}
    else {
      windSpeed = ((factor * pulseCounter) / ((currentMillis - previousMillis)));}

    windSpeedAvg += windSpeed;
    if(windSpeed > windPeak){
      windPeak = windSpeed;}

    avgCounter++;
    pulseCounter = 0;
    previousMillis = currentMillis;}

  
  if(flag == 1){

    // Get wind direction
    windDirection = ams5600.getRawAngle() * 0.087;

    // Calculate average wind speed
    windSpeedAvg = windSpeedAvg/avgCounter;
    
    // Save data on Firebase DB using wifi
    timeClient.update();
    formattedDate = timeClient.getFormattedDate();
    if (Firebase.ready()){      
      Firebase.setFloat(fbdo, (formattedDate+dirstr)  , windDirection);
      Firebase.setFloat(fbdo, (formattedDate+spdstr)  , windSpeedAvg);
      Firebase.setFloat(fbdo, (formattedDate+peakstr) , windPeak);}

    // Reset data to get new ones
    flag = 0;
    windSpeedAvg = 0;
    avgCounter = 0;
    windPeak = 0;
  }
}

```



------

### Análise de dados

Os dados na database são separados pela identificação da data e horário, onde cada um possui a direção no momento do envio, média de velocidade e o maior pico de velocidade no intervalo de obtenção dos dados. O valor de pico é identificado a cada segundo.


![Sem título](https://user-images.githubusercontent.com/53865196/181165618-43a49c92-6297-4766-9136-80ac9b9b36c5.jpg)

Os dados da database foram transformados em uma planilha do excel utilizando o [Flatly](https://flatly.io/scheduler), que permite ao usuário uma atualização da planilha com os dados de 6 em 6 horas. Com estes dados planificados, foi possível conectar a planilha gerada a uma outra planilha responsável pela análise e apresentação gráfica dos dados, pois a planilha atualizada periodicamente acabaria por apagar os gráficos gerados e cálculos obtidos. A planilha gerada é salva no onedrive, permitindo ao usuário o acesso remoto aos dados necessários para a análise da estação.


![flatly](https://user-images.githubusercontent.com/53865196/181691290-2ba38c29-4a14-4cb2-b1dc-7c9b44647d05.png)

Os dados de direção podem nos indicar a direção predominante do vento no determinado local ou indicar que o local pode apresentar variações repentinas na direção do vento que podem acabar por diminuir a eficiência de um possível aerogerador.


![Direction](https://user-images.githubusercontent.com/53865196/181690793-27a0aaef-d8cb-46cf-90ae-62cb1e2dd3a9.png)

Os dados de velocidade nos indicam se o aerogerador instalado será capaz de atuar na potência nominal, os limites de velocidade nominal e limite são dados que devem ser colocados pelo usuário conforme o aerogerador planejado. É ideal que os dados de velocidade estejam dentro da faixa delimitada pelas linha verde e linha vermelha, identificadas como velocidade nominal e limite, respectivamente.


![Speed](https://user-images.githubusercontent.com/53865196/181697413-846c310d-5b0d-4e7c-8c0a-eb7143565843.png)


### Resultados

A precisão dos sensores é satisfatória. O valor de ângulo varia um pouco mesmo com a biruta estável porém a variação é pequena. Os valores de velocidade são calculados com sucesso e, junto deles o valor de pico para um determinado intervalor de tempo.

O WiFi se mostrou ser uma ferramenta mais confiável do que o BLE visto que independe da distância com o usuário e possui maior compatibilidade com o sistema operacional em que o projeto foi desenvolvido (Windows).

O banco de dados permite armazenas todas as informações necessárias para análise de dados e possui um tempo de resposta satisfatório.






------

### Referências

A HISTÓRIA DA PRODUÇÃO DE ENERGIA, Quantum Engenharia 2017. Disponível em: https://www.quantumengenharia.net.br/historia-da-producao-de-energia-sustentabilidade/. Acesso em: 25 maio de 2022

Estacao Meteorologica, IFPR 2016. Disponível em: http://wiki.foz.ifpr.edu.br/wiki/index.php/Estacao_Meteorologica. Acesso em: 25 maio de 2022

Como é medida a velocidade do vento?, Clima de Ensinar 2016. Disponível em: https://www.climadeensinar.com.br/post/2016/09/08/como-%C3%A9-medida-a-velocidade-do-vento. Acesso em: 25 maio de 2022

Modelo Climático para Ventos Extremos no Brasil/Brazilian Extreme Wind Climate, Matthew Bruce Vallis 2020. Disponível em: https://www.windytips.com/. Acesso em: 25 maio de 2022

Projeto Conceitual e Análise de Viabilidade Econômica de Unidade de Geração de Energia Elétrica Eólica na Lagoa dos Patos - RS, Ernesto Augusto Garbe, 2011. Disponível em: https://ecen.com/eee83/eee83p/viabilidade_energia_eolica.htm. Acesso: 25 maio de 2022

Energia Eólica: Viabilidade Técnica e Econômico-Financeira, João Monlevade 2016. Disponível em: https://www.monografias.ufop.br/bitstream/35400000/208/1/MONOGRAFIA_EnergiaE%C3%B3licaViabilidade.pdf. Acesso em 25 maio de 2022

Getting Started with ESP32 Bluetooth Low Energy (BLE) on Arduino IDE.  Random Nerd Tutorials 2019. Disponível em: https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/. Acesso em: 25 maio de 2022

BLE C++ Guide.  Neil Kolban 2018. Disponível em: https://github.com/nkolban/esp32-snippets/blob/master/Documentation/BLE%20C%2B%2B%20Guide.pdf. Acesso em 01 junho de 2022

[Estudo de viabilidade Econômica para a implantação de uma fonte de energia renovável em uma grande consumidore de grande porte](http://repositorio.utfpr.edu.br/jspui/bitstream/1/12581/1/viabilidadeimplanta%C3%A7%C3%A3oenergiarenov%C3%A1vel.pdf)

https://capsistema.com.br/index.php/2020/06/02/conectando-o-esp8266-ao-stm32f103c8-criando-um-servidor-da-web/
