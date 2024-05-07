const int octavesCount = 2;
const int notesPerOctave = 7;
const int speakerPin = 52;

int notePins[octavesCount][notesPerOctave] = {
  {53, 51, 49, 47, 45, 43, 31},
  {35, 33, 31, 29, 27, 25, 23}
};

float frequencies[octavesCount][notesPerOctave] = {
  {130.81, 146.83, 164.81, 174.61, 196.00, 220.00, 246.94},
  {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88}
};

int level = 1;
int sequenceNotes;
int sequence[10];
int userInput[10];

int points = 0;
int streak = 0;

void setup() {
  for (int i = 0; i < octavesCount; i++) {
    for (int j = 0; j < notesPerOctave; j++) {
      pinMode(notePins[i][j], INPUT);
    }
  }

  pinMode(speakerPin, OUTPUT);

  generateSequence();
  playSequence();
}

void loop() {
  Serial.begin(9600);
  Serial.println("Play the keys: ");
  while (Serial.available() < sequenceNotes) {}
  for (int i = 0; i < sequenceNotes; i++) {
    userInput[i] = Serial.parseInt();
  }

  bool isCorrect = true;
  for (int i = 0; i < sequenceNotes; i++) {
    if (userInput[i] != sequence[i]) {
      isCorrect = false;
      break;
    }
  }

  if (isCorrect) {
    Serial.println("Congratulations!");
    streak++;
    points += streak;
    level++;
    Serial.print("Points: ");
    Serial.println(points);
    generateSequence();
    playSequence();
  } else {
    Serial.println("Wrong sequence. Try again.");
    streak = 0;
  }

  delay(2000);
}

void generateSequence() {
  sequenceNotes = level + 1;
  randomSeed(analogRead(0));
  for (int i = 0; i < sequenceNotes; i++) {
    sequence[i] = random(7, octavesCount * notesPerOctave);
  }
}

void playSequence() {
  for (int i = 0; i < sequenceNotes; i++) {
    playNote(sequence[i]);
    delay(1000);
    stopNote();
    delay(500);
  }
}

void playNote(int noteIndex) {
  for (int i = 0; i < octavesCount; i++) {
    tone(speakerPin, frequencies[i][noteIndex]);
  }
}

void stopNote() {
  noTone(speakerPin);
}
