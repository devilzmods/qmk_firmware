//Added to enable Bluetooth through an Adafruit BLE SPI Friend.

#define HAL_USE_SPI TRUE
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
#include_next "halconf.h"
