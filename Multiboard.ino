#include <IRremote.h>
#include <LiquidCrystal.h>
#include <dht.h>


//IRsend irsend;

LiquidCrystal lcd(2, 4, 5, 6, 7, 9);

const int RECV_PIN = 10;
//const int SENDV_PIN = 3; //IRsend default output 3

IRrecv irrecv(RECV_PIN);
decode_results results;

dht DHT;
#define DHT11_PIN 8

void setup() {
  //Serial.begin(9600);
  //pinMode(SENDV_PIN, OUTPUT);

  irrecv.enableIRIn();
  //irrecv.blink13(true);
  lcd.begin(16, 2);
}

void loop() {

  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    lcd.setCursor(0, 0);
    irrecv.resume();
    lcd.print("IR=");
    lcd.print(results.value, HEX);
    delay(300);//300ms can testing different IRcode in one press
    irrecv.decode(&results);
    lcd.setCursor(0, 1);
    irrecv.resume();
    lcd.print("IR=");
    lcd.print(results.value, HEX);
    
    //irsend.sendNEC(0xAA5511EE, 32);
    
    delay(1000);
    lcd.clear();

  } else {

    int chk = DHT.read11(DHT11_PIN);
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    delay(2000);//2s make the display shown correct otherwise -999 will be shown in LCD
    lcd.clear();
  }
}


