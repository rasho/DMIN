#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

const int startButtonPin = 2;
const int resetButtonPin = 3;
const int relayTipButton = 4;
const int relayOutputPin = 12;
const int ledPin = 13;
const int ledDirektni = 11;
const int ledInverzni = 10;
const int ledBaterija = 9;

volatile unsigned long hh = 0;
volatile unsigned long mm = 0;
volatile unsigned long ss = 0;
volatile unsigned long ms = 0;
volatile bool timerStart = false;

bool isTimeDisplayed = false;

int relayState = 0;
int address = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(relayOutputPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledDirektni, OUTPUT);
  pinMode(ledInverzni, OUTPUT);
  pinMode(relayTipButton, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.print("DIGITALNI MJERAC");
  lcd.setCursor(0, 1);
  lcd.print("  INT. VREMENA  ");
  delay(1000);
  lcd.clear();
  lcd.print("POKRENI MJERENJE");
  lcd.setCursor(0, 1);
  lcd.print("   NA START");

  relayState = EEPROM.read(address);
  if (relayState == 1) {
    digitalWrite(ledDirektni, HIGH);
    digitalWrite(ledInverzni, LOW);
  } else {
    digitalWrite(ledDirektni, LOW);
    digitalWrite(ledInverzni, HIGH);
  }

  setupTimer();
}

void loop() {
  if (buttonPressed(startButtonPin)) {
    toggleTimer();
  }

  if (buttonPressed(resetButtonPin)) {
    resetTimer();
  }

  if (timerStart || isTimeDisplayed) {
    displayTime();
  }

  toggleRelayState();

  delay(5);
}

// Funkcija koja proverava da li je dugme pritisnuto
bool buttonPressed(int buttonPin) {
  static bool previousState = HIGH;
  bool currentState = digitalRead(buttonPin);

  if (currentState != previousState) {
    delay(20);
    currentState = digitalRead(buttonPin);
  }

  previousState = currentState;

  return (currentState == LOW);
}

// Funkcija za podešavanje tajmera
void setupTimer() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 1999;
  TCCR1B |= (1 << WGM12) | (1 << CS11);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

// Funkcija za promenu stanja tajmera
void toggleTimer() {
  timerStart = !timerStart;
  if (timerStart) {
    isTimeDisplayed = true;
    digitalWrite(relayOutputPin, (relayState == 1) ? LOW : HIGH);
    lcd.clear();
    lcd.print("MJERENJE VREMENA");
  } else {
    digitalWrite(relayOutputPin, (relayState == 1) ? HIGH : LOW);
    lcd.clear();
    lcd.print(" VRIJEME ODRADE");
  }
}

// Funkcija za resetovanje tajmera
void resetTimer() {
  hh = 0;
  mm = 0;
  ss = 0;
  ms = 0;
  timerStart = false;
  isTimeDisplayed = false;
  digitalWrite(relayOutputPin, LOW);
  lcd.clear();
  lcd.print("POKRENI MJERENJE");
  lcd.setCursor(0, 1);
  lcd.print("   NA START");
}

// Funkcija za prikazivanje vremena na LCD-u
void displayTime() {
  lcd.setCursor(2, 1);
  lcd.print(hh / 10);
  lcd.print(hh % 10);
  lcd.print(":");
  lcd.print(mm / 10);
  lcd.print(mm % 10);
  lcd.print(":");
  lcd.print(ss / 10);
  lcd.print(ss % 10);
  lcd.print(":");
  lcd.print(ms / 100);
  lcd.print((ms / 10) % 10);
  lcd.print(ms % 10);
}

// Funkcija za promenu stanja releja
void toggleRelayState() {
  if (buttonPressed(relayTipButton)) {
    relayState = !relayState;
    digitalWrite(relayOutputPin, relayState);

    EEPROM.update(address, relayState);
    delay(5);

    digitalWrite(ledDirektni, (relayState == 1) ? HIGH : LOW);
    digitalWrite(ledInverzni, (relayState == 1) ? LOW : HIGH);
  }
}

// Prekidna rutina za tajmer
ISR(TIMER1_COMPA_vect) {
  if (timerStart) {
    ms++;
    if (ms > 999) {
      ms = 0;
      ss++;
      if (ss > 59) {
        ss = 0;
        mm++;
        if (mm > 59) {
          mm = 0;
          hh++;
        }
      }
    }
  }
}
