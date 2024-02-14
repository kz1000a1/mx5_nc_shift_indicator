CAN_frame_t rx_frame;

void mazdaMx5ShiftIndicator()
{
  float EngineRPM;
  float Speed;
  float AcceleratorPosition;
  float GearRatio;
  uint8_t ShiftPotition;

  // CAN_frame_t rx_frame;

  // Serial.printf("xQueueReceive()");

  // Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {

    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      // Serial.printf("New standard frame");
    }
    else {
      // Serial.printf("New extended frame");
    }

    if (rx_frame.FIR.B.RTR == CAN_RTR) {
      Serial.printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
    }
    else {
      
      Serial.printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        Serial.printf("0x%02X ", rx_frame.data.u8[i]);
      }
      Serial.printf("\n");

      EngineRPM = bytesToUint(rx_frame.data.u8,0,2) / 4.00;
      Speed = (bytesToUint(rx_frame.data.u8,4,2)/100.00)-100;
      // Raw speed data is given in km/h with a 100 km/h offset.
      AcceleratorPosition = bytesToUint(rx_frame.data.u8,6,1) / 2.00;
      // This is a percentage, increments of 0.5%
      if((int)Speed != 0 && (int)EngineRPM != 0)
      {
        Serial.printf("%5.2f rpm, %3.2f km/h\n",EngineRPM,Speed);
        GearRatio = (EngineRPM * 60) / FINAL_RATIO * (TYRE_OUTER_DIAMETER_16 / 100000) / Speed;
      } else {
        GearRatio = 0;
        printf("GearRatio=%d\n",GearRatio);
      }

      if(GearRatio == 0){
        ShiftPotition = 0;
      } else if(GearRatio < (GEAR_RATIO_6 + GEAR_RATIO_5) / 2) {
        ShiftPotition = 6;
        Serial.printf("GearRatio=%f\n",GearRatio);
      } else if(GearRatio < (GEAR_RATIO_5 + GEAR_RATIO_4) / 2) {
        ShiftPotition = 5;
      } else if(GearRatio < (GEAR_RATIO_4 + GEAR_RATIO_3) / 2) {
        ShiftPotition = 4;
      } else if(GearRatio < (GEAR_RATIO_3 + GEAR_RATIO_2) / 2) {
        ShiftPotition = 3;
      } else if(GearRatio < (GEAR_RATIO_2 + GEAR_RATIO_1) / 2) {
        ShiftPotition = 2;
      } else {
        ShiftPotition = 1;
      }

      Serial.printf("%5.2f rpm, %3.2f km/h %3.1f percent,%d gear\n",EngineRPM,Speed,AcceleratorPosition, ShiftPotition);
      
      // Serial.printf("%4d rpm\n", (rx_frame.data.u8[1] << 6) + (rx_frame.data.u8[2] >> 2));
    }
  }
  // Serial.printf("exit can_test()"); 
}