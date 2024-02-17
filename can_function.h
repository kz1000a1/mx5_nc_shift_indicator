#define USE_CAN_BUS_UNIT

#define CAN_FILTER0 0x080
#define CAN_MASK0   0x00F
#define CAN_FILTER1 0x201
#define CAN_MASK1   0x030

void init_can();
void can_setFilter(uint16_t canid);
bool can_readFrame(long unsigned int *rxId, unsigned char *len, unsigned char rxBuf[]);