#include "can_function.h"

#ifdef USE_COMMU

/* COMMU */

#include <mcp_can.h>

#define CAN0_INT 15  // Set INT to pin 2
MCP_CAN CAN0(12);    // Set CS to pin 10

void init_can() {


  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the
  // masks and filters disabled.
  if (CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");

  pinMode(CAN0_INT, INPUT);  // Configuring pin for /INT input

  // Set filter all can id block
  CAN0.init_Mask(0, 0x07ff0000 & ~(CAN_MASK0 << 16));

CAN0.init_Filt(0, CAN_FILTER0 << 16);


  CAN0.init_Filt(1, CAN_FILTER1 << 16);  // Set can id that wanted to FILTER0

  CAN0.init_Mask(1, 0x07ff0000 & ~(CAN_MASK1 << 16));
  CAN0.init_Filt(2, 0x00000000);
  CAN0.init_Filt(3, 0x00000000);
  CAN0.init_Filt(4, 0x00000000);
  CAN0.init_Filt(5, 0x00000000);

  CAN0.setMode(MCP_NORMAL);
  // CAN0.setMode(MCP_LISTENONLY);
8
  Serial.println("MCP2515 Library Receive Example...");
}

void can_setFilter(uint16_t canid) {
  if (canid == CAN_ID_ENGINE_SPEED) {
    CAN0.init_Filt(0, CAN_ID_TRANSMISSION << 16);
  } else {
    CAN0.init_Filt(0, 0x00000000);
  }

  CAN0.init_Filt(1, canid << 16);  // Set can id that wanted to FILTER0
  return;
}

bool can_readFrame(long unsigned int *rxId, unsigned char *len, unsigned char rxBuf[]) {
  if (!digitalRead(CAN0_INT))  // If CAN0_INT pin is low, read receive buffer
  {

    do {
      CAN0.readMsgBuf(
        rxId, len,
        rxBuf);  // Read data: len = data length, buf = data byte(s)
      // Serial.println("CAN0.readMsgBuf()");
    } while (!digitalRead(CAN0_INT));

    return 0;
  }

  return 1;
}

#else

/* CAN BUS Unit */

#include <ESP32CAN.h>

CAN_device_t CAN_cfg;          // CAN Config
const int rx_queue_size = 10;  // Receive Queue size
CAN_filter_t p_filter;

void init_can() {

  CAN_cfg.speed = CAN_SPEED_500KBPS;   // Set 1000kbps but work 500kbps
  CAN_cfg.tx_pin_id = GPIO_NUM_21;
  CAN_cfg.rx_pin_id = GPIO_NUM_22;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  Serial.println("ESP32.CANInit.....");
  // Set CAN Filter
  // See in the SJA1000 Datasheet chapter "6.4.15 Acceptance filter"
  // and the APPLICATION NOTE AN97076 chapter "4.1.2 Acceptance Filter"
  // for PeliCAN Mode
  // p_filter.FM = Dual_Mode;
  p_filter.FM = Dual_Mode;

  p_filter.ACR0 = CAN_FILTER0 >> 3;
  p_filter.ACR1 = (CAN_FILTER0 << 5) & 0xE0;
  
  p_filter.ACR2 = CAN_FILTER1 >> 3;
  p_filter.ACR3 = (CAN_FILTER1 << 5) & 0xE0;
  // p_filter.ACR2 = 0;
  // p_filter.ACR3 = 0;
  p_filter.AMR0 = CAN_MASK0 >> 3;
  p_filter.AMR1 = ((CAN_MASK0 << 5) & 0xff) | 0x1F;
  p_filter.AMR2 = CAN_MASK1 >> 3;
  p_filter.AMR3 = ((CAN_MASK1 << 5) & 0xff) | 0x1F;

  // p_filter.AMR2 = 0xFF;
  // p_filter.AMR3 = 0x1F;
  ESP32Can.CANConfigFilter(&p_filter);
  // CAN0.setMode(MCP_LISTENONLY);
  ESP32Can.CANInit();
  Serial.println("MCP2515 Library Receive Example...");
}
void can_setFilter(uint16_t canid) {
  ESP32Can.CANStop();
  p_filter.ACR0 = canid >> 3;
  p_filter.ACR1 = (canid << 5) & 0xE0;

  if (canid == CAN_ID_ENGINE_SPEED) {
    p_filter.ACR2 = CAN_ID_TRANSMISSION >> 3;
    p_filter.ACR3 = (CAN_ID_TRANSMISSION << 5) & 0xE0;
  } else {
    p_filter.ACR2 = 0;
    p_filter.ACR3 = 0;
  }

  ESP32Can.CANConfigFilter(&p_filter);
  // CAN0.setMode(MCP_LISTENONLY);
  ESP32Can.CANInit();

  return;
}

bool can_readFrame(long unsigned int *rxId, unsigned char *len, unsigned char rxBuf[]) {
  CAN_frame_t rx_frame;

  if (uxQueueMessagesWaiting(CAN_cfg.rx_queue)) {
    do {
      xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS);
    } while (uxQueueMessagesWaiting(CAN_cfg.rx_queue));

    *rxId = rx_frame.MsgID;
    *len = rx_frame.FIR.B.DLC;
    for (int i = 0; i < *len; i++) {
      rxBuf[i] = rx_frame.data.u8[i];
    }

    return 0;
  }

  return 1;
}




#endif
