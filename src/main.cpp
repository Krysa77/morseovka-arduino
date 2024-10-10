#include <Arduino.h>
const int dotDuration = 70;
const int dashDuration = 250; 
const int pauseDuration = 300; 
const int ledPin = 12;

// (A-Z)
String morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
  "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

// (0-9)
String morseNumbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

String convertToMorse(String text);
void blinkMorse(String morseCode);

void setup() {
  // Nastavení LED pinu jako výstupu
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // LED je zhasnutá na začátku, tohle mi vubec nefunguje z nejakeho duvodu

  // Nastavení sériové komunikace
  Serial.begin(9600);
  Serial.println("Zadej text pro prevod na morseovku:");
}

void loop() {
  // Kontrola, zda je dostupný vstup ze Serial monitoru
  if (Serial.available() > 0) { // Čeká na vstup ze Serial monitoru
    String input = Serial.readStringUntil('\n');  // Přečte celý řádek po stisku Enteru, tohle mi taky nefunguje
    input.trim();  // Odstraní bílé znaky na začátku a konci
    if (input.length() > 0) {
      String morseTranslation = convertToMorse(input); // Převede vstup na morseovku
      Serial.println("Morseovka: " + morseTranslation); // Vypíše morseovku do Serial monitoru
      blinkMorse(morseTranslation);                    // Bliká LED podle morseovky
    }
  } else {
    digitalWrite(ledPin, LOW); // LED zůstane zhasnutá, pokud není žádný vstup
  }
}

String convertToMorse(String text) {
  text.toUpperCase();  // Převede text na velká písmena
  String morse = "";
  
  for (int i = 0; i < text.length(); i++) {
    char c = text.charAt(i);

    if (c >= 'A' && c <= 'Z') {
      morse += morseCode[c - 'A']; // Převede písmeno na morseovku
      morse += " ";  // Přidá mezeru mezi znaky
    } else if (c >= '0' && c <= '9') {
      morse += morseNumbers[c - '0']; // Převede číslo na morseovku
      morse += " ";  // Přidá mezeru mezi znaky
    } else if (c == ' ') {
      morse += "  ";  // Dvě mezery mezi slovy
    }
  }
  return morse;
}

// Funkce pro blikání LED podle morseovky
void blinkMorse(String morseCode) {
  for (int i = 0; i < morseCode.length(); i++) {
    char symbol = morseCode.charAt(i);

    if (symbol == '.') {
      digitalWrite(ledPin, HIGH);
      delay(dotDuration);  // Blik tečky
      digitalWrite(ledPin, LOW);
    } else if (symbol == '-') {
      digitalWrite(ledPin, HIGH);
      delay(dashDuration);  // Blik čárky
      digitalWrite(ledPin, LOW);
    }
    delay(pauseDuration);  // Pauza mezi tečkami/čárkami
  }
}
