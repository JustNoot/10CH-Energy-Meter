#include <SPI.h>

#define BL0910_CS_PIN 21
 
static const uint8_t BL0910_READ_COMMAND = 0x82;
static const uint8_t BL0910_WRITE_COMMAND = 0x81;
 
 // current and voltage waveform data, 24bit signed number, default: 0x000000
static const uint8_t BL0910_REG_WAVE_1 = 0x01;
static const uint8_t BL0910_REG_WAVE_2 = 0x02;
static const uint8_t BL0910_REG_WAVE_3 = 0x03;
static const uint8_t BL0910_REG_WAVE_4 = 0x04;
static const uint8_t BL0910_REG_WAVE_5 = 0x05;
static const uint8_t BL0910_REG_WAVE_6 = 0x06;
static const uint8_t BL0910_REG_WAVE_7 = 0x07;
static const uint8_t BL0910_REG_WAVE_8 = 0x08;
static const uint8_t BL0910_REG_WAVE_9 = 0x09;
static const uint8_t BL0910_REG_WAVE_10 = 0x0A;
static const uint8_t BL0910_REG_WAVE_11 = 0x0B;
 
 // effective value calculation register, 24 bit unsigned number, default: 0x000000
static const uint8_t BL0910_REG_RMS_1 = 0x0C;
static const uint8_t BL0910_REG_RMS_2 = 0x0D;
static const uint8_t BL0910_REG_RMS_3 = 0x0E;
static const uint8_t BL0910_REG_RMS_4 = 0x0F;
static const uint8_t BL0910_REG_RMS_5 = 0x10;
static const uint8_t BL0910_REG_RMS_6 = 0x11;
static const uint8_t BL0910_REG_RMS_7 = 0x12;
static const uint8_t BL0910_REG_RMS_8 = 0x13;
static const uint8_t BL0910_REG_RMS_9 = 0x14;
static const uint8_t BL0910_REG_RMS_10 = 0x15;
static const uint8_t BL0910_REG_RMS_11 = 0x16;
 
 // fast effective value register, 24 bit unsigned number, default: 0x000000
static const uint8_t BL0910_REG_FAST_RMS_1 = 0x17;
static const uint8_t BL0910_REG_FAST_RMS_2 = 0x18;
static const uint8_t BL0910_REG_FAST_RMS_3 = 0x19;
static const uint8_t BL0910_REG_FAST_RMS_4 = 0x1A;
static const uint8_t BL0910_REG_FAST_RMS_5 = 0x1B;
static const uint8_t BL0910_REG_FAST_RMS_6 = 0x1C;
static const uint8_t BL0910_REG_FAST_RMS_7 = 0x1D;
static const uint8_t BL0910_REG_FAST_RMS_8 = 0x1E;
static const uint8_t BL0910_REG_FAST_RMS_9 = 0x1F;
static const uint8_t BL0910_REG_FAST_RMS_10 = 0x20;
static const uint8_t BL0910_REG_FAST_RMS_11 = 0x21;
 
 // active power, 24 bit signed number, default 0x000000
static const uint8_t BL0910_REG_WATT_1 = 0x22;
static const uint8_t BL0910_REG_WATT_2 = 0x23;
static const uint8_t BL0910_REG_WATT_3 = 0x24;
static const uint8_t BL0910_REG_WATT_4 = 0x25;
static const uint8_t BL0910_REG_WATT_5 = 0x26;
static const uint8_t BL0910_REG_WATT_6 = 0x27;
static const uint8_t BL0910_REG_WATT_7 = 0x28;
static const uint8_t BL0910_REG_WATT_8 = 0x29;
static const uint8_t BL0910_REG_WATT_9 = 0x2A;
static const uint8_t BL0910_REG_WATT_10 = 0x2B;
static const uint8_t BL0910_REG_WATT_TOTAL = 0x2C;
 
static const uint8_t BL0910_REG_FVAR = 0x2D;
static const uint8_t BL0910_REG_VA = 0x2E;
 
 // active energy pulse count register, 24 bit unsigned number, default: 0x000000
static const uint8_t BL0910_REG_CF_CNT_1 = 0x2F;
static const uint8_t BL0910_REG_CF_CNT_2 = 0x30;
static const uint8_t BL0910_REG_CF_CNT_3 = 0x31;
static const uint8_t BL0910_REG_CF_CNT_4 = 0x32;
static const uint8_t BL0910_REG_CF_CNT_5 = 0x33;
static const uint8_t BL0910_REG_CF_CNT_6 = 0x34;
static const uint8_t BL0910_REG_CF_CNT_7 = 0x35;
static const uint8_t BL0910_REG_CF_CNT_8 = 0x36;
static const uint8_t BL0910_REG_CF_CNT_9 = 0x37;
static const uint8_t BL0910_REG_CF_CNT_10 = 0x38;
static const uint8_t BL0910_REG_CF_CNT_TOTAL = 0x39;
static const uint8_t BL0910_REG_CFQ_CNT_TOTAL = 0x3A;
static const uint8_t BL0910_REG_CFS_CNT_TOTAL = 0x3B;
 
 // phase angle measurement register, 16 bit unsigned number, default: 0x0000
static const uint8_t BL0910_REG_ANGLE_1 = 0x3C;
static const uint8_t BL0910_REG_ANGLE_2 = 0x3D;
static const uint8_t BL0910_REG_ANGLE_3 = 0x3E;
static const uint8_t BL0910_REG_ANGLE_4 = 0x3F;
static const uint8_t BL0910_REG_ANGLE_5 = 0x40;
static const uint8_t BL0910_REG_ANGLE_6 = 0x41;
static const uint8_t BL0910_REG_ANGLE_7 = 0x42;
static const uint8_t BL0910_REG_ANGLE_8 = 0x43;
static const uint8_t BL0910_REG_ANGLE_9 = 0x44;
static const uint8_t BL0910_REG_ANGLE_10 = 0x45;
 
static const uint8_t BL0910_REG_FAST_RMS_H_1 = 0x46;
static const uint8_t BL0910_REG_FAST_RMS_H_2 = 0x47;
static const uint8_t BL0910_REG_FAST_RMS_H_3 = 0x48;
static const uint8_t BL0910_REG_FAST_RMS_H_4 = 0x49;
static const uint8_t BL0910_REG_FAST_RMS_H_5 = 0x57;
static const uint8_t BL0910_REG_FAST_RMS_H_6 = 0x58;
static const uint8_t BL0910_REG_FAST_RMS_H_7 = 0x59;
static const uint8_t BL0910_REG_FAST_RMS_H_8 = 0x5A;
static const uint8_t BL0910_REG_FAST_RMS_H_9 = 0x5B;
static const uint8_t BL0910_REG_FAST_RMS_H_10 = 0x5C;
 
static const uint8_t BL0910_REG_PF = 0x4A;
 
static const uint8_t BL0910_REG_LINE_WATTHR = 0x4B;
static const uint8_t BL0910_REG_LINE_VARH = 0x4C;
static const uint8_t BL0910_REG_SIGN = 0x4D;
static const uint8_t BL0910_REG_PERIOD = 0x4E;
 
static const uint8_t BL0910_REG_STATUS1 = 0x54;
static const uint8_t BL0910_REG_STATUS3 = 0x56;
 
 // temperature measurement register, 24 bit unsigned numver, default: 0x000000
static const uint8_t BL0910_REG_TPS1 = 0x5E; // internal temperature, (TPS1-64)*12.5/59-40 ˚C
static const uint8_t BL0910_REG_TPS2 = 0x5F; // VT pin ADC value
 
 // PGA gain adjustment register, 24 bit (4 bits per channel), default: 0x000000
 // 4 PGA settings: 0000 = 1; 0001 = 2; 0010 = 8; 0011 = 16
 // [3:0]   voltage channel,    current channel 6
 // [7:4]   current channel 1,  current channel 7
 // [11:8]  current channel 2,  current channel 8
 // [15:12] current channel 3,  current channel 9
 // [19:16] current channel 4,  current channel 10
 // [23:20] current channel 5
static const uint8_t BL0910_REG_GAIN1 = 0x60;
static const uint8_t BL0910_REG_GAIN2 = 0x61;
 
 
 // channel phase compensation register, 16 bit (8 bit per channel), default: 0x0000
static const uint8_t BL0910_REG_PHASE_1_2 = 0x64;
static const uint8_t BL0910_REG_PHASE_3_4 = 0x65;
static const uint8_t BL0910_REG_PHASE_5_6 = 0x66;
static const uint8_t BL0910_REG_PHASE_7_8 = 0x67;
static const uint8_t BL0910_REG_PHASE_9_10 = 0x68;
static const uint8_t BL0910_REG_PHASE_11 = 0x69; // 8 bit, default: 0x00
 
 // phase compensation register, 5 bit number, default: 0000H
static const uint8_t BL0910_REG_VAR_PHCAL_I = 0x6A;
static const uint8_t BL0910_REG_VAR_PHCAL_V = 0x6B;
 
static const uint8_t BL0910_REG_RMS_GAIN_1 = 0x6C;
static const uint8_t BL0910_REG_RMS_GAIN_2 = 0x6D;
static const uint8_t BL0910_REG_RMS_GAIN_3 = 0x6E;
static const uint8_t BL0910_REG_RMS_GAIN_4 = 0x6F;
static const uint8_t BL0910_REG_RMS_GAIN_5 = 0x70;
static const uint8_t BL0910_REG_RMS_GAIN_6 = 0x71;
static const uint8_t BL0910_REG_RMS_GAIN_7 = 0x72;
static const uint8_t BL0910_REG_RMS_GAIN_8 = 0x73;
static const uint8_t BL0910_REG_RMS_GAIN_9 = 0x74;
static const uint8_t BL0910_REG_RMS_GAIN_10 = 0x75;
static const uint8_t BL0910_REG_RMS_GAIN_11 = 0x76;
 
static const uint8_t BL0910_REG_RMS_OFFSET_1 = 0x77;
static const uint8_t BL0910_REG_RMS_OFFSET_2 = 0x78;
static const uint8_t BL0910_REG_RMS_OFFSET_3 = 0x79;
static const uint8_t BL0910_REG_RMS_OFFSET_4 = 0x7A;
static const uint8_t BL0910_REG_RMS_OFFSET_5 = 0x7B;
static const uint8_t BL0910_REG_RMS_OFFSET_6 = 0x7C;
static const uint8_t BL0910_REG_RMS_OFFSET_7 = 0x7D;
static const uint8_t BL0910_REG_RMS_OFFSET_8 = 0x7E;
static const uint8_t BL0910_REG_RMS_OFFSET_9 = 0x7F;
static const uint8_t BL0910_REG_RMS_OFFSET_10 = 0x80;
static const uint8_t BL0910_REG_RMS_OFFSET_11 = 0x81;
 
 // active power small signal compensation register, 12 bit two's complement (register is 24 bit), default: 0x000
static const uint8_t BL0910_REG_WA_LOW_OFFSET_1_2 = 0x82;
static const uint8_t BL0910_REG_WA_LOW_OFFSET_3_4 = 0x83;
static const uint8_t BL0910_REG_WA_LOW_OFFSET_5_6 = 0x84;
static const uint8_t BL0910_REG_WA_LOW_OFFSET_7_8 = 0x85;
static const uint8_t BL0910_REG_WA_LOW_OFFSET_9_10 = 0x86;
 
static const uint8_t BL0910_REG_FVAR_LOW_OFFSET = 0x87;
 
 // [11:0] active power anti-creep threshold register, 12 bit unsigned number, default: 0x04C
 // [23:12] reactive power anti-creep threshold register, 12 bit unsigned number, default: 0x04C
 // 24 bit unsigned number, default: 0x04C04C
static const uint8_t BL0910_REG_VAR_CREEP_WA_CREEP = 0x88;
 
 // total power anti-creep threshold register, 12 bit unsigned number, default: 0x000
static const uint8_t BL0910_REG_WA_CREEP2 = 0x89;
 
 // effective value anti-creep threshold register, 12 bit unsigned number, default: 0x200
static const uint8_t BL0910_REG_RMS_CREEP = 0x8A;
 
static const uint8_t BL0910_REG_FAST_RMS_CTRL = 0x8B;
 
 // peak threshold register, 24 bit number, deafult: 0xFFFFFF
 // [11:0] voltage peak threshold, default: 0xFFF
 // [23:12] current peak threshold, default: 0xFFF
static const uint8_t BL0910_REG_I_PKLVL_V_PKLVL = 0x8C;
 
static const uint8_t BL0910_REG_SAGCYC_ZXTOUT = 0x8E;
static const uint8_t BL0910_REG_SAGLVL_LINECYC = 0x8F;
 
static const uint8_t BL0910_REG_FLAG_CTRL = 0x90;
static const uint8_t BL0910_REG_FLAG_CTRL1 = 0x91;
static const uint8_t BL0910_REG_FLAG_CTRL2 = 0x92;
 
 // ADC shutdown register, 11 bit number, default: 0x000
static const uint8_t BL0910_REG_ADC_PD = 0x93;
 
 // temperature control register, 16 bit number, default: 0x07FF
static const uint8_t BL0910_REG_TPS_CTRL = 0x94;
 
 // external temperature coefficient register, 16 bit number, default: 0x0000
static const uint8_t BL0910_REG_TPS2_A_B = 0x95;
 
static const uint8_t BL0910_REG_MODE1 = 0x96;
static const uint8_t BL0910_REG_MODE2 = 0x97;
static const uint8_t BL0910_REG_MODE = 0x98;
 
static const uint8_t BL0910_REG_MASK1 = 0x9A;
 
static const uint8_t BL0910_REG_RST_ENG = 0x9D;
 
static const uint8_t BL0910_REG_USR_WRPROT = 0x9E;
 
static const uint8_t BL0910_REG_SOFT_RESET = 0x9F;
 
 // channel gain calibration register, 16 bit two's complement, default: 0x0000
static const uint8_t BL0910_REG_CHANNEL_GAIN_1 = 0xA0;
static const uint8_t BL0910_REG_CHANNEL_GAIN_2 = 0xA1;
static const uint8_t BL0910_REG_CHANNEL_GAIN_3 = 0xA2;
static const uint8_t BL0910_REG_CHANNEL_GAIN_4 = 0xA3;
static const uint8_t BL0910_REG_CHANNEL_GAIN_5 = 0xA4;
static const uint8_t BL0910_REG_CHANNEL_GAIN_6 = 0xA5;
static const uint8_t BL0910_REG_CHANNEL_GAIN_7 = 0xA6;
static const uint8_t BL0910_REG_CHANNEL_GAIN_8 = 0xA7;
static const uint8_t BL0910_REG_CHANNEL_GAIN_9 = 0xA8;
static const uint8_t BL0910_REG_CHANNEL_GAIN_10 = 0xA9;
static const uint8_t BL0910_REG_CHANNEL_GAIN_11 = 0xAA;
 
 // channel offset calibration register, 16 bit two's complement, default: 0x0000
static const uint8_t BL0910_REG_CHANNEL_OFFSET_1 = 0xAB;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_2 = 0xAC;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_3 = 0xAD;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_4 = 0xAE;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_5 = 0xAF;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_6 = 0xB0;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_7 = 0xB1;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_8 = 0xB2;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_9 = 0xB3;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_10 = 0xB4;
static const uint8_t BL0910_REG_CHANNEL_OFFSET_11 = 0xB5;
 
 //active power gain correction register, 16bit signed number, default: 0x0000
static const uint8_t BL0910_REG_WATT_GAIN_1 = 0xB6;
static const uint8_t BL0910_REG_WATT_GAIN_2 = 0xB7;
static const uint8_t BL0910_REG_WATT_GAIN_3 = 0xB8;
static const uint8_t BL0910_REG_WATT_GAIN_4 = 0xB9;
static const uint8_t BL0910_REG_WATT_GAIN_5 = 0xBA;
static const uint8_t BL0910_REG_WATT_GAIN_6 = 0xBB;
static const uint8_t BL0910_REG_WATT_GAIN_7 = 0xBC;
static const uint8_t BL0910_REG_WATT_GAIN_8 = 0xBD;
static const uint8_t BL0910_REG_WATT_GAIN_9 = 0xBE;
static const uint8_t BL0910_REG_WATT_GAIN_10 = 0xBF;
 
 //active power offset correction register, 16bit signed number, default: 0x0000
static const uint8_t BL0910_REG_WATT_OFFSET_1 = 0xC0;
static const uint8_t BL0910_REG_WATT_OFFSET_2 = 0xC1;
static const uint8_t BL0910_REG_WATT_OFFSET_3 = 0xC2;
static const uint8_t BL0910_REG_WATT_OFFSET_4 = 0xC3;
static const uint8_t BL0910_REG_WATT_OFFSET_5 = 0xC4;
static const uint8_t BL0910_REG_WATT_OFFSET_6 = 0xC5;
static const uint8_t BL0910_REG_WATT_OFFSET_7 = 0xC6;
static const uint8_t BL0910_REG_WATT_OFFSET_8 = 0xC7;
static const uint8_t BL0910_REG_WATT_OFFSET_9 = 0xC8;
static const uint8_t BL0910_REG_WATT_OFFSET_10 = 0xC9;
 
static const uint8_t BL0910_REG_VAR_GAIN = 0xCA;
static const uint8_t BL0910_REG_VAR_OFFSET = 0xCB;
 
static const uint8_t BL0910_REG_VA_GAIN = 0xCC;
static const uint8_t BL0910_REG_VA_OFFSET = 0xCD;
 
static const uint8_t BL0910_REG_CFDIV = 0xCE;
 
static const uint8_t BL0910_REG_OTP_CHECKSUM1 = 0xD0;


static const float BL0910_IREF = (12875.0f * 33.0f) / (1.097f * 2000.0f / 1000.0f); // magic1 * Rburden1 / Vref * CT ratio
static const float BL0910_UREF = (13162.0f * 220.0f) / (1.097f * 132.0f); // magic2 * Rburden2 / Vref * PT primary resistance
static const float BL0910_PREF = (40.4125f * 33.0f * 220.0f * 1000.0f / 2000.0f) / (1.097f * 1.097f * 132.0f); // magic3 * Rburden1 * Rburden2 / Vref * Vref * PT primary resistance * CT ratio
static const float BL0910_EREF = (3600000.0f * 16.0f * BL0910_PREF) / (4194304.0f * 0.032768f * 16.0f);

float voltage = 0;
float current1 = 0;
float power1 = 0;
float energy1 = 0;


void bl0910_startSPI()
{
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
  digitalWrite(BL0910_CS_PIN, LOW);
}


void bl0910_endSPI()
{
  digitalWrite(BL0910_CS_PIN, HIGH);
  SPI.endTransaction();
}


uint8_t bl0910_checksum_calc(uint8_t* data)
{
  uint8_t checksum = 0;
  for (int i = 0; i < 5; i++)
  {
    checksum += data[i];
  }
  checksum &= 0xFF;
  checksum ^= 0xFF;
  
  return checksum;
}


uint8_t bl0910_checksum_check_ok(uint8_t* data)
{
  uint8_t checksum = 0;
  for (int i = 0; i < 5; i++)
  {
    checksum += data[i];
  }
  checksum &= 0xFF;
  checksum ^= 0xFF; // bit invert
  
  if (checksum == data[5]) // checksum is byte 6
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


void bl0910_write_data(uint8_t addr, uint32_t data)
{
  uint8_t packet[6] = {0};
  
  packet[0] = BL0910_WRITE_COMMAND;
  packet[1] = addr;
  packet[2] = (data >> 16) & 0xFF;
  packet[3] = (data >> 8) & 0xFF;
  packet[4] = data & 0xFF;
  packet[5] = bl0910_checksum_calc(packet);
  bl0910_startSPI();
  for (uint8_t i = 0; i < 6; i++)
  {
    SPI.transfer(packet[i]);
  }
  bl0910_endSPI();
}


void bl0910_write_data(uint8_t addr, uint8_t data_h, uint8_t data_m, uint8_t data_l)
{
  uint8_t packet[6] = {0};
  
  packet[0] = BL0910_WRITE_COMMAND;
  packet[1] = addr;
  packet[2] = data_h;
  packet[3] = data_m;
  packet[4] = data_l;
  packet[5] = bl0910_checksum_calc(packet);
  bl0910_startSPI();
  for (uint8_t i = 0; i < 6; i++)
  {
    SPI.transfer(packet[i]);
  }
  bl0910_endSPI();
}


int32_t bl0910_read_data(uint8_t addr)
{
  int32_t data = 0;
  uint8_t packet[6] = {0};
  
  packet[0] = BL0910_READ_COMMAND;
  packet[1] = addr;
  bl0910_startSPI();
  SPI.transfer(packet[0]);
  SPI.transfer(packet[1]);
  for (uint8_t i = 2; i < 6; i++)
  {
    packet[i] = SPI.transfer(0x00);
  }
  bl0910_endSPI();
  
  if(bl0910_checksum_check_ok(packet))
  {
    data = (((int8_t)packet[2]) << 16) | (packet[3] << 8) | packet[4];
    return data;
  }
  else
  {
    return 0xFF000000;
  }
}

 
void bl0910_init(void)
{  
  bl0910_write_data(BL0910_REG_SOFT_RESET, 0x5A, 0x5A, 0x5A); // Reset to default
  bl0910_write_data(BL0910_REG_USR_WRPROT, 0x00, 0x55, 0x55); // Enable User Operation Write
  bl0910_write_data(BL0910_REG_MODE, 0x00, 0x00, 0x00);
  bl0910_write_data(BL0910_REG_TPS_CTRL, 0x00, 0x07, 0xFF);
  bl0910_write_data(BL0910_REG_FAST_RMS_CTRL, 0x40, 0xFF, 0xFF);
  bl0910_write_data(BL0910_REG_GAIN1, 0x00, 0x00, 0x00);
}


float bl0910_getVoltage(void)
{
  float voltage = (float)bl0910_read_data(BL0910_REG_RMS_11) / BL0910_UREF;
  
  return voltage;
}


float bl0910_getCurrent(uint8_t channel)
{
  float current = 0;
  
  switch(channel)
  {
    case 1: current = (float)bl0910_read_data(BL0910_REG_RMS_1); break;
    case 2: current = (float)bl0910_read_data(BL0910_REG_RMS_2); break;
    case 3: current = (float)bl0910_read_data(BL0910_REG_RMS_3); break;
    case 4: current = (float)bl0910_read_data(BL0910_REG_RMS_4); break;
    case 5: current = (float)bl0910_read_data(BL0910_REG_RMS_5); break;
    case 6: current = (float)bl0910_read_data(BL0910_REG_RMS_6); break;
    case 7: current = (float)bl0910_read_data(BL0910_REG_RMS_7); break;
    case 8: current = (float)bl0910_read_data(BL0910_REG_RMS_8); break;
    case 9: current = (float)bl0910_read_data(BL0910_REG_RMS_9); break;
    case 10: current = (float)bl0910_read_data(BL0910_REG_RMS_10); break;
    default: current = 0; break;
  }
  current /= BL0910_IREF;
  
  return current;
}


float bl0910_getPower(uint8_t channel)
{
  float power = 0;
  
  switch(channel)
  {
    case 1: power = (float)bl0910_read_data(BL0910_REG_WATT_1); break;
    case 2: power = (float)bl0910_read_data(BL0910_REG_WATT_2); break;
    case 3: power = (float)bl0910_read_data(BL0910_REG_WATT_3); break;
    case 4: power = (float)bl0910_read_data(BL0910_REG_WATT_4); break;
    case 5: power = (float)bl0910_read_data(BL0910_REG_WATT_5); break;
    case 6: power = (float)bl0910_read_data(BL0910_REG_WATT_6); break;
    case 7: power = (float)bl0910_read_data(BL0910_REG_WATT_7); break;
    case 8: power = (float)bl0910_read_data(BL0910_REG_WATT_8); break;
    case 9: power = (float)bl0910_read_data(BL0910_REG_WATT_9); break;
    case 10: power = (float)bl0910_read_data(BL0910_REG_WATT_10); break;
    default: power = 0; break;
  }
  power /= BL0910_PREF;
  
  return power;
}


float bl0910_getEnergy(uint8_t channel)
{
  float energy = 0;
  
  switch(channel)
  {
    case 1: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_1); break;
    case 2: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_2); break;
    case 3: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_3); break;
    case 4: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_4); break;
    case 5: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_5); break;
    case 6: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_6); break;
    case 7: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_7); break;
    case 8: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_8); break;
    case 9: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_9); break;
    case 10: energy = (float)bl0910_read_data(BL0910_REG_CF_CNT_10); break;
    default: energy = 0; break;
  }
  energy /= BL0910_EREF;
  
  return energy;
}


void setup() {
  Serial0.begin(115200);
  Serial0.println("BL0910 test");
  Serial0.println();
  SPI.begin(5, 19, 18, BL0910_CS_PIN);
  pinMode(BL0910_CS_PIN, OUTPUT);
  digitalWrite(BL0910_CS_PIN, HIGH);
  bl0910_init();
}

void loop()
{
  voltage = bl0910_getVoltage();
  current1 = bl0910_getCurrent(1);
  power1 = bl0910_getPower(1);
  energy1 = bl0910_getEnergy(1);

  Serial0.print("Voltage=");
  Serial0.print(voltage);
  Serial0.println('V');
  Serial0.print("Current=");
  Serial0.print(current1);
  Serial0.println('A');
  Serial0.print("Power=");
  Serial0.print(power1);
  Serial0.println('W');
  Serial0.print("Energy=");
  Serial0.print(energy1);
  Serial0.println("kWh");
  Serial0.println();
  delay(60000);
}
