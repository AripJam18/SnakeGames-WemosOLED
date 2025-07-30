#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Pin tombol ---
#define UP_BTN    D5
#define DOWN_BTN  D6
#define LEFT_BTN  D7
#define RIGHT_BTN D3
#define BUZZER_PIN D4

// --- Game config ---
const int cellSize = 4;
const int gameX = 4;
const int gameY = 20;
const int gameWidth = 120;
const int gameHeight = 40;

const int maxLength = 64;
int snakeX[maxLength];
int snakeY[maxLength];
int length = 1;

int dirX = cellSize;
int dirY = 0;

int foodX = 40;
int foodY = 40;

int score = 0;
unsigned long startTime = 0;

void setup() {
  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  snakeX[0] = 8;
  snakeY[0] = 24;
  length = 1;
  spawnFood();
  startTime = millis();
}

void loop() {
  handleInput();

  // Geser badan ular
  for (int i = length - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Gerakkan kepala
  snakeX[0] += dirX;
  snakeY[0] += dirY;

  // Cek tabrak dinding
  if (snakeX[0] < gameX || snakeX[0] >= gameX + gameWidth ||
      snakeY[0] < gameY || snakeY[0] >= gameY + gameHeight) {
    gameOver();
    return;
  }

  // Cek tabrak diri sendiri
  for (int i = 1; i < length; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver();
      return;
    }
  }

  // Cek makan
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (length < maxLength) length++;
    score++;
    spawnFood();
    beep(50);
  }

  drawScreen();
  delay(200); // kecepatan game
}

void handleInput() {
  if (digitalRead(UP_BTN) == LOW && dirY == 0) {
    dirX = 0; dirY = -cellSize;
  }
  if (digitalRead(DOWN_BTN) == LOW && dirY == 0) {
    dirX = 0; dirY = cellSize;
  }
  if (digitalRead(LEFT_BTN) == LOW && dirX == 0) {
    dirX = -cellSize; dirY = 0;
  }
  if (digitalRead(RIGHT_BTN) == LOW && dirX == 0) {
    dirX = cellSize; dirY = 0;
  }
}

void spawnFood() {
  foodX = gameX + (random(gameWidth / cellSize)) * cellSize;
  foodY = gameY + (random(gameHeight / cellSize)) * cellSize;
}

void drawScreen() {
  display.clearDisplay();

  // Score dan time
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);
  display.setCursor(80, 0);
  display.print("Time: ");
  display.print((millis() - startTime) / 1000);

  // Kotak game
  display.drawRect(gameX - 1, gameY - 1, gameWidth + 2, gameHeight + 2, SSD1306_WHITE);

  // Ular
  for (int i = 0; i < length; i++) {
    display.fillRect(snakeX[i], snakeY[i], cellSize, cellSize, SSD1306_WHITE);
  }

  // Makanan
  display.fillRect(foodX, foodY, cellSize, cellSize, SSD1306_WHITE);

  display.display();
}

void beep(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

void gameOver() {
  for (int i = 0; i < 3; i++) {
    beep(100);
    delay(100);
  }

  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("Game Over!");
  display.setCursor(20, 35);
  display.print("Score: ");
  display.print(score);
  display.display();
  while (1); // stop di game over
}
