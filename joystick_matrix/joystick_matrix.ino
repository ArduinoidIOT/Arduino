
#define max7219_reg_noop        0x00
#define max7219_reg_digit0      0x01
#define max7219_reg_digit1      0x02
#define max7219_reg_digit2      0x03
#define max7219_reg_digit3      0x04
#define max7219_reg_digit4      0x05
#define max7219_reg_digit5      0x06
#define max7219_reg_digit6      0x07
#define max7219_reg_digit7      0x08
#define max7219_reg_decodeMode  0x09
#define max7219_reg_intensity   0x0a
#define max7219_reg_scanLimit   0x0b
#define max7219_reg_shutdown    0x0c
#define max7219_reg_displayTest 0x0f

#define DEFAULT_MAX 800
#define DEFAULT_MIN 200
#define INTENSITY   0x02
#define DELAY   1000
#define TAIL_LEN 10
byte data = 11;
byte CLOCK = 12;
byte load = 8;
byte buffer[80];
int tail_len = 1;
byte tail[TAIL_LEN][2];
byte NUM = 1;

void setCommand(byte command, byte value)
{
  digitalWrite(load, LOW);
  for (int i = 0; i < NUM; i++)
  {
    shiftOut(data, CLOCK, MSBFIRST, command);
    shiftOut(data, CLOCK, MSBFIRST, value);
  }
  digitalWrite(load, LOW);
  digitalWrite(load, HIGH);
}
void clear() {
  setCommand(max7219_reg_digit7, 0);
  setCommand(max7219_reg_digit6, 0);
  setCommand(max7219_reg_digit5, 0);
  setCommand(max7219_reg_digit4, 0);
  setCommand(max7219_reg_digit3, 0);
  setCommand(max7219_reg_digit2, 0);
  setCommand(max7219_reg_digit1, 0);
  setCommand(max7219_reg_digit0, 0);
  for (int i = 0; i < 80; i++)
    buffer[i] = 0;
}


void setIntensity(byte intensity)
{
  setCommand(max7219_reg_intensity, intensity);
}



void setColumn(byte col, byte value)
{
  int n = col / 8;
  int c = col % 8;
  digitalWrite(load, LOW);
  for (int i = 0; i < NUM; i++)
  {
    if (i == n)
    {
      shiftOut(data, CLOCK, MSBFIRST, c + 1);
      shiftOut(data, CLOCK, MSBFIRST, value);
    }
    else
    {
      shiftOut(data, CLOCK, MSBFIRST, 0);
      shiftOut(data, CLOCK, MSBFIRST, 0);
    }
  }
  digitalWrite(load, LOW);
  digitalWrite(load, HIGH);

  buffer[col] = value;
}



void setDot(byte col, byte row, byte value)
{
  bitWrite(buffer[col], row, value);

  int n = col / 8;
  int c = col % 8;
  digitalWrite(load, LOW);
  for (int i = 0; i < NUM; i++)
  {
    if (i == n)
    {
      shiftOut(data, CLOCK, MSBFIRST, c + 1);
      shiftOut(data, CLOCK, MSBFIRST, buffer[col]);
    }
    else
    {
      shiftOut(data, CLOCK, MSBFIRST, 0);
      shiftOut(data, CLOCK, MSBFIRST, 0);
    }
  }
  digitalWrite(load, LOW);
  digitalWrite(load, HIGH);
}


void reload()
{
  for (int i = 0; i < 8; i++)
  {
    int col = i;
    digitalWrite(load, LOW);
    for (int j = 0; j < NUM; j++)
    {
      shiftOut(data, CLOCK, MSBFIRST, i + 1);
      shiftOut(data, CLOCK, MSBFIRST, buffer[col]);
      col += 8;
    }
    digitalWrite(load, LOW);
    digitalWrite(load, HIGH);
  }
}

void setup() {
  pinMode(data,  OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(load,  OUTPUT);
  digitalWrite(CLOCK, HIGH);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  //  attachInterrupt(digitalPinToInterrupt(2),set_Tail_Len,FALLING);
  setCommand(max7219_reg_scanLimit, 0x07);
  setCommand(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  setCommand(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  // no display test
  setCommand(max7219_reg_displayTest, 0x00);
  // empty registers, turn all LEDs off
  clear();
  setIntensity(INTENSITY);

  setDot(0, 0, 0);
  randomSeed(analogRead(A5));
}
byte dotX = 0;
byte dotY = 0;
int appleX = random(0, 7);
int appleY = random(0, 7);
void loop() {
  clear();
  setDot(appleX, appleY, 1);
  //  for (int i = 0; i < 8; i++) {
  //    if ( i % 2 == 0) {
  //      for (int j = 0; j < 8; j++) {
  //        setDot(i, j, 1);
  //        delay(DELAY);
  //      }
  //    }  else {
  //      for (int j = 8; j >= 0; --j) {
  //        setDot(i, j, 1);
  //        delay(DELAY);
  //
  //      }
  //    }
  //  }
  //setDot(0,1,0);
  int VRx = analogRead(A0);
  int VRy = analogRead(A1);

  if (VRx < DEFAULT_MAX && VRx > DEFAULT_MIN && VRy < DEFAULT_MAX && VRy > DEFAULT_MIN) {
    //Do nothing
    drawTail();
    delay(50);
    return;
  }
  if (VRx > DEFAULT_MAX) {
    dotX = (dotX + 1) % 8;
  } else if (VRx < DEFAULT_MIN) {
    dotX = (dotX + 7) % 8;
  }

  if (VRy > DEFAULT_MAX) {
    dotY = (dotY + 1) % 8;
  }
  else if (VRy < DEFAULT_MIN) {
    dotY = (dotY + 7) % 8;
  }
  //  setDot(dotX, dotY, 1);
  collect(dotX, dotY);
  drawTail();
  delay(100);
  if (/*random(0,100)>95*/dotX == appleX && dotY == appleY) {
    tail_len = (tail_len+1)%TAIL_LEN;
    collect(dotX, dotY);
    appleX = random(0, 7);
    appleY = random(0, 7);
  }
}

void collect(int x, int y) {
  for (int i = tail_len - 2; i >= 0; i--) {
    tail[i + 1][0] = tail[i][0];
    tail[i + 1][1] = tail[i][1];
  }

  tail[0][0] = x;
  tail[0][1] = y;

  //  for(int i = 0; i < tail_len; i++){
  //    setDot(tail[i][0], tail[i][1], 1);
  //  }
}

void drawTail() {
  for (int i = 0; i < tail_len; i++) {
    setDot(tail[i][0], tail[i][1], 1);
  }
}



