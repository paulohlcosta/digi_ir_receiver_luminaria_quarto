/*  aprovado
 *  
 *  Funcionalidades
 *  Recebe infra-vermelho
 *  Controla saida para alimentação de LEDs
 *  
 */

#define IRpin_PIN PINB // ATTiny85 had Port B pins
#define IRpin 2
#define saida 0

#define MAXPULSE    5000  // the maximum pulse we'll listen for - 5 milliseconds 
#define NUMPULSES    50   // max IR pulse pairs to sample
#define RESOLUTION    2   // time between IR measurements

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse
uint16_t currentpulse = 0;      // index for pulses we're storing
uint32_t irCode = 0;
uint32_t irCodeLast = 0;
unsigned long lastPress = 0;

 //----------------------------------------- CODIGOS CONTROLE SAMSUNG
#define IR_MUTE  4164434947
#define IR_VOLUP 4164433927 
#define IR_VOLDN 4164432907 
#define IR_LEFT  4164430230 
#define IR_RIGHT 4164424110
#define IR_UP    4164420030 
#define IR_DOWN  4164428190
#define IR_SOURC 4164427807
#define IR_POWER 4164423727

#define saida 0 //---- I2C SDA, PWM

boolean estado = HIGH;          // flag para controlar LEDs
boolean toggle_pir = HIGH;       // flag para ativar leitura do PIR
int brilho = 0;

/***************************************************/
void setup() {
  pinMode(IRpin, INPUT);
  pinMode(saida, OUTPUT);
  digitalWrite(saida, HIGH);
  pinMode(1, OUTPUT);       //DIGISPARK PIRATA LED = PINO 1
  digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(1, LOW);
  delay(500);
  digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(1, LOW);
  delay(500);
  digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(1, LOW);  
}


void fazer_nada() { }


uint16_t listenForIR() {  // IR receive code
  currentpulse = 0;
  while (1) {
    unsigned int highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length

    while (IRpin_PIN & _BV(IRpin)) { // got a high pulse
      highpulse++;
      delayMicroseconds(RESOLUTION);
      if (((highpulse >= MAXPULSE) && (currentpulse != 0)) || currentpulse == NUMPULSES)
        return currentpulse;
      if (lowpulse >= MAXPULSE)
        delay(10);
    }
    pulses[currentpulse][0] = highpulse;

    while (! (IRpin_PIN & _BV(IRpin))) { // got a low pulse
      lowpulse++;
      delayMicroseconds(RESOLUTION);
      if (((lowpulse >= MAXPULSE) && (currentpulse != 0)) || currentpulse == NUMPULSES)
        return currentpulse;
      if (lowpulse >= MAXPULSE)
        delay(10);
    }
    pulses[currentpulse][1] = lowpulse;
    currentpulse++;
  }
}
