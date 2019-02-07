#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP WUdp;

//Wifi settings
char* base_ssid = "whale2";            // will be complet with 1 or 2 !! -> id impare = whale1 // id paire = whale2
//const char* password = "9000leds";

//
// NETWORK
//
IPAddress server;
unsigned int udpPort_node = 3737;  // Node port to listen on
unsigned int udpPort_server = 3738;  // Server port to speak to

bool wifi_available = false;


//
// PROTOTYPES
//

void wifi_init() {

  String ssid = String(base_ssid);

  // detect subnet group (paire / impaire)
  byte subnet_group = 2;
//  if ( (eeprom_getID() & 0x01) == 0) subnet_group = 2;
//  ssid += String(subnet_group);
  
  IPAddress ip(192, 168, subnet_group, eeprom_getID() + 100);               // Static IP
  IPAddress gateway(192, 168, subnet_group, 1);
  IPAddress subnet_mask(255, 255, 255, 0);

  // Enable wifi
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet_mask);

  // Connect wifi
  WiFi.onEvent(wifi_event);
  // WiFi.begin(ssid, password);
  WiFi.begin(ssid.c_str());

  // UDP Receiver
  WUdp.begin(udpPort_node);

  // UDP Send to
  server = IPAddress(192, 168, subnet_group, 200);

#if defined(DEBUG)
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), udpPort_node);
#endif

}

void wifi_send(uint8_t* message, int sizeM) {
  if (!wifi_available) return;
  WUdp.beginPacket(server, udpPort_server);
  WUdp.write(message, sizeM);
  WUdp.endPacket();
}


bool wifi_read(unsigned char* incomingPacket) {
  int packetSize = WUdp.parsePacket();
  if (packetSize)
  {
#if defined(DEBUG_MSG)
    Serial.printf("Received %d bytes from %s\n", packetSize, WUdp.remoteIP().toString().c_str());
#endif

    // receive incoming UDP packets
    int len = WUdp.read(incomingPacket, MTUu);

#if defined(DEBUG_MSG)
    Serial.println("Packet stored\n");
    for (int k = 0; k < len; k++) Serial.printf("%i ", incomingPacket[k]);
    Serial.println();
#endif

    return true;
  }
  return false;
}

void wifi_event(WiFiEvent_t event) {
  static byte retry = 0;

  if (event == SYSTEM_EVENT_STA_DISCONNECTED) {
    wifi_available = false;
    retry += 1;

#ifdef DEBUG
    Serial.print(" reconnecting ");
    Serial.println(retry);
#endif
    WiFi.reconnect();
  }
  else if (event == SYSTEM_EVENT_STA_GOT_IP) {
    retry = 0;
    wifi_available = true;
  }
}

bool wifi_isok() {
  return wifi_available;
}
