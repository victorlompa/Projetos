#include "Arduino.h"
#include "AS5600.h"
#include "Wire.h"

AMS_5600::AMS_5600()
{
}

void AMS_5600::setOutPut(uint8_t mode)
{
  int _conf_lo = _addr_conf+1; // lower byte address
  uint8_t config_status;
  config_status = readOneByte(_conf_lo);
  if (mode == 1) {
    config_status = config_status & 0xcf;
  } else {
    uint8_t config_status;
    config_status = readOneByte(_conf_lo);
    if (mode == 1)
      config_status = config_status & 0xcf;
    else
      config_status = config_status & 0xef;
    writeOneByte(_conf_lo, lowByte(config_status));
  }
}

int AMS_5600::getAddress()
{
  return _ams5600_Address;
}

word AMS_5600::setMaxAngle(word newMaxAngle)
{
  word _maxAngle;
  if (newMaxAngle == -1)
    _maxAngle = getRawAngle();
  else
    _maxAngle = newMaxAngle;

  writeOneByte(_addr_mang, highByte(_maxAngle));
  delay(2);
  writeOneByte(_addr_mang+1, lowByte(_maxAngle));
  delay(2);

  word retVal = readTwoBytesSeparately(_addr_mang);
  return retVal;
}

word AMS_5600::getMaxAngle()
{
  return readTwoBytesSeparately(_addr_mang);
}

word AMS_5600::setStartPosition(word startAngle)
{
  word _rawStartAngle;
  if (startAngle == -1)
    _rawStartAngle = getRawAngle();
  else
    _rawStartAngle = startAngle;

  writeOneByte(_addr_zpos, highByte(_rawStartAngle));
  delay(2);
  writeOneByte(_addr_zpos+1, lowByte(_rawStartAngle));
  delay(2);
  word _zPosition = readTwoBytesSeparately(_addr_zpos);

  return (_zPosition);
}

word AMS_5600::getStartPosition()
{
  return readTwoBytesSeparately(_addr_zpos);
}

word AMS_5600::setEndPosition(word endAngle)
{
  word _rawEndAngle;
  if (endAngle == -1)
    _rawEndAngle = getRawAngle();
  else
    _rawEndAngle = endAngle;

  writeOneByte(_addr_mpos, highByte(_rawEndAngle));
  delay(2);
  writeOneByte(_addr_mpos+1, lowByte(_rawEndAngle));
  delay(2);
  word _mPosition = readTwoBytesSeparately(_addr_mpos);

  return (_mPosition);
}

word AMS_5600::getEndPosition()
{
  word retVal = readTwoBytesSeparately(_addr_mpos);
  return retVal;
}

word AMS_5600::getRawAngle()
{
  return readTwoBytesTogether(_addr_raw_angle);
}

word AMS_5600::getScaledAngle()
{
  return readTwoBytesTogether(_addr_angle);
}

int AMS_5600::detectMagnet()
{
  int magStatus;
  int retVal = 0;
  magStatus = readOneByte(_addr_status);

  if (magStatus & 0x20)
    retVal = 1;

  return retVal;
}

int AMS_5600::getMagnetStrength()
{
  int magStatus;
  int retVal = 0;
  magStatus = readOneByte(_addr_status);
  if (detectMagnet() == 1) {
    retVal = 2;
    if (magStatus & 0x10)
      retVal = 1;
    else if (magStatus & 0x08)
      retVal = 3;
  }

  return retVal;
}

int AMS_5600::getAgc()
{
  return readOneByte(_addr_agc);
}

word AMS_5600::getMagnitude()
{
  return readTwoBytesTogether(_addr_magnitude);
}

word AMS_5600::getConf()
{
  return readTwoBytesSeparately(_addr_conf);
}

void AMS_5600::setConf(word _conf)
{
  writeOneByte(_addr_conf, highByte(_conf));
  delay(2);
  writeOneByte(_addr_conf+1, lowByte(_conf));
  delay(2);
}

int AMS_5600::getBurnCount()
{
  return readOneByte(_addr_zmco);
}

int AMS_5600::burnAngle()
{
  word _zPosition = getStartPosition();
  word _mPosition = getEndPosition();
  word _maxAngle = getMaxAngle();

  int retVal = 1;
  if (detectMagnet() == 1) {
    if (getBurnCount() < 3) {
      if ((_zPosition == 0) && (_mPosition == 0))
        retVal = -3;
      else
        writeOneByte(_addr_burn, 0x80);
    }
    else
      retVal = -2;
  } else
    retVal = -1;

  return retVal;
}

int AMS_5600::burnMaxAngleAndConfig()
{
  word _maxAngle = getMaxAngle();

  int retVal = 1;
  if (getBurnCount() == 0) {
    if (_maxAngle * 0.087 < 18)
      retVal = -2;
    else
      writeOneByte(_addr_burn, 0x40);
  }
  else
    retVal = -1;

  return retVal;
}

int AMS_5600::readOneByte(int in_adr)
{
  int retVal = -1;
  Wire.beginTransmission(_ams5600_Address);
  Wire.write(in_adr);
  Wire.endTransmission();
  Wire.requestFrom(_ams5600_Address, (uint8_t) 1);
  while (Wire.available() == 0)
    ;
  retVal = Wire.read();

  return retVal;
}

word AMS_5600::readTwoBytesTogether(int addr_in)
{
  Wire.beginTransmission(_ams5600_Address);
  Wire.write(addr_in);
  Wire.endTransmission();
  Wire.requestFrom(_ams5600_Address, (uint8_t) 2);
  while (Wire.available() < 2)
    ;
  
  int highByte = Wire.read();
  int lowByte  = Wire.read();

  return ( highByte << 8 ) | lowByte;
}

word AMS_5600::readTwoBytesSeparately(int addr_in)
{
  int highByte = readOneByte(addr_in  );
  int lowByte  = readOneByte(addr_in+1);
  return ( highByte << 8 ) | lowByte;
}

void AMS_5600::writeOneByte(int adr_in, int dat_in)
{
  Wire.beginTransmission(_ams5600_Address);
  Wire.write(adr_in);
  Wire.write(dat_in);
  Wire.endTransmission();
}

float convertRawAngleToDegrees(word newAngle)
{
  /* 0 - 4095 Segmentos = 0.087 de um grau*/
  float retVal = newAngle * 0.087;
  return retVal;
}


/**********  END OF AMS 5600 CALSS *****************/