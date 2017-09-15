#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

static const int pin = 0;
static volatile os_timer_t some_timer;

void ICACHE_FLASH_ATTR
user_set_station_config(void) {
  char ssid[32] = "Honeynet";
  char pass[64] = "MateMateMate";

  struct station_config stationConf;

  stationConf.bssid_set = 0;

  os_memcpy(&stationConf.ssid, ssid, 32);
  os_memcpy(&stationConf.password, pass, 64);
  wifi_station_set_config(&stationConf);
}

void user_init() {
  // init gpio sussytem
  gpio_init();

  // configure UART TXD to be GPIO1, set as output
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_GPIO1); 
  gpio_output_set(0, 0, (1 << pin), 0);

  wifi_set_opmode(STATION_MODE);
  user_set_station_config();
  
  gpio_output_set((1 << pin), 0, 0, 0);
}
