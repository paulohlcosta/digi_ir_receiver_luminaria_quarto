void verifica_ir(int value) {
  switch(value){                              //-----CONTROLE KEYES------------    
    case 3810010651: ligarleds(); break;      //value int for keypad button "1"         
    case 5316027: ligarleds(); break;       //value int for keypad button "2"     
    case 4001918335: ligarleds();  break;      //value int for keypad button "3"     
    case 1386468383: desligarleds(); break;       //value int for keypad button "4"     
    case 3622325019: desligarleds(); break;       //value int for keypad button "5"     
    case 553536955: desligarleds(); break;       //value int for keypad button "6"     
    case 2538093563: set_pir(); break;              //value int for keypad button "0"     
    case 3238126971:                      //value int for keypad button "*"     
      for (int i = 0; i < 60; i++) {
        digitalWrite(saida, !estado); delay(500);
        digitalWrite(saida, estado); delay(500);
      }
    case 1033561079: fade(25);            //value int for keypad button "volume up"
    case 10335619: fade(-50);             //value int for keypad button "volume down"
    case 2351064443: fazer_nada();       //value int for keypad button "left"
    case 71952287: fazer_nada();       //value int for keypad button "right"
//----------CONTROLE TV SAMSUNG---------
    case IR_VOLUP: fade(25);  break;
    case IR_VOLDN: fade(-50);  break;
    case IR_RIGHT: digitalWrite(saida, HIGH);  break;
    case IR_LEFT: digitalWrite(saida, LOW);  break;
    case IR_SOURC: ligarleds();  break;
    case IR_POWER: desligarleds();  break;  
    case IR_MUTE:   
      for (int i = 0; i < 60; i++) {
        digitalWrite(saida, !estado); delay(500);
        digitalWrite(saida, estado); delay(500);
      }
      break;
  } // close switch
} // close void




void loop() {
//function below decodes the received IR signal and store it in variable result.
  uint16_t numpulse = listenForIR(); // Wait for an IR Code

  // Process the pulses to get a single number representing code
  for (int i = 0; i < 32; i++) {
    irCode = irCode << 1;
    if ((pulses[i][0] * RESOLUTION) > 0 && (pulses[i][0] * RESOLUTION) < 500) {
      irCode |= 0;
    } else {
      irCode |= 1;
    }
  }
  int repeat = (irCode!=irCodeLast || (millis() - lastPress)>200);
  
  verifica_ir(irCode);
  
  irCodeLast = irCode;
  lastPress = millis();

// ----------------------

}
