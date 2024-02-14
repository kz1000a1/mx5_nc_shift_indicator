/*
  Please add MCP_CAN_LIB to your library first........
  MCP_CAN_LIB file in M5stack lib examples -> modules -> COMMU ->
  MCP_CAN_lib.rar
*/

#include <M5Stack.h>
#include <ESP32CAN.h>
#include "mazda_mx5_nc.h"

/**
 * variable for CAN
 */
CAN_device_t CAN_cfg;               // CAN Config
// unsigned long previousMillis = 0;   // will store last time a CAN Message was send
// const int interval = 1000;          // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;       // Receive Queue size
CAN_filter_t p_filter;

void init_can();
void test_can();

uint16_t can_id = CAN_ID_ENGINE_SPEED;

void setup() {
    M5.begin();
    Serial.begin(115200);
    delay(1000);
/*
    data[0] = 0xff;
    data[1] = 0xff;
    data[2] = 0xff;
    data[3] = 0xff;
    Serial.printf("0x%02X%02X%02X%02X -> steering angle = %+d\n",data[0], data[1], data[2], data[3], bytesToInt(data, 2, 2));

    data[2] = 0x00;
    data[3] = 0x00;
    Serial.printf("0x%02X%02X%02X%02X -> steering angle = %+d\n",data[0], data[1], data[2], data[3], bytesToInt(data, 2, 2));

    data[2] = 0x88;
    data[3] = 0x88;
    Serial.printf("0x%02X%02X%02X%02X -> steering angle = %+d\n",data[0], data[1], data[2], data[3], bytesToInt(data, 2, 2));
    
    Serial.println("Test Filter all IDs");

    data[0] = 0xff;
    data[1] = 0x7f;
    data[2] = 0xff;
    data[3] = 0xff;
    // Serial.printf("bitToUint test 1=%d,8=%d,9=%d,10=%d,16=%d,17=%d\n",bitToUint(data, 1), bitToUint(data, 8), bitToUint(data, 9), bitToUint(data, 10), bitToUint(data, 16), bitToUint(data, 17));
    Serial.printf("1,1=%04X,8,1=%04X,9,1=%04X,8,3=%04X\n",bitsToUint(data,1,1) ,bitsToUint(data,8,1) ,bitsToUint(data,9,1) ,bitsToUint(data,8,3));
*/

  init_can();
}


void loop() {
    if (M5.BtnA.wasPressed()) {
        // init_can();
        ESP32Can.CANStop();

        p_filter.ACR0 = can_id >> 3;
        p_filter.ACR1 = (can_id << 5) & 0xE0;

        ESP32Can.CANConfigFilter(&p_filter);
        Serial.printf("FM:%d,C0:0x%02X,C1:0x%02X,C2:0x%02X,C3:0x%02X,M0:0x%02X,M1:0x%02X,M2:0x%02X,M3:0x%02X\n",
                     p_filter.FM,
                      p_filter.ACR0,
                      p_filter.ACR1,
                      p_filter.ACR2,
                      p_filter.ACR3,
                      p_filter.AMR0,
                      p_filter.AMR1,
                      p_filter.AMR2,
                      p_filter.AMR3);
        // Init CAN Module
        ESP32Can.CANInit();
     }
    mazdaMx5ShiftIndicator();

    // test_can();
    M5.update();
}

void init_can() {
    // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the
    // masks and filters disabled.
    CAN_cfg.speed = CAN_SPEED_1000KBPS;
    CAN_cfg.tx_pin_id = GPIO_NUM_21;
    CAN_cfg.rx_pin_id = GPIO_NUM_22;
    CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
    Serial.println("ESP32.CANInit.....");
    // Set CAN Filter
    // See in the SJA1000 Datasheet chapter "6.4.15 Acceptance filter"
    // and the APPLICATION NOTE AN97076 chapter "4.1.2 Acceptance Filter" 
    // for PeliCAN Mode
    p_filter.FM = Single_Mode;

    p_filter.ACR0 = can_id >> 3;
    p_filter.ACR1 = (can_id << 5) & 0xE0;
    p_filter.ACR2 = 0;
    p_filter.ACR3 = 0;

    p_filter.AMR0 = 0xFF;
    p_filter.AMR1 = 0xFF;
    p_filter.AMR2 = 0xFF;
    p_filter.AMR3 = 0xFF;
    ESP32Can.CANConfigFilter(&p_filter);
    Serial.printf("FM:%d,C0:0x%02X,C1:0x%02X,C2:0x%02X,C3:0x%02X,M0:0x%02X,M1:0x%02X,M2:0x%02X,M3:0x%02X\n",
                  p_filter.FM,
                  p_filter.ACR0,
                  p_filter.ACR1,
                  p_filter.ACR2,
                  p_filter.ACR3,
                  p_filter.AMR0,
                  p_filter.AMR1,
                  p_filter.AMR2,
                  p_filter.AMR3);
    // Init CAN Module
    ESP32Can.CANInit();
    Serial.println("Init CAN Module.....");
    Serial.println("Waiting Frame");
    Serial.println(
        "If there are phenomena such as failure of normal communication");
    Serial.println(
        "Please check the communication rate or add a terminal resistance "
        "between the H and L phases");
}
