#ifndef ADIS16364_h
#define ADIS16405_h
#include "Arduino.h"
#include <SPI.h>

// convient macros for accessing burst mode sensor data
#define SUPPLY 0
#define XGYRO  1
#define YGYRO  2
#define ZGYRO  3
#define XACCEL 4
#define YACCEL 5
#define ZACCEL 6
#define XTEMP  7
#define YTEMP  8
#define ZTEMP  9
#define TEMP   10
#define ANALOG 11

// Memory map
#define FLASH_CNT   0x00  // Flash memory write count  N/A
#define SUPPLY_OUT  0x02  // Power supply measurement  See Table 9
#define XGYRO_OUT   0x04  // X-axis gyroscope output  See Table 9
#define YGYRO_OUT   0x06  // Y-axis gyroscope output  See Table 9
#define ZGYRO_OUT   0x08  // Z-axis gyroscope output  See Table 9
#define XACCL_OUT   0x0A  // X-axis accelerometer output  See Table 9
#define YACCL_OUT   0x0C  // Y-axis accelerometer output  See Table 9
#define ZACCL_OUT   0x0E  // Z-axis accelerometer output  See Table 9
#define XTEMP_OUT   0x10  // X-axis gyroscope temperature output  See Table 9
#define YTEMP_OUT   0x12  // Y-axis gyroscope temperature output  See Table 9
#define ZTEMP_OUT   0x14  // Z-axis gyroscope temperature output  See Table 9
#define AUX_ADC     0x18  // Auxiliary ADC output  See Table 9
#define XGYRO_OFF   0x1A  // X-axis gyroscope bias offset factor  See Table 15
#define YGYRO_OFF   0x1C  // Y-axis gyroscope bias offset factor  See Table 15
#define ZGYRO_OFF   0x1E  // Z-axis gyroscope bias offset factor  See Table 15
#define XACCL_OFF   0x20  // X-axis acceleration bias offset factor  See Table 16
#define YACCL_OFF   0x22  // Y-axis acceleration bias offset factor  See Table 16
#define ZACCL_OFF   0x24  // Z-axis acceleration bias offset factor  See Table 16
#define ALM_MAG1    0x40  // Alarm 1 amplitude threshold  See Table 27
#define ALM_MAG2    0x42  // Alarm 2 amplitude threshold  See Table 27
#define ALM_SMPL1   0x44  // Alarm 1 sample size  See Table 28
#define ALM_SMPL2   0x46  // Alarm 2 sample size  See Table 28
#define ALM_CTRL    0x48  // Alarm control  See Table 29
#define AUX_DAC     0x4A  // Auxiliary DAC data  See Table 23
#define GPIO_CTRL   0x32  // Auxiliary digital input/output control  See Table 21
#define MSC_CTRL    0x34  // Data ready, self-test, miscellaneous  See Table 22
#define SMPL_PRD    0x36  // Internal sample period (rate) control  See Table 18
#define SENS_AVG    0x38  // Dynamic range and digital filter control  See Table 17
#define SLP_CNT     0x3A  // Sleep mode control  See Table 19
#define DIAG_STAT   0x3C  // System status  See Table 26
#define GLOB_CMD    0x3E  // System commands  See Table 17
#define LOT_ID1     0x52  // Lot Identification Code 1  See Table 32
#define LOT_ID2     0x54  // Lot Identification Code 2  See Table 32
#define PROD_ID     0x56  // Product identification, ADIS16364  See Table 32
#define SERIAL_NUM  0x58  // Serial number  See Table 32

// ADIS16405 class definition
class ADIS16405{

public:

  double sensor[12];
  double xacc;
  // Constructor with configurable CS pin, and Destructor
  ADIS16405(int CS);
  ~ADIS16405();

  // Burst read
  void burst_read();
  
  // debug
  void debug();
  
  // Regsiter read/write, and two's complement converters
  unsigned int read(unsigned char nbits, unsigned char reg);
  void write(unsigned char reg, unsigned int value);
  double signed_double(unsigned char nbits, unsigned int num);
  unsigned int twos_comp(double num);
  
  // Get methods
  unsigned int device_id();
  double x_gyro_offset();
  double y_gyro_offset();
  double z_gyro_offset();
  double x_accel_offset();
  double y_accel_offset();
  double z_accel_offset();

  // Offset set methods and Gyro null
  void x_gyro_offset(double value);
  void y_gyro_offset(double value);
  void z_gyro_offset(double value);
  void x_accel_offset(double value);
  void y_accel_offset(double value);
  void z_accel_offset(double value);
  void gyro_null();        // Not Tested
  void gyro_prec_null();   // Not Tested
  void sens_avg();
  // Power managment
  void low_power_mode();   // Not Tested
  void normal_mode();      // Not Tested
  void sleep();            // Not Tested
  void sleep(double dur);  // Not Tested
  void wake();     // Not Tested
  //read xacc
  void xacc_read();
    
  // System Settings
  void factory_reset();
  
private:

  // Chip select pin
  int CS;
  
  // low power mode flag
  bool low_power;
  
  // Set SPI Settings
  void set_SPI();

  // Delay one SCLK cycle
  void delay_cycle();
};
#endif
