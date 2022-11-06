//CS12020 Assignment
//Zuzanna Ziolek [zuz2]
#define pot A0
#define red 5
#define orange 6
#define yellow 9
#define green 10
#define blue 11
const int arrLength = 46;
const int disCodeLength = 5;
const char alphabet[arrLength] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', ',', '\'', '?', '!', '+', '-', '*', '/', '='};
const char disCode[arrLength][disCodeLength] = {"^", "$$+", "$+^", "+$", "$", "$+$", "++", "$++", "$$", "+$$", "+$^", "$$^", "$+", "$^", "^+", "^$", "+^", "$^+", "$^$", "+", "^^", "++^", "++$", "+^$", "$^^", "+++", "^$$+", "^$$^", "^$+$", "^$++", "^$+^", "^$^$", "^$^+", "^$^^", "^+$$", "^$$$", "^$$", "^+$", "^$+", "^++", "^+^", "^^$", "^^+", "^^^", "^$^", "^+++^"};

void comMessageT(){
  const int disTime = 250;
  #ifdef debug1
    Serial.println("Entered T");
  #endif
  digitalWrite(5,HIGH);
  delay(disTime);  
  digitalWrite(6,HIGH);
  delay(disTime);
  digitalWrite(9,HIGH);
  delay(disTime);
  digitalWrite(11,HIGH);
  delay(disTime);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  digitalWrite(11,LOW);
}

void comMessageP(String decimalstr){
  int decimalInt;
  bool digit = true;
  #ifdef debug1
    Serial.println("Entered P");
  #endif
  //Check if the decimalstr is a digit
  for (int i = 0; i < 3; i++){
    if (digit == false) {
      break;
    }
    digit = isDigit(decimalstr[i]);
  }
  if (digit == true){
    decimalInt = decimalstr.toInt(); 
  }
  #ifdef debug1
    Serial.println(decimalInt);
  #endif
  if (decimalInt < 255){
    digitalWrite(11,decimalInt);
    delay(500);
    digitalWrite(11,0);
  }
}

void comMessageA(int sum){
  const int disTime = 125;
  String decimalstr;
  String strhundred;
  String strten;
  String strunit;
  int hundred;
  int ten;
  int unit;
  decimalstr = (String)sum;
  strhundred = decimalstr[0];
  strten = decimalstr[1];
  strunit = decimalstr[2];
  hundred = strhundred.toInt();
  ten = strten.toInt();
  unit = strunit.toInt();
  #ifdef debug1
    Serial.println("Entered A");
    Serial.println(hundred);
    Serial.println(ten);
    Serial.println(unit);
  #endif
  if (sum <= 999){
    for (int i = 0; i < 10; i++){
      if (hundred > 0){
        digitalWrite(5,HIGH);
        hundred -= 1;
      }
      if (ten > 0){
        digitalWrite(6,HIGH);
        ten -= 1;
     }
      if (unit > 0){
        digitalWrite(9,HIGH);
        unit -= 1;
      }
      delay(disTime);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(9,LOW);
      if (i+1 != 10){
        delay(disTime);
      }
    }
  }
  else {
    hundred = 9;
    ten = 9;
    unit = 9;
    digitalWrite(11,HIGH);
    for (int i = 0; i < 10; i++){
      if (hundred > 0){
        digitalWrite(5,HIGH);
        hundred -= 1;
      }
      if (ten > 0){
        digitalWrite(6,HIGH);
        ten -= 1;
     }
      if (unit > 0){
        digitalWrite(9,HIGH);
        unit -= 1;
      }
      delay(disTime);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(9,LOW);
      delay(disTime);
    }
    digitalWrite(11,LOW);
  }
}

int displaySpeed(){
  int disTime;
  int potTime;
  float temp;
  potTime = analogRead(pot);
  temp = (float)potTime / 1024.0;
  temp *= 480;
  temp += 20;
  disTime = round(temp);
  return disTime;
}
void disCodeLED(String text){
  int textLen = text.length();
  int disTime = displaySpeed(); 
  for (int i = 0; i < textLen; i++){
    if (text[i] == '^'){
      //1 time unit
      digitalWrite(11,HIGH);
      delay(disTime);
      digitalWrite(11,LOW);
    }
    else if (text[i] == '$'){
      //2 time units
      digitalWrite(11,HIGH);
      delay(disTime * 2);
      digitalWrite(11,LOW);
    }
    else if (text[i] == '+'){
      //4 time units
      digitalWrite(11,HIGH);
      delay(disTime * 4);
      digitalWrite(11,LOW);
    }
    else if (text[i] == '|'){
      //3 time units
      delay(disTime * 3);
    }
    else if (text[i] == ' '){
      //5 time units
      delay(disTime * 5);
    }
    if (text[i + 1] != '|' || text[i + 1] != ' ') {
      //between chars 1 time unit
      delay(disTime * 1);
    }   
  }
}

void asciiLED(String text){
  int textLen = text.length();
  int disTime = displaySpeed(); 
  for (int i = 0; i < textLen; i++){
    if (text[i] == '^'){
      //1 time unit
      digitalWrite(10,HIGH);
      delay(disTime);
      digitalWrite(10,LOW);
    }
    else if (text[i] == '$'){
      //2 time units
      digitalWrite(10,HIGH);
      delay(disTime * 2);
      digitalWrite(10,LOW);
    }
    else if (text[i] == '+'){
      //4 time units
      digitalWrite(10,HIGH);
      delay(disTime * 4);
      digitalWrite(10,LOW);
    }
    else if (text[i] == '|'){
      //3 time units
      delay(disTime * 3);
    }
    else if (text[i] == ' '){
      //5 time units
      delay(disTime * 5);
    }
    if (text[i + 1] != '|' || text[i + 1] != ' ') {
      //between chars 1 time unit
      delay(disTime * 1);
    }   
  }
}

char disCharToASCII(String letter) {
  char ASCIIchar;
#ifdef debug
  Serial.println("Enterred2A");
#endif
  for (int i = 0; i < arrLength; i++) {
    if (letter == disCode[i]) {
      ASCIIchar = alphabet[i];
      break;
    }
  }
#ifdef debug
  Serial.println(letter);
  Serial.println(ASCIIchar);
#endif
  return ASCIIchar;
}

String disCodeToText(String disCode, int start) {
  String temp;
  String text;
  int disCodeLen = disCode.length();
#ifdef debug
  Serial.println("Enterred2");
#endif
  for (int i = start; i < disCodeLen; i++) {
    if (i == disCodeLen - 1){
      if (disCode[i] == ' ') {
        text += disCharToASCII(temp);
        text += ' ';
      }
      else {
        temp += disCode[i];
        text += disCharToASCII(temp);
      }
    }
    else if (disCode[i] == '^' || disCode[i] == '$' || disCode[i] == '+') {
      temp += disCode[i];
    }
    else if (disCode[i] == '|') {
      text += disCharToASCII(temp);
      temp = "";
    }
    else if (disCode[i] == ' ') {
      text += disCharToASCII(temp);
      temp = "";
      text += " ";
    }
    #ifdef debug
      Serial.println(temp);
      Serial.println(text);
    #endif
  }
  return text;
}

char * ASCIIToDisCode(char letter) {
  int index = 0;
#ifdef debug
  Serial.println("Enterred1A");
#endif
  for (int i = 0; i < arrLength; i++) {
    if (toupper(letter) == alphabet[i]) {
      index = i;
      break;
    }
  }
#ifdef debug
  Serial.println(letter);
  Serial.println(disCode[index]);
#endif
  return disCode[index];
}

String textToDisCode(String text, int start) {
  String disCode;  
  int textLen = text.length();
#ifdef debug
  Serial.println("Enterred1");
#endif
  for (int i = start; i < textLen; i++) {
#ifdef debug
    Serial.println(text[i]);
#endif
    if (text[i] == ' ') {   
      disCode += " ";      
      continue;               
    }
    disCode += ASCIIToDisCode(text[i]);   
    if (i + 1 < textLen && text[i + 1] != ' ') {    
      disCode += "|";   
    }
  }
#ifdef debug
  Serial.println(disCode);
#endif
  return disCode;
}

void setup() {
  // put your setup code here, to run once:
  //Part 1 - Encoding and decoding DisCode code
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(orange,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
}

void loop() {
  //Part 1 - Encoding and decoding DisCode code
  String userText;
  String translatedText;
  int textLength;
  int start = 0;
  int disTrue = 0;
  char command;
  int comStart;
  while (!Serial.available()) {
    //Wait for a user to enter a value
    ;
  }
  userText = Serial.readString();
  textLength = userText.length();
#ifdef debug
  Serial.println(userText);
  Serial.println(textLength);
#endif
  //Check if the userText is ASCII or DisCode
  for (int i = 0; i < textLength; i++) {
    #ifdef debug
      Serial.println(userText[i]);
    #endif
    //Check if ASCII or DisCode has been found
    if (disTrue != 0) {
      #ifdef debug
        Serial.println("char has been found");
      #endif
      break;
    }
    //Check if there is a command at the beginning of the userText
    if (userText[i] == 'T'){
    #ifdef debug1
      Serial.println("T");
    #endif
      command = 'T';
      if (i+1 == textLength){
        break;
      }
      else {
        continue;
      }
    }
    else if (userText[i] == 'P'){
      #ifdef debug1
        Serial.println("P");
      #endif
      command = 'P';
      comStart = i;
      i += 4;
      if (i == textLength){
        break;
      }
    }
    else if (userText[i] == 'A'){
      #ifdef debug1
        Serial.println("A");
      #endif
      command = 'A';
      comStart = i;
      i += 7;
      if (i == textLength){
        break;
      } 
    }  
    //Check if the first character is not a space 
    if (userText[i] != ' ') {
      start = i;
      for (int z = 0; z < arrLength; z++) {
        //Check if the character is a DisCode character
        if (userText[i] == '^' || userText[i] == '$' || userText[i] == '+') {
          #ifdef debug
            Serial.println("disCode");
          #endif
          disTrue = 1;
          break;
        }
        //Check if the character is an ASCII character
        else if (userText[i] == alphabet[z]) {
          #ifdef debug
            Serial.println("ASCII");
          #endif
          disTrue = 2;
          break;
        }
      }
    }
    else if (userText[i] == ' '){
      #ifdef debug
        Serial.println("char is a space");
      #endif
      continue;
    }
  }
#ifdef debug
  Serial.println(disTrue);
#endif
  //Check if the userText is DisCode
  if (disTrue == 1) {
    translatedText = disCodeToText(userText, start);
    Serial.println(translatedText);
    asciiLED(userText);
  }
  //Check if the userText is ASCII
  else if (disTrue == 2) {
    translatedText = textToDisCode(userText, start);
    Serial.println(translatedText);
    disCodeLED(translatedText);
  }
  //Check if a command has been identified
  if (command == 'T'){
    comMessageT();
  }
  else if (command == 'P'){
    String decimalstr;
    decimalstr = userText[comStart + 1];
    decimalstr += userText[comStart + 2];
    decimalstr += userText[comStart + 3];
    #ifdef debug1
      Serial.println(decimalstr);
    #endif
    comMessageP(decimalstr);
  }
  else if (command == 'A'){
    String decimalstr1;
    String decimalstr2;
    int decimalInt1;
    int decimalInt2;
    int decimalSum;
    bool digit = true;
    decimalstr1 = userText[comStart + 1];
    decimalstr1 += userText[comStart + 2];
    decimalstr1 += userText[comStart + 3];
    for (int i = 0; i < 3; i++){
      if (digit == false) {
        break;
      }
      digit = isDigit(decimalstr1[i]);
    }
    if (digit == true){
      decimalInt1 = decimalstr1.toInt(); 
    }
    decimalstr2 = userText[comStart + 4];
    decimalstr2 += userText[comStart + 5];
    decimalstr2 += userText[comStart + 6];
    for (int i = 0; i < 3; i++){
      if (digit == false) {
        break;
      }
      digit = isDigit(decimalstr2[i]);
    }
    if (digit == true){
      decimalInt2 = decimalstr2.toInt(); 
    }
    decimalSum = decimalInt1 + decimalInt2;
    #ifdef debug1
      Serial.println(decimalstr1);
      Serial.println(decimalstr2);
      Serial.println(digit);
      Serial.println(decimalInt1);
      Serial.println(decimalInt2);
      Serial.println(decimalSum);
    #endif
    comMessageA(decimalSum);
  }
}
