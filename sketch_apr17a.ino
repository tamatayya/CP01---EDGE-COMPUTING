// CHAMA AS FUNCOES DO LCD
#include <LiquidCrystal.h>
//CONFIGURA O LCD
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

//CONFIGURANDO OS DESENHINHOS
byte sorriso[] = {
  B00000,
  B00000,
  B00000,
  B11011,
  B00000,
  B10001,
  B01110,
  B00000
};

byte vazio[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

//SETANDO AS CONEXOES
  const int ldr = A0;
  const int led_vermelho = 7;
  const int led_amarelo = 8;
  const int led_verde = 9;
  const int buzzer = 6;

//CONFIGURANDO AS VARIAVEIS DE ESTADO
  int estadoAnterior = -1;
  int luminosidadeAnterior = -1;
  unsigned long tempoFimAlerta = 0;   // guarda quando o alerta terminou
  bool aguardandoRepeticao = false;   // flag para saber se deve repetir


void setup()
{
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(3,0);
  lcd.print("Asia.dev");
  lcd.createChar(0, sorriso);
  lcd.createChar(2, vazio);
  lcd.setCursor(12, 0);
  lcd.write(byte(0));
  lcd.setCursor(0,1);
  lcd.print("Seja bem-vindo!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Iniciando...");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  vinheria();
  digitalWrite(led_verde, HIGH);
}

void loop(){
  
  int ldrStatus = analogRead(ldr);
  int luminosidade = map(ldrStatus, 0, 588, 0, 100);
  
  Serial.println(ldrStatus);
  porcentagem(luminosidade);
  
  if (luminosidade < 20) {
    aguardandoRepeticao = false;  // cancela repetição se saiu do alerta
    if (estadoAnterior != 0) {
      estadoAnterior = 0;
      seguro();
    }
  } else if (luminosidade >= 20 && luminosidade < 60) {
    if (estadoAnterior != 1) {
      estadoAnterior = 1;
      alerta();
    }

    // VERIFICA SE JÁ PASSARAM 3 SEGUNDOS DESDE O FIM DO ALERTA
    if (aguardandoRepeticao && millis() - tempoFimAlerta >= 3000) {
      alerta();
    }

  } else if (luminosidade >= 60) {
    aguardandoRepeticao = false;  // cancela repetição se saiu do alerta
    if (estadoAnterior != 2) {
      estadoAnterior = 2;
      perigo();
    }
      digitalWrite(led_vermelho, HIGH);
      tone(6, 3000, 400);
      delay(100);
      digitalWrite(led_vermelho, LOW);
      tone(6, 2000, 400);
      delay(100);
  }
}


void vinheria(){
  lcd.print("Vinhos Asia.dev");
  lcd.setCursor(7,1);
  lcd.print("luz: ");
}

void alerta(){
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  lcd.setCursor(0,1);
  lcd.print("alerta");
  for (int i=1; i<6; i++){
    digitalWrite(led_amarelo, HIGH);
    tone(6, 1000, 300);
    delay(300);
    digitalWrite(led_amarelo, LOW);
    tone(6, 600, 300);
    delay(300);
  }
  digitalWrite(led_amarelo, HIGH);

  // APÓS O BUZZER, REGISTRA O TEMPO E ATIVA A FLAG DE REPETIÇÃO
  tempoFimAlerta = millis();
  aguardandoRepeticao = true;
}

void seguro(){
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_verde, HIGH);
  lcd.setCursor(0,1);
  lcd.print("seguro");
}

void perigo(){
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarelo, LOW);
  lcd.setCursor(0,1);
  lcd.print("perigo");
}

void porcentagem(int luminosidade){
  if (luminosidade == luminosidadeAnterior) return;
  luminosidadeAnterior = luminosidade;
    
  lcd.setCursor(15,1);
  lcd.write(byte(2));
  lcd.setCursor(14,1);
  lcd.write(byte(2));
  lcd.setCursor(13,1);
  lcd.write(byte(2));
  lcd.setCursor(12,1);
  lcd.print(luminosidade);
  lcd.print("%");
}