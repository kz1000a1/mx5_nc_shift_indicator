/*
  Please add MCP_CAN_LIB to your library first........
  MCP_CAN_LIB file in M5stack lib examples -> modules -> COMMU ->
  MCP_CAN_lib.rar
*/

// #include <M5Stack.h>
#include <ESP32-Chimera-Core.h>
#include "mazda_mx5_nc.h"

#include "can_function.h"
#include "common.h"
#include "layout.h"


void setup() {
  int offset;

  M5.begin();
  M5.Power.begin();
  M5.Lcd.init();
  Serial.begin(115200);
  M5.Lcd.setColorDepth(16);
  M5.Lcd.fillScreen(TFT_BLACK);
  mazdaMx5ScreenInit();
  init_can();
}

void loop() {
  long unsigned int rxId;
  unsigned char len = 0;
  unsigned char rxBuf[8];
  // char msgString[128];  // Array to store serial string


  if (!can_readFrame(&rxId, &len, rxBuf)) {
    switch (rxId) {
      case 0x211:
        break;
      case CAN_ID_ENGINE_SPEED:
      case CAN_ID_TRANSMISSION:
        mazdaMx5ShiftIndicator(&rxId, rxBuf);
        break;
      case CAN_ID_STEERLING:
        mazdaMx5SteeringAngle(rxBuf);
        break;
      case CAN_ID_BRAKE:
        mazdaMx5BrakePressure(rxBuf);
        break;
      default:
        Serial.printf("Unexpected can frame received. rxId=%3x\n", rxId);
    }
  }
}
