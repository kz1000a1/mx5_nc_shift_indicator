

int16_t bytesToInt(uint8_t raw[], int shift, int size) {

  int16_t result = 0;

  for (int i = 0; i < size; i++) {
    // Serial.printf("result=%04X << %d = ",result, sizeof(byte) * 8);
    result = result << (sizeof raw[0] * 8);
    // Serial.printf("%d\n",result);
    for (int j = 0; j < sizeof(byte) * 8; j++) {
      // Serial.printf("%04X & %04X = %d += %04X,result=%04X\n", raw[i + shift], 1 << j,raw[i + shift] & (1 << j),result);
      // if(raw[i + shift] & (1 << j))(result += 1 << j);
      result += raw[i + shift] & (1 << j);
      //Serial.printf("i=%d,j=%d,raw[%d]=0x%02X,result=0x%04X\n",i,j,i+shift,raw[i+shift],result);
    }
  }

  return result;

  // return &raw[shift];
}

uint16_t bytesToUint(uint8_t raw[], int shift, int size) {

  uint16_t result = 0;

  for (int i = 0; i < size; i++) {
    // Serial.printf("result=%04X << %d = ",result, sizeof(byte) * 8);
    result = result << (sizeof raw[0] * 8);
    // Serial.printf("%d\n",result);
    for (int j = 0; j < sizeof(byte) * 8; j++) {
      // Serial.printf("%04X & %04X = %d += %04X,result=%04X\n", raw[i + shift], 1 << j,raw[i + shift] & (1 << j),result);
      // if(raw[i + shift] & (1 << j))(result += 1 << j);
      result += raw[i + shift] & (1 << j);
      //Serial.printf("i=%d,j=%d,raw[%d]=0x%02X,result=0x%04X\n",i,j,i+shift,raw[i+shift],result);
    }
  }

  return result;

  // return &raw[shift];
}

uint16_t bitsToUint(uint8_t raw[], int shift, int size) {

  uint16_t result = 0;

  for (int i = shift; i < shift + size; i++) {
    result = result << 1;
    result += bitToUint(raw, i);
  }

  return result;

  // return &raw[shift];
}

uint16_t bitToUint(uint8_t raw[], int shift) {
  uint16_t result;
  // Serial.printf("raw[%d]=%02X,>> %d = 0x%02X, & 0xFE\n",(shift - 1) / 8,raw[(shift - 1) / 8],7 - (shift - 1) % 8,(raw[(shift - 1) / 8] >> 7 - (shift - 1) % 8));

  result = (raw[(shift - 1) / 8] >> 7 - (shift - 1) % 8) & 0x01;
  /*
  printf("result0=%02X, result1=",result);
  result = result & 0x01;
  printf("%02X\n",result);
  } else {
    result = (raw[(shift - 1) / 8] & 0xFE);
  }*/
  return result;
}
