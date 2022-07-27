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

A grande demanda energética das últimas décadas trás consigo a necessidade de constantes avanços nos meios de produção de energia. Sucessivas crises energéticas, como o apagão de 2001 no Brasil, ilustram esta necessidade e levantam algumas questões a serem discutidas. De acordo com uma [pesquisa](https://www.epe.gov.br/pt/abcdenergia/matriz-energetica-e-eletrica) de 2021 feito pela Empresa de Pesquisa Energética,  os combustíveis fósseis são responsáveis por cerca de 80% da matriz energética mundial, apesar dos grandes esforços dos últimos anos em pesquisa de meios de geração de energia com foco em energias renováveis.

Apesar do foco em sustentabilidade, esta modalidade de geração de energia está atrelada a um custo. Atualmente, a instalação de usinas eólicas é vantajosa? A ideia deste projeto é desenvolver uma estação para coleta de dados referentes a velocidade e direção do vento em determinado local para avaliar a possibilidade de instalação de usinas eólicas de pequeno ou grande porte tal como a expectativa de retorno financeiro para a mesma.

### Requisitos de projeto



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

### Código

O código do programa apresentado abaixo inclui a obtenção e tratamento dos dados provenientes dos sensores, obtenção do horário exato para referenciação dentro da Database e conexão e envio de dados para a Database. A biblioteca utilizada para leitura dos dados do módulo AS5600 podem ser encontradas nos arquivos do projeto.

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
#define DATABASE_URL "https://windstation-5f17d-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyAryL_5tPGzdpO0_CaSgIH3CEe4AnR42jw"
#define USER_EMAIL "titilompa@gmail.com"
#define USER_PASSWORD "DteXT53QeWtQ7WGkVKdN"

/* NTP Defines */
#define dirstr  "Direction"
#define spdstr  "Speed"
#define peakstr "Peak"

/* Project Defines */
#define WIFI_SSID "Schwider"            // Wifi Name
#define WIFI_PASSWORD "48991159652!!!"  // WiFi Password
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
  timerAlarmWrite(My_timer, 5*USTOSEC, true); // Value in Seconds
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

### Resultados

### Considerações Finais

### Referências

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
