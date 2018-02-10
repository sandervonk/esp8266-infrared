#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <framework.h>

#define PanasonicAddress      (0x4004)

typedef struct {
  char const * name;
  uint32_t code;
} button_t;

button_t buttons[] = {
  { "power", 0x0538BC81 },
  { "pause", 0x05505005 },
  { "play", 0x05505005 },
  { "next song", 0x0538526F },
  { "previous song", 0x053892AF },
  { "track 1", 0x05380835 },
  { "track 2", 0x053888B5 },
  { "track 3", 0x05384875 },
  { "track 4", 0x0538C8F5 },
  { "track 5", 0x05382815 },
  { "track 6", 0x0538A895 },
  { "track 7", 0x05386855 },
  { "track 8", 0x0538E8D5 },
  { "track 9", 0x05381825 },
  { "two digits", 0x0538211C },
  { "volume up", 0x05000401 },
  { "volume down", 0x05008481 },
  { NULL, 0x0 }
};

IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)

void handleRoot(void)
{
    String message = "";

    if (Framework::server.args() >= 1 && 
        Framework::server.argName(0) == "req") {
          
      String buttonReq = Framework::server.arg(0);      
      button_t const *p;
      for (p = buttons; p->name; p++) {
        if ( String(p->name) == buttonReq ) {
          break;
        }
      }
      if (p->name) {
          message += "Sending "; 
          message += p->name;
          message += "\n\n";
          irsend.sendPanasonic(PanasonicAddress, p->code);
      } else {
          message += "'"; 
          message += buttonReq;
          message +="' not found\n\n";
      }
    }
    message += "Valid commands are:<ul>\n\n";
    for (button_t const *p = buttons; p->name; p++) {
      message += "<li>";
      message += "<a href=\"/ir?ir=";
      message += p->name;
      message += "\">";
      message += p->name;
      message += "</li>\n";
    }
    message += "</ul>";

    Serial.println(message);
    Framework::server.send( 200, "text/html", message );
}


void setup() 
{
  Framework::begin();
  Framework::server.on("/ir", handleRoot);
  Framework::server.begin();
  delay(500);  // Wait a bit for the serial connection to be establised.
  irsend.begin();

 if (!MDNS.begin("ir-interface")) {
    Serial.println("Error setting up MDNS responder!");
    while(1) { 
      delay(1000);
    }
  }
  MDNS.addService("http", "tcp", 80);
  
  Serial.println("Ready");
}

void loop() {
  // test only
  irsend.sendPanasonic(PanasonicAddress, 0x05505005);

  Framework::handle();
}

