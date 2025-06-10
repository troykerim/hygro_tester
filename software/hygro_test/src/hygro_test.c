#include "PmodHYGRO.h"
#include "sleep.h"
#include "xil_printf.h"
#include "xparameters.h"

//#define TIMER_FREQ_HZ 100000000  // AXI clock on Zynq
#define TIMER_FREQ_HZ 50000000
PmodHYGRO myDevice;

void DemoInitialize();
void DemoRun();
//void DemoCleanup();

int main() {
   DemoInitialize();
   DemoRun();
   //DemoCleanup();
   xil_printf("Test!\n\r");
   return 0;
}

void DemoInitialize() {
   xil_printf("Init Started\n\r");
   HYGRO_begin(
      &myDevice,
      XPAR_PMODHYGRO_0_AXI_LITE_IIC_BASEADDR,
      0x40,
      XPAR_PMODHYGRO_0_AXI_LITE_TMR_BASEADDR,
      XPAR_PMODHYGRO_0_DEVICE_ID,
      TIMER_FREQ_HZ
   );
   xil_printf("Init Done\n\r");
}


void DemoRun() {
   float temp_degc, hum_perrh, temp_degf;
   while (1) {
      temp_degc = HYGRO_getTemperature(&myDevice);
      temp_degf = HYGRO_tempC2F(temp_degc);
      hum_perrh = HYGRO_getHumidity(&myDevice);
      xil_printf("Temperature: %d.%02d deg F  Humidity: %d.%02d RH\n\r",
         (int) temp_degf,
         ((int) (temp_degf * 100)) % 100,
         (int) hum_perrh,
         ((int) (hum_perrh * 100)) % 100);
      sleep(1);
   }
}
