#include <LiquidCrystal_I2C.h>

int totalColumns = 16;
int totalRows = 2;

LiquidCrystal_I2C lcd(0x3F, totalColumns, totalRows);

const int go_but = 2;
const int stopp_but = 3;

int state_go = 0;
int state_stopp = 0;

int gotrue = false;

byte go[8] = {
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b10100,
  0b00110,
  0b01001,
  0b10001,
};
byte stopp[8] = {
  0b00010,
  0b00111,
  0b00111,
  0b10111,
  0b10111,
  0b11111,
  0b11111,
  0b01110,
};

void setup() {
  lcd.init();
  lcd.backlight(); // use to turn on and turn off LCD back light
  lcd.createChar(0, go);
  lcd.createChar(1, stopp);

  pinMode(go_but, INPUT);
  pinMode(stopp_but, INPUT);
}

void loop() {
  while (true) {
    
    lcd.setCursor(0,0);
    lcd.write(0);
    
  }
}
