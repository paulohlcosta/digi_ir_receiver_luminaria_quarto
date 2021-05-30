void ligarleds() {
  Serial.println("ligarleds");
  for (int i = 0; i < 255; i++) {           //FADE IN DAS LUZES 255x10 MILISEGUNDOS
    analogWrite(saida, i);
    delay(10);
  }
  estado = HIGH;
  digitalWrite(saida, estado);
}

void desligarleds() {
  Serial.println("desligarleds");
  for (int i = 0; i < 255; i++) {           //FADE OUT DAS LUZES
    analogWrite(saida, (255-i));
    delay(10);
  }
  estado = LOW;
  digitalWrite(saida, estado);
}

void fade(int valor) {
  brilho = brilho+valor; 
  Serial.print("Brilho: "); Serial.println(brilho);
  if (0 < brilho < 255) { //------------------limite de brilho
    if (valor > 0) { // se o comando for para aumentar brilho
      for (int i = (brilho-valor); i < brilho; i++) {   //FADE IN DAS LUZES
        analogWrite(saida, i);
        delay(10);                
      }
    }
    if (valor < 0) { // se o comando for para diminuir
      for (int i = (brilho-valor); i > brilho; i--) {   //FADE OUT DAS LUZES
        analogWrite(saida, i);
        delay(10);                
      }
    }
  } else if (brilho >= 255) {  //-------limite de brilho, se atingindo piscar LED.
      estado = HIGH;
      digitalWrite(saida, !estado);
      delay(100);
      digitalWrite(saida, estado);
  } else {  //--------------------------limite de brilho, se atingindo piscar LED.
      estado = LOW;
      digitalWrite(saida, !estado);
      delay(100);
      digitalWrite(saida, estado);
  } // close if
}

void set_pir() {
  toggle_pir = !toggle_pir;
  digitalWrite(saida, !estado); //pisca para dar feedback
  delay(100);
  digitalWrite(saida, estado);
}
