
---

## 🧾 **README.md (English)**

### 📘 Overview

`NTC` is a lightweight and portable library for calculating temperature using an NTC thermistor and ADC readings.
It provides an easy-to-use interface for initialization, runtime configuration modification, and resource release.

---

### ⚙️ Features

* Simple and clean API
* Supports dynamic configuration
* Calculates temperature using the Beta constant model
* Designed for embedded systems (MCUs like S32K, STM32, ESP32, etc.)

---

### 📂 File Structure

```
ntc.h
ntc.c
```

---

### 🧠 How It Works

The NTC thermistor is connected in a voltage divider circuit.
The ADC measures the voltage across the NTC resistor, then the library calculates its resistance and temperature using the **B-value equation**:

[
T = \frac{1}{\frac{1}{298.15} + \frac{1}{B} \ln\left(\frac{R}{R_{25}}\right)} - 273.15
]

---

### 🧩 API Reference

#### `Ntc_Sta_t Ntc_Init(Ntc_Handle_t *handle, Ntc_Conf_t *conf);`

**Description:**
Initializes an NTC object and copies the configuration parameters.
**Return:** `NTC_OK` if successful, otherwise `NTC_ERR`.

---

#### `Ntc_Sta_t Ntc_CalTempture(Ntc_Handle_t handle, uint16_t adc, float *buffer);`

**Description:**
Calculates the temperature (in °C) from the ADC reading.
**Parameters:**

* `handle`: Initialized NTC handle
* `adc`: ADC conversion result
* `buffer`: Pointer to store calculated temperature
  **Return:** `NTC_OK` on success

---

#### `Ntc_Sta_t Ntc_Modify(Ntc_Handle_t *handle, Ntc_Conf_t *conf);`

**Description:**
Updates configuration values of the NTC object.
**Return:** `NTC_OK` if updated successfully.

---

#### `Ntc_Sta_t Ntc_Delete(Ntc_Handle_t *handle);`

**Description:**
Frees allocated resources and invalidates the handle.
**Return:** `NTC_OK` if successful.

---

### 🧱 Configuration Structure

```c
typedef struct {
    uint32_t adcMax;     // ADC max value (e.g. 4095)
    float Vref;          // Reference voltage (V)
    uint16_t Bvalue;     // Beta constant of NTC
    uint32_t R_fixed;    // Fixed resistor in divider circuit (Ω)
    uint16_t R25;        // NTC resistance at 25°C (Ω)
} Ntc_Conf_t;
```

---

### 💡 Example Usage

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

    float temperature;

    Ntc_Init(&ntc, &conf);
    Ntc_CalTempture(ntc, 2048, &temperature); // Example ADC value
    printf("Temperature = %.2f°C\n", temperature);
    Ntc_Delete(&ntc);
}
```

---

### ⚠️ Notes

* Avoid using `calloc`/`free` in real-time critical systems (consider static allocation).
* Ensure ADC readings never exceed reference voltage to avoid division by zero.
* Add filtering if ADC noise is significant.

---
