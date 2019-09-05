#include <IRremote.h>
#include <LiquidCrystal.h>
#include <dht.h>

LiquidCrystal lcd(2, 4, 5, 6, 7, 9);
const int RECV_PIN = 10;
int Button_Pin = A0;
int Buzzer = A1;
int Red_LED = A3;
int Green_LED = A2;
boolean flag = true;

IRrecv irrecv(RECV_PIN);
decode_results results;
dht DHT;
#define DHT11_PIN 8

void setup()
{
	Serial.begin(9600);

	pinMode(Button_Pin, INPUT_PULLUP);
	pinMode(Buzzer, OUTPUT);
	pinMode(Green_LED, OUTPUT);
	digitalWrite(Green_LED, HIGH);
	pinMode(Red_LED, OUTPUT);
	digitalWrite(Red_LED, LOW);
	digitalWrite(Buzzer, HIGH);
	irrecv.enableIRIn();
	// irrecv.blink13(true);
	lcd.begin(16, 2);
}

void loop()
{
	// unsigned long currentMillis = millis();
	if (analogRead(Button_Pin) < 50)
	{
		digitalWrite(Red_LED, !digitalRead(Red_LED));
		digitalWrite(Green_LED, !digitalRead(Green_LED));
		flag = !flag;
		delay(200);
		// while (analogRead(Button_Pin) < 50);
	}
	if (irrecv.decode(& results) && (flag == false))
	{
		digitalWrite(Red_LED, HIGH);
		Serial.println(results.value, HEX);
		lcd.setCursor(0, 0);
		irrecv.resume();
		lcd.print("IR=");
		lcd.print(results.value, HEX);
		delay(300); // 300ms can testing different IRcode in one press
		irrecv.decode(& results);
		lcd.setCursor(0, 1);
		irrecv.resume();
		lcd.print("IR=");
		lcd.print(results.value, HEX);
		// irsend.sendNEC(0xAA5511EE, 32);
		//delay(2000);
		// digitalWrite(Red_LED, LOW);
		
		while (analogRead(Button_Pin)>1000);
		
		lcd.clear();
	}
	else
	{
		int chk = DHT.read11(DHT11_PIN);
		lcd.setCursor(0, 0);
		lcd.print("Temp: ");
		lcd.print(DHT.temperature);
		lcd.print((char) 223);
		lcd.print("C");
		// lcd.print(flag);
		lcd.setCursor(0, 1);
		lcd.print("Humidity: ");
		lcd.print(DHT.humidity);
		lcd.print("%");
		// if (currentMillis - previousMillis >= interval)
		// {
		// previousMillis = currentMillis;
		delay(2000); // 1s make the display shown correct otherwise -999 will be shown in LCD
		lcd.clear();
		// }
	}
}
