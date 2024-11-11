#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int pos = 0;
int y = 1;
const int buttonPin = 13;
bool buttonPressed = false;
bool gameOver = false;
int score = 0;

byte anjing[8] = {
  B00000,
  B00010,
  B10011,
  B11111,
  B11110,
  B10010,
  B00000,
  B00000,
};

byte obstacle[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B01010,
  B01010,
  B00000,
  B00000,
};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, anjing);
  lcd.createChar(1, obstacle);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Bersihkan layar dan tampilkan kaktus
  lcd.clear();

  if (gameOver && digitalRead(buttonPin) == LOW) {
    gameOver = false;
    score = 0;
    pos = 0;
  }

  for(int i = 0; i < 4; i++) {
    int posObstacle = 3 + (i * 3);

    if (posObstacle == pos && y == 1) {
      gameOver = true;
      break;
    } else if (posObstacle == pos && y == 0) {
      score++;
    }

    lcd.setCursor(posObstacle, 1);
    lcd.write((byte)1);
  }

  if (gameOver) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("YAHH KALAHH BROKK");
    lcd.setCursor(0, 1);
    lcd.print("Point : ");
    lcd.setCursor(8, 1);
    lcd.print(score);
    delay(500);
    return;
  }
  
  // Cek apakah tombol ditekan untuk membuat dino melompat
  if (digitalRead(buttonPin) == LOW) {
    y = 0;
  } else {
    y = 1;
  }

  lcd.setCursor(14, 0);
  lcd.print(score);

  // Tampilkan dino di posisi tertentu
  lcd.setCursor(pos, y);
  lcd.write((byte)0);

  // Gerakkan dino ke kanan
  pos++;
  if (pos > 15) {
    pos = 0;
  }


  // Delay untuk mengontrol kecepatan animasi
  delay(500);
}