#include "common.h"

#include <stdio.h>

void mazdaMx5ScreenInit() {
uint8_t text_width,font_height;
  char s_Output[16];

  M5.Lcd.fillScreen(BG_COLOR);

  // ENGINE RPM
  M5.Lcd.fillRect(RPM_ORIGIN_X, RPM_ORIGIN_Y, SCREEN_WIDTH, LINE_WIDTH, LINE_COLOR);
  M5.Lcd.fillRect(RPM_ORIGIN_X, RPM_ORIGIN_Y, LINE_WIDTH, METER_HEIGHT, LINE_COLOR);
  M5.Lcd.fillRect(SCREEN_WIDTH, RPM_ORIGIN_Y, -LINE_WIDTH, METER_HEIGHT, LINE_COLOR);
  M5.Lcd.setTextSize(UNIT_FONT_SIZE, UNIT_FONT_SIZE);
  M5.Lcd.setFont(UNIT_FONT);
  M5.Lcd.setTextColor(UNIT_FONT_COLOR, BG_COLOR); 
  M5.Lcd.setTextDatum(textdatum_t::top_left);
  M5.Lcd.drawString("0", RPM_ORIGIN_X, RPM_ORIGIN_Y + METER_HEIGHT);
  M5.Lcd.setTextDatum(textdatum_t::top_center);
  M5.Lcd.drawString("ENGINE(rpm)", (SCREEN_WIDTH - RPM_ORIGIN_X) / 2, RPM_ORIGIN_Y + METER_HEIGHT);
  M5.Lcd.setTextDatum(textdatum_t::top_right);
  M5.Lcd.drawString("7,500", SCREEN_WIDTH, RPM_ORIGIN_Y + METER_HEIGHT);

  // STEERING ANGLE
  M5.Lcd.fillArc(STEERING_ORIGIN_X, STEERING_ORIGIN_Y + STEERING_R, STEERING_R, STEERING_R - LINE_WIDTH + 1, 270 - round(asin((float)STEERING_ORIGIN_X / (float)STEERING_R) * 180 / M_PI), 270 + round(asin((float)(SCREEN_MAX_X - STEERING_ORIGIN_X) / (float)STEERING_R) * 180 / M_PI), LINE_COLOR);
  Serial.printf("X=%d,R=%dasin = %f, degree = %d\n", STEERING_ORIGIN_X, STEERING_R, asin((float)STEERING_ORIGIN_X / (float)STEERING_R), 270 - round(asin(STEERING_ORIGIN_X / STEERING_R) * 180 / M_PI));
  M5.Lcd.fillRect(SCREEN_MIN_X, STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))), LINE_WIDTH, METER_HEIGHT, LINE_COLOR);
  M5.Lcd.fillRect(SCREEN_WIDTH, STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(SCREEN_MAX_X - STEERING_ORIGIN_X, 2))), - LINE_WIDTH, METER_HEIGHT, LINE_COLOR);
  M5.Lcd.fillRect(STEERING_ORIGIN_X - LINE_WIDTH / 2,STEERING_ORIGIN_Y + METER_HEIGHT + METER_SPACE, LINE_WIDTH,METER_SPACE,LINE_COLOR);

  M5.Lcd.setTextDatum(textdatum_t::top_left);
  sprintf(s_Output, "%+.0f" , - MAX_STEERING_ANGLE);
  M5.Lcd.drawString(s_Output, SCREEN_MIN_X, STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT);
  M5.Lcd.setTextDatum(textdatum_t::top_center);
  M5.Lcd.drawString("0",STEERING_ORIGIN_X,STEERING_ORIGIN_Y + METER_HEIGHT + 2 * METER_SPACE);
  M5.Lcd.drawString("STEERING ANGLE", STEERING_ORIGIN_X, STEERING_ORIGIN_Y + METER_HEIGHT + 2 * METER_SPACE + 1.5 * M5.Lcd.fontHeight());
  M5.Lcd.drawString("(DEGREE)", STEERING_ORIGIN_X, STEERING_ORIGIN_Y + METER_HEIGHT + 2 * METER_SPACE + 2.5 * M5.Lcd.fontHeight());
  M5.Lcd.setTextDatum(textdatum_t::top_right);
  sprintf(s_Output, "%+.0f" , MAX_STEERING_ANGLE);
  Serial.printf("MAX_STEERING_ANGLE = %+.0f, %f\n",MAX_STEERING_ANGLE,MAX_STEERING_ANGLE);
  M5.Lcd.drawString(s_Output, SCREEN_WIDTH, STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(SCREEN_MAX_X - STEERING_ORIGIN_X, 2))) + METER_HEIGHT);

  // BRAKE PERCENTAGE
  M5.Lcd.fillRect(BRAKE_ORIGIN_X, BRAKE_ORIGIN_Y + METER_HEIGHT - LINE_WIDTH, ACCEL_ORIGIN_X, LINE_WIDTH, LINE_COLOR);
  M5.Lcd.fillRect(BRAKE_ORIGIN_X, BRAKE_ORIGIN_Y, LINE_WIDTH, METER_HEIGHT, LINE_COLOR);
  M5.Lcd.setTextDatum(textdatum_t::bottom_left);
  M5.Lcd.drawString("100", BRAKE_ORIGIN_X, BRAKE_ORIGIN_Y);
  M5.Lcd.setTextDatum(textdatum_t::bottom_center);
  M5.Lcd.drawString("BRAKE(%)", (int)((ACCEL_ORIGIN_X - BRAKE_ORIGIN_X + LINE_WIDTH - 1) / 2), BRAKE_ORIGIN_Y);

  // ACCEL PERCENTAGE
  M5.Lcd.fillRect(ACCEL_ORIGIN_X, ACCEL_ORIGIN_Y + METER_HEIGHT - LINE_WIDTH, SCREEN_WIDTH - ACCEL_ORIGIN_X, LINE_WIDTH, LINE_COLOR);
  M5.Lcd.fillRect(ACCEL_ORIGIN_X, ACCEL_ORIGIN_Y, LINE_WIDTH, METER_HEIGHT, LINE_COLOR);
  M5.Lcd.fillRect(SCREEN_WIDTH, ACCEL_ORIGIN_Y, -LINE_WIDTH, METER_HEIGHT, LINE_COLOR);
  M5.Lcd.setTextDatum(textdatum_t::bottom_center);
  M5.Lcd.drawString("0", ACCEL_ORIGIN_X + (int)(LINE_WIDTH / 2), ACCEL_ORIGIN_Y);
  M5.Lcd.setTextDatum(textdatum_t::bottom_center);
  M5.Lcd.drawString("ACCEL(%)", (int)((SCREEN_WIDTH + ACCEL_ORIGIN_X) / 2), ACCEL_ORIGIN_Y);
  M5.Lcd.setTextDatum(textdatum_t::bottom_right);
  M5.Lcd.drawString("100", SCREEN_WIDTH, ACCEL_ORIGIN_Y);

  M5.Lcd.setTextSize(SPEED_FONT_SIZE, SPEED_FONT_SIZE);
  M5.Lcd.setFont(SPEED_FONT);
  M5.Lcd.setTextColor(SPEED_FONT_COLOR, BG_COLOR); 
  M5.Lcd.setTextDatum(textdatum_t::bottom_right);
  M5.Lcd.drawString("0.0", SCREEN_MIN_X + M5.Lcd.textWidth("200.0"),(int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + M5.Lcd.fontHeight()) / 2));
 
  text_width = M5.Lcd.textWidth("200.0");
  font_height = M5.Lcd.fontHeight();

  M5.Lcd.setTextSize(UNIT_FONT_SIZE, UNIT_FONT_SIZE);
  M5.Lcd.setFont(UNIT_FONT);
  M5.Lcd.setTextColor(UNIT_FONT_COLOR, BG_COLOR); 

  M5.Lcd.setTextDatum(textdatum_t::bottom_left);

  M5.Lcd.drawString("km/h", SCREEN_MIN_X + text_width+ M5.Lcd.textWidth("0"),(int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + font_height) / 2));
  text_width += M5.Lcd.textWidth("0km/h");

  M5.Lcd.setTextSize(SHIFT_FONT_SIZE, SHIFT_FONT_SIZE);
  M5.Lcd.setFont(SHIFT_FONT);

  M5.Lcd.drawRect(SCREEN_WIDTH - M5.Lcd.textWidth("N") + M5.Lcd.textWidth("N") % 2 + 1,(int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + M5.Lcd.fontHeight()) / 2) + 1,- (M5.Lcd.textWidth("N") + 3), - (M5.Lcd.fontHeight() + 2),LINE_COLOR);
  text_width = M5.Lcd.textWidth("N") ;
  font_height = M5.Lcd.fontHeight();

  Serial.printf("N=%d\n",M5.Lcd.textWidth("N"));
  Serial.printf("1=%d\n",M5.Lcd.textWidth("1"));
  Serial.printf("2=%d\n",M5.Lcd.textWidth("2"));
  Serial.printf("3=%d\n",M5.Lcd.textWidth("3"));
  Serial.printf("4=%d\n",M5.Lcd.textWidth("4"));
  Serial.printf("5=%d\n",M5.Lcd.textWidth("5"));
  Serial.printf("6=%d\n",M5.Lcd.textWidth("6"));
  Serial.printf("C=%d\n",M5.Lcd.textWidth("C"));

  M5.Lcd.setTextSize(UNIT_FONT_SIZE, UNIT_FONT_SIZE);
  M5.Lcd.setFont(UNIT_FONT);
  M5.Lcd.setTextColor(UNIT_FONT_COLOR, BG_COLOR); 
   M5.Lcd.setTextDatum(textdatum_t::bottom_center);
 M5.Lcd.drawString("SHIFT", SCREEN_WIDTH - (text_width * 3 / 2), (int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + font_height) / 2) + 1 - (font_height + 3));

}

void mazdaMx5ShiftIndicator(long unsigned int* rxId, unsigned char* rxBuf) {
  static float EngineRPM;
  static float Speed;
  static float AcceleratorPosition;
  static float GearRatio;
  static uint8_t ShiftPosition;
  static uint8_t clutch = 0;
  static uint8_t neutral = 0;

  // float PrevSpeed = 0;
  static float PrevEngineRPM = 0;
  static float PrevSpeed = 0;
  static float PrevAcceleratorPosition = 0;
  static uint8_t PrevShiftPosition = 0;
  char s_Output[16];

  // Serial.println("mazdaMx5ShiftIndicator");

  if (*rxId == CAN_ID_TRANSMISSION) {
    clutch = bitToUint(rxBuf, 15);
    neutral = bitToUint(rxBuf, 14);
  } else {  // Serial.printf("neutral = %d, clutch = %d, rxId = %03x, rxBuf[1] = %02x\n", neutral, clutch, rxId, bytesToInt(rxBuf, 1, 1));
    EngineRPM = bytesToUint(rxBuf, 0, 2) / 4.00;
    Speed = (bytesToUint(rxBuf, 4, 2) / 100.00) - 100;
    // Raw speed data is given in km/h with a 100 km/h offset.
    AcceleratorPosition = bytesToUint(rxBuf, 6, 1) / 2.00;
    // This is a percentage, increments of 0.5%
    if ((int)Speed != 0 && (int)EngineRPM != 0) {
      // Serial.printf("%5.2f rpm, %3.2f km/h\n",EngineRPM,Speed);
      GearRatio = (EngineRPM * 60) / FINAL_RATIO * (TYRE_OUTER_DIAMETER_16 / 100000) / Speed;
    } else {
      GearRatio = 0;
    }

    if (clutch) {
      /*      if ((int)Speed != 0 && (int)PrevSpeed == 0) {
        ShiftPosition = 1;
      } else if ((int)Speed == 0) {
        ShiftPosition = 0;
      }
      */
      ShiftPosition = 0;
    } else {
      if (neutral) {
        ShiftPosition = 7;
      } else {
        if (GearRatio == 0) {
          ShiftPosition = 0;
        } else if (GearRatio < (GEAR_RATIO_6 + GEAR_RATIO_5) / 2) {
          ShiftPosition = 6;
        } else if (GearRatio < (GEAR_RATIO_5 + GEAR_RATIO_4) / 2) {
          ShiftPosition = 5;
        } else if (GearRatio < (GEAR_RATIO_4 + GEAR_RATIO_3) / 2) {
          ShiftPosition = 4;
        } else if (GearRatio < (GEAR_RATIO_3 + GEAR_RATIO_2) / 2) {
          ShiftPosition = 3;
        } else if (GearRatio < (GEAR_RATIO_2 + GEAR_RATIO_1) / 2) {
          ShiftPosition = 2;
        } else {
          ShiftPosition = 1;
        }
      }
    }

    // Serial.printf("Prev %5.2f rpm,Now %5.2f rpm\n", PrevEngineRPM, EngineRPM);
    if (PrevEngineRPM != EngineRPM) {
      // Serial.println("PrevEngineRPM != EngineRPM");
      sprintf(s_Output, "%.0f", EngineRPM);

      if (PrevEngineRPM < EngineRPM) {
        M5.Lcd.fillRect((int)(PrevEngineRPM * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE)) / REV_LIMIT) + RPM_ORIGIN_X + LINE_WIDTH + METER_SPACE, RPM_ORIGIN_Y + LINE_WIDTH + METER_SPACE, (int)(EngineRPM * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE)) / REV_LIMIT) - (int)(PrevEngineRPM * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE)) / REV_LIMIT), METER_HEIGHT - LINE_WIDTH - METER_SPACE, RPM_COLOR);
      } else {
        M5.Lcd.fillRect((int)(PrevEngineRPM * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE)) / REV_LIMIT) + RPM_ORIGIN_X + LINE_WIDTH + METER_SPACE, RPM_ORIGIN_Y + LINE_WIDTH + METER_SPACE, (int)(EngineRPM * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE)) / REV_LIMIT) - (int)(PrevEngineRPM * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE)) / REV_LIMIT), METER_HEIGHT - LINE_WIDTH - METER_SPACE, BG_COLOR);
      }
/*
      M5.Lcd.setTextSize(0.5, 0.5);
      M5.Lcd.setFont(&fonts::Font7);
      M5.Lcd.setTextDatum(textdatum_t::bottom_right);
      M5.Lcd.setTextColor(TFT_GREEN, METER_BG_COLOR);
      // M5.Lcd.drawCentreString(s_Output, 160, 150, 4);
      M5.Lcd.fillRect(114, 160, 64, 24, METER_BG_COLOR);
      M5.Lcd.drawString(s_Output, 178, (int)(RPM_ORIGIN_Y + METER_HEIGHT + ACCEL_ORIGIN_Y + M5.Lcd.fontHeight()) / 2,SCREEN_MIN_X + M5.Lcd.fontWidth("200.0"));
*/
      PrevEngineRPM = EngineRPM;
    }

    if (PrevShiftPosition != ShiftPosition) {
      // M5.Lcd.setCursor(248 - M5.Lcd.textWidth(s_Output) / 2, 63 + 40 * 2);
      if (ShiftPosition == 7) {
        M5.Lcd.setTextColor(SHIFT_N_COLOR, BG_COLOR);
        sprintf(s_Output, "N");
      } else if (ShiftPosition == 0) {
        M5.Lcd.setTextColor(SHIFT_C_COLOR, BG_COLOR);
        sprintf(s_Output, "C");
      } else {
        M5.Lcd.setTextColor(SHIFT_FONT_COLOR, BG_COLOR);
        sprintf(s_Output, "%d", ShiftPosition);
      }
      M5.Lcd.setTextSize(SHIFT_FONT_SIZE, SHIFT_FONT_SIZE);
  M5.Lcd.setFont(SHIFT_FONT);
  M5.Lcd.setTextDatum(textdatum_t::bottom_center);
      M5.Lcd.fillRect(SCREEN_WIDTH - M5.Lcd.textWidth("N"),(int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + M5.Lcd.fontHeight()) / 2), - M5.Lcd.textWidth("N"),- M5.Lcd.fontHeight(), BG_COLOR);
      M5.Lcd.drawString(s_Output, SCREEN_WIDTH - M5.Lcd.textWidth("N") * 3 / 2,(int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + M5.Lcd.fontHeight()) / 2));
      PrevShiftPosition = ShiftPosition;
    }

    if ((int)(PrevSpeed * 10) != (int)(Speed * 10)) {
      sprintf(s_Output, "%3.1f", Speed);
      // M5.Lcd.fillRect(0, 83, 140, 48, TFT_BLACK);
      //M5.Lcd.fillRect(0, 75, 140, 60, TFT_BLACK);
  M5.Lcd.setTextSize(SPEED_FONT_SIZE, SPEED_FONT_SIZE);
  M5.Lcd.setFont(SPEED_FONT);
  M5.Lcd.setTextColor(SPEED_FONT_COLOR, BG_COLOR); 
  M5.Lcd.setTextDatum(textdatum_t::bottom_right);
      M5.Lcd.fillRect(SCREEN_MIN_X + M5.Lcd.textWidth("200.0"),(int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + M5.Lcd.fontHeight()) / 2), - M5.Lcd.textWidth("200.0"),- M5.Lcd.fontHeight(), BG_COLOR);
      M5.Lcd.drawString(s_Output, SCREEN_MIN_X + M5.Lcd.textWidth("200.0"),(int)((STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow(STEERING_ORIGIN_X, 2))) + METER_HEIGHT + ACCEL_ORIGIN_Y + M5.Lcd.fontHeight()) / 2));

      PrevSpeed = Speed;
    }

    if ((int)(PrevAcceleratorPosition * 10) != (int)(AcceleratorPosition * 10)) {
      if (PrevAcceleratorPosition < AcceleratorPosition) {
        M5.Lcd.fillRect((int)(PrevAcceleratorPosition * (SCREEN_WIDTH - ACCEL_ORIGIN_X - 2 * (LINE_WIDTH + METER_SPACE)) / 100) + ACCEL_ORIGIN_X + LINE_WIDTH + METER_SPACE, ACCEL_ORIGIN_Y, (int)(AcceleratorPosition * (SCREEN_WIDTH - ACCEL_ORIGIN_X - 2 * (LINE_WIDTH + METER_SPACE)) / 100) - (int)(PrevAcceleratorPosition * (SCREEN_WIDTH - ACCEL_ORIGIN_X - 2 * (LINE_WIDTH + METER_SPACE)) / 100), METER_HEIGHT - LINE_WIDTH - METER_SPACE, ACCEL_COLOR);
      } else {
        M5.Lcd.fillRect((int)(PrevAcceleratorPosition * (SCREEN_WIDTH - ACCEL_ORIGIN_X - 2 * (LINE_WIDTH + METER_SPACE)) / 100) + ACCEL_ORIGIN_X + LINE_WIDTH + METER_SPACE, ACCEL_ORIGIN_Y, (int)(AcceleratorPosition * (SCREEN_WIDTH - ACCEL_ORIGIN_X - 2 * (LINE_WIDTH + METER_SPACE)) / 100) - (int)(PrevAcceleratorPosition * (SCREEN_WIDTH - ACCEL_ORIGIN_X - 2 * (LINE_WIDTH + METER_SPACE)) / 100), METER_HEIGHT - LINE_WIDTH - METER_SPACE, BG_COLOR);
      }
      PrevAcceleratorPosition = AcceleratorPosition;
    }
  }
}



void mazdaMx5SteeringAngle(unsigned char* rxBuf) {
  static int16_t SteeringAngle;
  static int16_t PrevSteeringAngle = 0;
  // Serial.println("mazdaMx5SteeringAngle");

  SteeringAngle = bytesToInt(rxBuf, 2, 2);
  // Serial.printf("SteeringAngle %+d degree\n", SteeringAngle);
  if (PrevSteeringAngle != SteeringAngle) {

      if (PrevSteeringAngle < SteeringAngle) {
        for(int i = 0;i<((int)(SteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) - (int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)));i++){
        M5.Lcd.drawFastVLine(STEERING_ORIGIN_X + (int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) + STEERING_WIDTH / 2 + 1 + i,
                             STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow((int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) + STEERING_WIDTH / 2 + 1 + i, 2))) + LINE_WIDTH + METER_SPACE,
                             METER_HEIGHT - LINE_WIDTH - METER_SPACE, 
                             STEERING_COLOR);
        M5.Lcd.drawFastVLine(STEERING_ORIGIN_X + (int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) - STEERING_WIDTH / 2 + i,
                             STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow((int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) - STEERING_WIDTH / 2 + i, 2))) + LINE_WIDTH + METER_SPACE,
                             METER_HEIGHT - LINE_WIDTH - METER_SPACE, 
                             BG_COLOR);

        }
      } else {
        for(int i = 0;i<((int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) - (int)(SteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)));i++){
        M5.Lcd.drawFastVLine(STEERING_ORIGIN_X + (int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) - STEERING_WIDTH / 2 - 1 - i,
                             STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow((int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) - STEERING_WIDTH / 2 - 1 - i, 2))) + LINE_WIDTH + METER_SPACE,
                             METER_HEIGHT - LINE_WIDTH - METER_SPACE, 
                             STEERING_COLOR);
        M5.Lcd.drawFastVLine(STEERING_ORIGIN_X + (int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) + STEERING_WIDTH / 2 - i,
                             STEERING_ORIGIN_Y + STEERING_R - (int)(sqrt(pow(STEERING_R, 2) - pow((int)(PrevSteeringAngle * (SCREEN_WIDTH - 2 * (LINE_WIDTH + METER_SPACE) - STEERING_WIDTH) / (STEERING_MAX - STEERING_MIN)) + STEERING_WIDTH / 2 - i, 2))) + LINE_WIDTH + METER_SPACE,
                             METER_HEIGHT - LINE_WIDTH - METER_SPACE, 
                             BG_COLOR);
        }
      }
          PrevSteeringAngle = SteeringAngle;
    }



}


void mazdaMx5BrakePressure(unsigned char* rxBuf) {
  // static float BrakePressure;
  static float BrakePercentage;
  static float PrevBrakePercentage = 0;
  // bool OnOff;

  // Serial.println("mazdaMx5BrakePressure");

  // BrakePressure = (3.4518689053 * bytesToInt(rxBuf, 0, 2) - 327.27) / 1000.00;
  // BrakePercentage = min(0.2 * (bytesToInt(rxBuf, 0, 2) - 102), 100);
  BrakePercentage = 0.2 * (bytesToInt(rxBuf, 0, 2) - 102);
  if (100 < BrakePercentage) {
    BrakePercentage = 100;
  }

  // OnOff = bitsToUint(rxBuf, 17, 1);
  // Serial.printf("BrakePressure %f kPa\n", BrakePressure);
  // Serial.printf("BrakePercentage %3.1f percent\n", BrakePercentage);
  // Serial.printf("OnOff %d\n", OnOff);
  if (PrevBrakePercentage < BrakePercentage) {
            M5.Lcd.fillRect(ACCEL_ORIGIN_X - 1 - METER_SPACE - (int)(PrevBrakePercentage * (ACCEL_ORIGIN_X - 1 - BRAKE_ORIGIN_X - LINE_WIDTH - 2 * METER_SPACE) / 100),
                            BRAKE_ORIGIN_Y,
                            (int)(PrevBrakePercentage * (ACCEL_ORIGIN_X - 1 - BRAKE_ORIGIN_X - LINE_WIDTH - 2 * METER_SPACE) / 100) - 
                                (int)(BrakePercentage * (ACCEL_ORIGIN_X - 1 - BRAKE_ORIGIN_X - LINE_WIDTH - 2 * METER_SPACE) / 100),
                            METER_HEIGHT - LINE_WIDTH - METER_SPACE,
                            BRAKE_COLOR);
  } else {
            M5.Lcd.fillRect(ACCEL_ORIGIN_X - 1 - METER_SPACE - (int)(PrevBrakePercentage * (ACCEL_ORIGIN_X - 1 - BRAKE_ORIGIN_X - LINE_WIDTH - 2 * METER_SPACE) / 100),
                            BRAKE_ORIGIN_Y,
                            (int)(PrevBrakePercentage * (ACCEL_ORIGIN_X - 1 - BRAKE_ORIGIN_X - LINE_WIDTH - 2 * METER_SPACE) / 100) - 
                                (int)(BrakePercentage * (ACCEL_ORIGIN_X - 1 - BRAKE_ORIGIN_X - LINE_WIDTH - 2 * METER_SPACE) / 100),
                            METER_HEIGHT - LINE_WIDTH - METER_SPACE,
                            BG_COLOR);
  }
  PrevBrakePercentage = BrakePercentage;
}
