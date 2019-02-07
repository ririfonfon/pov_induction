// **Required** if debugging is enabled in library header
// TODO: Is there any way to put this in digitalLeds_initStrands() and avoid undefined refs?
#if DEBUG_ESP32_DIGITAL_LED_LIB
int digitalLeds_debugBufferSz = 1024;
char * digitalLeds_debugBuffer = static_cast<char*>(calloc(digitalLeds_debugBufferSz, sizeof(char)));
#endif

void dumpDebugBuffer(int, char *);

void dumpSysInfo() {
  esp_chip_info_t sysinfo;
  esp_chip_info(&sysinfo);
#ifdef DEBUG
  Serial.print("Model: ");
  Serial.print((int)sysinfo.model);
  Serial.print("; Features: 0x");
  Serial.print((int)sysinfo.features, HEX);
  Serial.print("; Cores: ");
  Serial.print((int)sysinfo.cores);
  Serial.print("; Revision: r");
  Serial.println((int)sysinfo.revision);
#endif
}// dumpSysInfo

void dumpDebugBuffer(int id, char * debugBuffer) {
#ifdef DEBUG
  Serial.print("DEBUG: (");
  Serial.print(id);
  Serial.print(") ");
  Serial.println(debugBuffer);
#endif
  debugBuffer[0] = 0;
}// dumpDebugBuffer
