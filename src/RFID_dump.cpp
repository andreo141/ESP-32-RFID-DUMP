
#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

#define RST_PIN         33          // Configurable, see typical pin layout above
#define SS_PIN          2         // Configurable, see typical pin layout above

#define SPI_CS	SS_PIN
#define SPI_MISO 4
#define SPI_MOSI 13
#define SPI_SCK 14

int rood = 15;
int groen = 23;


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin(SPI_SCK,SPI_MISO,SPI_MOSI,SS_PIN);			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
	
	pinMode(rood, OUTPUT);
	pinMode(groen, OUTPUT);
	digitalWrite(rood, LOW);
	digitalWrite(groen, LOW);

}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}


	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
	for (int i = 0; i < 10; i++)
	{
	digitalWrite(rood, HIGH);
	delay(30);
	digitalWrite(groen, HIGH);
	digitalWrite(rood, LOW);
	delay(30);
	digitalWrite(groen, LOW);
	}
	digitalWrite(groen, HIGH);
	delay(2000);
	digitalWrite(groen, LOW);
	return;
}
