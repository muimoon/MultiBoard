#include <IRremote.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }

  lcd.print("IR=");
  lcd.print(results.value, HEX);
  //lcd.println("IR=");
  //lcd.print(results.value, 32);

  delay(500);
  lcd.clear();
}


