
#ifdef ARDUINO_ARCH_ESP8266
  #define I2CBUS_SET_PINS_ON_BEGIN
  #define I2CBUS_SET_PINS
#endif
#ifdef ARDUINO_ARCH_ESP32
  #define I2CBUS_SET_PINS_ON_BEGIN
  #define I2CBUS_SET_PINS
#endif
#ifdef ARDUINO_ARCH_AVR
  #define I2CBUS_NO_SET_PINS
#endif
#ifndef I2CBUS_SET_PINS
  #warning "No support for setting SDL and SDA pins"
#endif

#ifdef ARDUINO_ARCH_ESP8266
  #define I2CBUS_FREQUENCY_BY_FUNCTION
  #define I2CBUS_FREQUENCY 700000
#endif
#ifdef ARDUINO_ARCH_ESP32
  #define I2CBUS_FREQUENCY_BY_FUNCTION
  #define I2CBUS_FREQUENCY 800000
#endif
#ifdef ARDUINO_ARCH_AVR
  #define I2CBUS_FREQUENCY_BY_FUNCTION
  #define I2CBUS_FREQUENCY 400000
#endif
#ifndef I2CBUS_FREQUENCY
  #warning "No support for setting I2C bus frequency"
#endif
