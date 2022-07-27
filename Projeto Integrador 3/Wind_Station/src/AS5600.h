#ifndef AMS_5600_h
#define AMS_5600_h

#include <Arduino.h>

class AMS_5600
{
public:
  AMS_5600(void);
  int getAddress();
  word setMaxAngle(word newMaxAngle = -1);
  word getMaxAngle();
  word setStartPosition(word startAngle = -1);
  word getStartPosition();
  word setEndPosition(word endAngle = -1);
  word getEndPosition();
  word getRawAngle();
  word getScaledAngle();
  int detectMagnet();
  int getMagnetStrength();
  int getAgc();
  word getMagnitude();
  word getConf();
  void setConf(word _conf);
  int getBurnCount();
  int burnAngle();
  int burnMaxAngleAndConfig();
  void setOutPut(uint8_t mode);
  float convertRawAngleToDegrees(word newAngle);

private:

  static const uint8_t _ams5600_Address = 0x36;
  static const uint8_t _addr_status = 0x0b;
  static const uint8_t _addr_agc    = 0x1a;
  static const uint8_t _addr_burn   = 0xff;
  static const uint8_t _addr_zmco   = 0x00; 
  static const uint8_t _addr_zpos      = 0x01;
  static const uint8_t _addr_mpos      = 0x03;
  static const uint8_t _addr_mang      = 0x05;
  static const uint8_t _addr_conf      = 0x07;
  static const uint8_t _addr_raw_angle = 0x0c;
  static const uint8_t _addr_angle     = 0x0e;
  static const uint8_t _addr_magnitude = 0x1b;

  int readOneByte(int in_adr);
  word readTwoBytesSeparately(int addr_in);
  word readTwoBytesTogether(int addr_in);
  void writeOneByte(int adr_in, int dat_in);
};
#endif