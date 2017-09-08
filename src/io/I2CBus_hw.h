
#ifdef ARDUINO_ARCH_ESP8266
  #define I2CBUS_SET_PINS
  #define I2CBUS_SET_PINS_ON_BEGIN
#endif
#ifdef ARDUINO_ARCH_ESP32
  #define I2CBUS_SET_PINS
  #define I2CBUS_SET_PINS_ON_BEGIN
#endif
#ifdef ARDUINO_ARCH_AVR
  #define I2CBUS_SET_PINS_NOT_IMPLEMENTED
#endif
#ifndef I2CBUS_SET_PINS
  #warning "No support for setting SDL and SDA pins"
#endif

#ifdef ARDUINO_ARCH_ESP8266
  #define I2CBUS_FREQUENCY_MAX 700000
#endif
#ifdef ARDUINO_ARCH_ESP32
  #define I2CBUS_FREQUENCY_MAX 900000
#endif
#ifdef ARDUINO_ARCH_AVR
  #define I2CBUS_FREQUENCY_MAX 400000
#endif
#ifndef I2CBUS_FREQUENCY_MAX
  #warning "No max I2C frequency defined for ARCH"
  #define I2CBUS_FREQUENCY_MAX 100000
#endif
