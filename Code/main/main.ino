// // const int outputPins[] = {35, 37, 39, 41, 43, 45, 47, 49, 51, 53};
// // const int inputPins[] = {34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const int inputPins[] = {24, 26, 28, 30, 32, 34, 36, 38, 40};
const int outputPins[] = {25, 27, 29, 31, 33, 35, 37, 39, 41};

const int buzzerPin = 7;

const int n_pins = 9;

const int notes[] = {
  // 262, // C4
  294, // D4
  330, // E4
  349, // F4
  392, // G4
  440, // A4
  494, // B4
  523, // C5
  587, // D5
  659  // E5
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < n_pins; i++) {
    pinMode(outputPins[i], OUTPUT);
    pinMode(inputPins[i], INPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  int level = 1;
  while (level <= 10) {
    if (!playLevel(level)) {
      playLostSound();
      resetGame();
      return;
    }
    level++;
  }
  playWinGameSound();
  resetGame();
}

bool playLevel(int level) {
  int sequence[level];
  for (int i = 0; i < level; i++) {
    sequence[i] = random(0, n_pins);
  }

  for (int i = 0; i < level; i++) {
    digitalWrite(outputPins[sequence[i]], HIGH);
    tone(buzzerPin, notes[sequence[i]], 500);

    Serial.print("Output: pin ");
    // Serial.println(outputPins[sequence[i]]);
    Serial.println(sequence[i] + 1);
    delay(500);
    digitalWrite(outputPins[sequence[i]], LOW);
    delay(500);
  }

  for (int i = 0; i < level; i++) {
    int expectedInput = inputPins[sequence[i]];
    int expectedNote = sequence[i] + 1;
    while (digitalRead(expectedInput) == LOW) {}
    delay(50);
    tone(buzzerPin, notes[sequence[i]], 500);
    digitalWrite(outputPins[sequence[i]], HIGH);
    Serial.print("Input: pin ");
    Serial.println(expectedNote);
    delay(500);
    digitalWrite(outputPins[sequence[i]], LOW);
  }

  indicateSuccess(level);
  Serial.print("Level ");
  Serial.print(level);
  Serial.println(" completed");
  return true;
}

void indicateSuccess(int level) {
  for (int i = 0; i < level && i < n_pins; i++) {
    digitalWrite(outputPins[i * 2], HIGH);
  }
  playWinLevelSound();
  delay(2000);
  for (int i = 0; i < level && i < n_pins; i++) {
    digitalWrite(outputPins[i * 2], LOW);
  }
}

void playWinLevelSound() {
  tone(buzzerPin, 523, 200);  // C5
  delay(200);
  tone(buzzerPin, 659, 200);  // E5
  delay(200);
  tone(buzzerPin, 784, 200);  // G5
  delay(200);
}

void playWinGameSound() {
  tone(buzzerPin, 784, 300);  // G5
  delay(300);
  tone(buzzerPin, 880, 300);  // A5
  delay(300);
  tone(buzzerPin, 988, 300);  // B5
  delay(300);
  tone(buzzerPin, 1047, 600); // C6
  delay(600);
  Serial.println("Game won");
}

void playLostSound() {
  tone(buzzerPin, 220, 500);  // A3
  delay(500);
  tone(buzzerPin, 220, 500);  // A3
  delay(500);
  Serial.println("Game lost");
}

void resetGame() {
  for (int i = 0; i < n_pins; i++) {
    digitalWrite(outputPins[i], LOW);
  }
  Serial.println("Game reset");
}

///////////////
//////////////
////////////

// const int notes[] = {
//   262, // C4
//   294, // D4
//   330, // E4
//   349, // F4
//   392, // G4
//   440, // A4
//   494, // B4
//   523, // C5
//   587, // D5
//   659  // E5
// };

// void setup() {
//   Serial.begin(9600);
//   for (int i = 0; i < n_pins; i++) {
//     pinMode(outputPins[i], OUTPUT);
//     pinMode(inputPins[i], INPUT);
//   }
//   pinMode(buzzerPin, OUTPUT);
// }

// void loop() {
//   for (int i = 0; i < n_pins; i++) {
//     if (digitalRead(inputPins[i]) == HIGH) {
//       digitalWrite(outputPins[i], HIGH);
//       tone(buzzerPin, notes[i], 500);
//       Serial.print("Input: pin ");
//       // Serial.println(inputPins[i]);
//       Serial.println(i + 1);
//       Serial.print("Output: pin ");
//       // Serial.println(outputPins[i]);
//       Serial.println(i + 1);
//       delay(500);
//       digitalWrite(outputPins[i], LOW);
//       delay(500);
//     }
//   }
// }
