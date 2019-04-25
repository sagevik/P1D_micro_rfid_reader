#include <SoftwareSerial.h>

// Interval for timer (in milliseconds)
#define INTERVAL 100

// Set up softwareserial on pins 8 and 9
#define TXPIN 8
#define RXPIN 9
SoftwareSerial softSer(TXPIN, RXPIN);

unsigned long timeLast = 0;

String rfidTag = "";

void setup() {
    Serial.begin(9600);
    while(!Serial){
        // wait for serial port to connect
    }
    // Init SoftwareSerial for using microRfid reader
    softSer.begin(9600);
    while(!softSer){
        // wait for softserial port to connect
    }
}

void loop() {
    unsigned long timeNow = millis();
    
    //check timer for and read tag if INTERVAL has past
    if ((timeNow - timeLast) > INTERVAL){
        rfidTag = readTag();

        // print tag to Serial if rfidTag contains a value
        if( rfidTag != "" ){
            Serial.println(rfidTag);
            rfidTag = "";
      }
      //update timer
      timeLast = timeNow;
    }

}


String readTag()
{
    String tag = "";
    char val = 0;

    softSer.write("RAT\r");
    if(softSer.available()){
        do{
            val = softSer.read();
            tag += val;
//            delayMicroseconds(50);
        }while (val != '\r');
    }
    if(tag.length()!= 33){
       tag = "";
    }
    return tag;  
}
