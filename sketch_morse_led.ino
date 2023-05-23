#include <string.h>

String alphanumToMorse(char val){
    String chars_alphanum[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", 
    "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", 
    "u", "v", "w", "x", "y", "z",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    String chars_morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
    "..", "...-", ".--", "-..-", "-.--", "--..",
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "-----."};
    
    int i=0, length; 
    length = sizeof(chars_alphanum) / sizeof(chars_alphanum[0]);
    
    for (i; i<length; i++){
        
        if (chars_alphanum[i][0] == tolower(val)){
            return chars_morse[i];
        }
    }
    return "";
}

// International Morse code is composed of five elements:
//    short mark, dot or dit (.): "dit duration" is one time unit long
//    long mark, dash or dah (-): three time units long
//    inter-element gap between the dits and dahs within a character: one dot duration or one unit long
//    short gap (between letters): three time units long
//    medium gap (between words): seven time units long (formerly five)

String textToMorse(const String& text){
  String textAsMorse;
  
  for (char val: text){
      if(isalpha(val) || isdigit(val)){
          String morse = alphanumToMorse(val);
          textAsMorse += morse + " ";
      }
      if(val == ' '){
          textAsMorse += "| ";
      }
  }
  
  return textAsMorse;
}

void morseToLed(String text){
  int duration = 200;

  for (char c : text){
    switch (c){
      case '.': 
        digitalWrite(LED_BUILTIN, HIGH);
        delay(duration);
        digitalWrite(LED_BUILTIN, LOW);
        delay(duration);
        break;
      case '-':
        digitalWrite(LED_BUILTIN, HIGH);
        delay(duration * 3);
        digitalWrite(LED_BUILTIN, LOW);
        delay(duration);
        break;
      case ' ':
        digitalWrite(LED_BUILTIN, LOW);
        delay(duration * 2);
        break;
      case '|':
        digitalWrite(LED_BUILTIN, LOW);
        delay(duration * 3);
        break;
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    // Wait for Serial port to connect
  }
}


void loop() {
  if (Serial.available()) {
    Serial.print("Type to send a message: ");
    String userInput = Serial.readStringUntil('\n');

    Serial.print("Your message: ");
    Serial.println(userInput);
    Serial.print("Your message in morse: ");
    Serial.println(textToMorse(userInput));
    Serial.println("begginning transmission");
    delay(500);
    morseToLed(textToMorse(userInput));
    Serial.println("message completed.\n");
  }
}
