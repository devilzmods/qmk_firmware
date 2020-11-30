//Added to enable Bluetooth through an Adafruit BLE SPI Friend.

#include_next "mcuconf.h"
#undef STM32_SPI_USESPI2
#undef STM32_SPI_USESPI3
#define STM32_SPI_USESPI2 FALSE
#define STM32_SPI_USESPI3 TRUE
