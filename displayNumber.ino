const byte a = 10;
const byte b = 13;
const byte c = 4;
const byte d = 6;
const byte e = 12;
const byte f = 11;
const byte g = 5;
const byte dp = 7;
const byte ONES = 3;
const byte TENS = 2;

byte state = 0;

byte segments[8] = {a, b, c, d, e, f, g, dp};

bool numbers[10][7] = {{1, 1, 1, 1, 1, 1, 0}, 
                       {0, 1, 1, 0, 0, 0, 0}, 
                       {1, 1, 0, 1, 1, 0, 1}, 
                       {1, 1, 1, 1, 0, 0, 1}, 
                       {0, 1, 1, 0, 0, 1, 1}, 
                       {1, 0, 1, 1, 0, 1, 1}, 
                       {1, 0, 1, 1, 1, 1, 1}, 
                       {1, 1, 1, 0, 0, 0, 0}, 
                       {1, 1, 1, 1, 1, 1, 1}, 
                       {1, 1, 1, 1, 0, 1, 1}};

void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

  pinMode(TENS, OUTPUT);
  pinMode(ONES, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  displayNumber(69);
  //delay(1);

}

int displayNumber(int number){
  byte ones = number % 10;
  byte tens = (number - ones) / 10;
  
  // tens place
  
  for(byte i = 0; i < 8; i++){
    digitalWrite(segments[i], 0);
  }
  
  delay(1);
  
  digitalWrite(ONES, 1);
  digitalWrite(TENS, 0);

  for(byte i = 0; i < 7; i++){
    digitalWrite(segments[i], numbers[tens][i] * 1);
  }

  delay(5);
  
  //ones place
  for(byte i = 0; i < 8; i++){
    digitalWrite(segments[i], 0);
  }
  
  digitalWrite(TENS, 1);
  digitalWrite(ONES, 0);

  for(byte i = 0; i < 7; i++){
    digitalWrite(segments[i], numbers[ones][i] * 1);
  }
  
  delay(5);

  for(byte i = 0; i < 7; i++){
    digitalWrite(segments[i], 0);
  }

  digitalWrite(TENS, 1);
  digitalWrite(ONES, 1);

  //delay(5);
  return 0;
}
