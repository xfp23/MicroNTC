#ifndef NTC_H
#define NTC_H

/**
 * @file ntc.h
 * @author https://github.com/xfp23/
 * @brief NTC thermistor calculation library
 * @version 0.1
 * @date 2025-10-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Check if a pointer is NULL and return NTC_ERR if true.
 */
#define NTC_CHECKPTR(p) do \
{\
    if(p == NULL)\
    {\
        return NTC_ERR;\
    }\
} while (0)

/**
 * @brief Return status codes for NTC operations.
 */
typedef enum
{
    NTC_OK,       /**< Operation successful */
    NTC_ERR,      /**< General error */
    NTC_RESERR,   /**< ADC resolution error */
    NTC_REFERR,   /**< Reference voltage error */
} Ntc_Sta_t;

/**
 * @brief Configuration structure for NTC thermistor.
 */
typedef struct 
{
    uint32_t adcMax;    /**< Maximum ADC value (e.g., 4095 for 12-bit ADC) */
    float Vref;         /**< Reference voltage of the ADC */
    uint16_t Bvalue;    /**< B constant of the NTC thermistor */
    uint32_t R_fixed;   /**< Fixed resistor value in the voltage divider (ohms) */
    uint16_t R25;       /**< Resistance of NTC at 25°C (ohms) */
} Ntc_Conf_t;

/**
 * @brief NTC object containing runtime data.
 */
typedef struct 
{
    Ntc_Conf_t conf;    /**< Configuration parameters */
    float R;            /**< Calculated resistance of NTC */
    float Voltage;      /**< Measured voltage at NTC node */
} Ntc_Obj;

/**
 * @brief Handle to an NTC object.
 */
typedef Ntc_Obj *Ntc_Handle_t;

/**
 * @brief Initialize an NTC object with configuration parameters.
 * 
 * @param handle Pointer to the NTC handle to initialize.
 * @param conf Pointer to configuration structure.
 * @return Ntc_Sta_t Status of initialization.
 */
extern Ntc_Sta_t Ntc_Init(Ntc_Handle_t *handle, Ntc_Conf_t *conf);

/**
 * @brief Calculate the temperature based on ADC reading.
 * 
 * @param handle NTC handle.
 * @param adc ADC raw value.
 * @param buffer Pointer to store the calculated temperature (°C).
 * @return Ntc_Sta_t Status of calculation.
 */
extern Ntc_Sta_t Ntc_CalTempture(Ntc_Handle_t handle, uint16_t adc, float *buffer);

/**
 * @brief Modify an existing NTC configuration.
 * 
 * @param handle Pointer to the NTC handle.
 * @param conf Pointer to the new configuration.
 * @return Ntc_Sta_t Status of operation.
 */
extern Ntc_Sta_t Ntc_Modify(Ntc_Handle_t *handle, Ntc_Conf_t *conf);

/**
 * @brief Release and delete the NTC object.
 * 
 * @param handle Pointer to the NTC handle to delete.
 * @return Ntc_Sta_t Status of operation.
 */
extern Ntc_Sta_t Ntc_Delete(Ntc_Handle_t *handle);

/**
 * @brief 
 * 
 * @param handle 
 * @param res 
 * @param buffer 
 * @return Ntc_Sta_t 
 */
extern Ntc_Sta_t Ntc_ResToTemp(Ntc_Handle_t handle, float res, float *buffer);

extern Ntc_Sta_t Ntc_CalcResistance(Ntc_Handle_t handle, uint16_t adc, float *result);

#ifdef __cplusplus
}
#endif

#endif /* NTC_H */
