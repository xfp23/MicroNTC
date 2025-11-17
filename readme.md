
---

[中文](./readme.zh.md)

# 🧾 **README.md (English)**

## 📘 Overview

`NTC` is a lightweight and portable library for calculating NTC thermistor resistance and temperature from ADC readings.
It provides APIs for initialization, configuration modification, resistance calculation, temperature calculation, and resource cleanup.

---

## 🧩 API Reference

### ⚙️ Configuration structure description

```c
typedef struct 
{
    uint32_t adcMax;     // The maximum value of ADC, for example, 4095.
    float Vref;          // ADC reference voltage
    uint16_t Bvalue;     // The constant B of the thermistor
    uint32_t R_fixed;    // Fixed resistor value in a voltage divider circuit (Ω)
    uint16_t R25;        // The resistance of the thermistor at 25°C (Ω)
} Ntc_Conf_t;
```

---

### **`Ntc_Sta_t Ntc_Init(Ntc_Handle_t *handle, Ntc_Conf_t *conf);`**

**Description:**
Initializes an NTC object and loads configuration parameters.

**Return:**
`NTC_OK` if successful, otherwise `NTC_ERR`.

---

### **`Ntc_Sta_t Ntc_CalRes(Ntc_Handle_t handle, uint16_t adc, float *result);`**

**Description:**
Calculates the NTC resistance (Ω) from an ADC reading.

**Parameters:**

* `handle` — Initialized NTC handle
* `adc` — ADC raw value
* `result` — Output resistance (Ω)

**Return:**
`NTC_OK` on success.

---

### **`Ntc_Sta_t Ntc_CalTempture(Ntc_Handle_t handle, uint16_t adc_or_res, float *buffer);`**

**Description:**
Calculates temperature (°C).
Supports input as ADC value or resistance depending on implementation.

**Parameters:**

* `handle` — Initialized NTC handle
* `adc_or_res` — ADC raw value *or* resistance value
* `buffer` — Output temperature (°C)

**Return:**
`NTC_OK` on success.

---

### **`Ntc_Sta_t Ntc_Modify(Ntc_Handle_t *handle, Ntc_Conf_t *conf);`**

**Description:**
Updates the configuration of an existing NTC object.

**Return:**
`NTC_OK` on success.

---

### **`Ntc_Sta_t Ntc_Delete(Ntc_Handle_t *handle);`**

**Description:**
Frees resources and invalidates the handle.

**Return:**
`NTC_OK` on success.

---

## 💡 Example Usage

```c
#include "ntc.h"

int main(void)
{
    Ntc_Handle_t ntc = NULL;
    Ntc_Conf_t conf = {
        .adcMax = 4095,
        .Vref = 5.0f,
        .Bvalue = 3950,
        .R_fixed = 10000,
        .R25 = 10000,
    };
    float temp; 
    float res;
    uint16_t adc = 2000;

    Ntc_Init(&ntc, &conf);
    Ntc_CalTempture(ntc, adc, &temp);
    Ntc_CalRes(ntc,adc,&res);
    printf("current temperature: %.2f °C\n", temp);
    printf("current resistance: %.2f Ω\n",res);

    Ntc_Delete(&ntc);
}
```

---
