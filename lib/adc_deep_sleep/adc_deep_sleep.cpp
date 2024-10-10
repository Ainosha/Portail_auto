#include <adc_deep_sleep.h>

static void init_ulp_program();
/*
   Based on :
   - https://docs.espressif.com/projects/esp-idf/en/v4.2.3/esp32/api-guides/ulp_macros.html
   - https://forum.arduino.cc/t/esp32-ulp-program-to-read-adc-when-in-deep-sleep/987884
   - https://github.com/SensorsIot/ESP32-ULP-Arduino-IDE
   - https://www.esp32.com/viewtopic.php?t=11215
*/

RTC_DATA_ATTR unsigned int ulp_adc_value = 0;
unsigned int ulp_adc_threshold = 1 * (4095 / 3.9);  // 1 volt

const ulp_insn_t ulp_adc_program[] = {
    I_DELAY(32000),                   // Wait until ESP32 goes to deep sleep
    M_LABEL(1),                       // LABEL 1
    I_ADC(R0, 0, 0),                  // Read ADC value to reg. R0
    M_BGE(2, ulp_adc_threshold),      // If average ADC value from reg. R0 is higher or equal than threshold, go to LABEL 2
    M_BX(1),                          // Go to LABEL 1
    M_LABEL(2),                       // LABEL 3
    I_MOVI(R1, ((unsigned int)&ulp_adc_value - (unsigned int)RTC_SLOW_MEM) / 4), // Set reg. R1 to adress of ulp_adc_value
    I_ST(R0, R1, 0),                                                             // Copy result of ADC to R1 adress, so ulp_adc_value
    I_WAKE(),                                                                    // Wake up ESP32
    I_END(),                                                                     // Stop ULP program timer
    I_HALT()                                                                     // Halt the coprocessor
};
	
void setup_adc_deep_sleep()
{
    Serial.begin(115200);
 
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    switch(wakeup_reason)
    {
      
      case ESP_SLEEP_WAKEUP_UNDEFINED : // First run, initialize ULP program
        printf("Not ULP wakeup\n");
        init_ulp_program();
        break;
 
      case ESP_SLEEP_WAKEUP_ULP : 
        /* PROCESS */
        wakeup_process();
        /* PROCESS */
        
        printf("Deep sleep wakeup\n");
        ulp_adc_value &= UINT16_MAX; /* Check https://docs.espressif.com/projects/esp-idf/en/v4.2.3/esp32/api-guides/ulp_macros.html?highlight=i_st#c.I_ST */
        printf("ULP Value=%d was above threshold (%d)\n", ulp_adc_value, ulp_adc_threshold);

        /* E.g. check current value, do not forget to reactivate adc1_ulp_enable wich is disabled by adc1_get_raw */
        int value = adc1_get_raw(ADC1_CHANNEL_0);
        printf("Current value=%d\n", value);
        adc1_ulp_enable();
        break;
    }
    delay(100);
    /* Start the program */
    ESP_ERROR_CHECK(ulp_run(0));
    ESP_ERROR_CHECK(esp_sleep_enable_ulp_wakeup());
    esp_deep_sleep_start();
}

static void init_ulp_program()
{
    /* Configure ADC channel */
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_ulp_enable();

    /* Set ULP wake up period to 100ms */
    ulp_set_wakeup_period(0, 100 * 1000);

    /* Load the ULP¨program from ULP macro */
    size_t size = sizeof(ulp_adc_program) / sizeof(ulp_insn_t);
    ulp_process_macros_and_load(0, ulp_adc_program, &size);
}