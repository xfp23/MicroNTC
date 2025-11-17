#include "ntc.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

Ntc_Sta_t Ntc_Init(Ntc_Handle_t *handle, Ntc_Conf_t *conf)
{
    NTC_CHECKPTR(handle);
    NTC_CHECKPTR(conf);

    if (*handle != NULL)
        return NTC_ERR;

    *handle = (Ntc_Obj *)calloc(1, sizeof(Ntc_Obj));

    NTC_CHECKPTR(*handle);

    memcpy(&(*handle)->conf, conf, sizeof(Ntc_Conf_t));

    return NTC_OK;
}

Ntc_Sta_t Ntc_CalTempture(Ntc_Handle_t handle, uint16_t adc, float *buffer)
{
    NTC_CHECKPTR(handle);

    if (!handle->conf.adcMax)
        return NTC_RESERR;

    handle->Voltage = ((float)adc / (float)handle->conf.adcMax) * handle->conf.Vref;

    if (handle->Voltage >= handle->conf.Vref)
        return NTC_REFERR;

    handle->R = (handle->conf.R_fixed * handle->Voltage) / (handle->conf.Vref - handle->Voltage);

    *buffer = (1.0f / ((1.0f / 298.15f) + (1.0f / handle->conf.Bvalue) * logf(handle->R / handle->conf.R25))) - 273.15f;
    return NTC_OK;
}

Ntc_Sta_t Ntc_Modify(Ntc_Handle_t *handle, Ntc_Conf_t *conf)
{
    NTC_CHECKPTR(handle);
    NTC_CHECKPTR(conf);

    memcpy(&(*handle)->conf, conf, sizeof(Ntc_Conf_t));
    return NTC_OK;
}

Ntc_Sta_t Ntc_Delete(Ntc_Handle_t *handle)
{
    NTC_CHECKPTR(handle);

    free(*handle);
    *handle = NULL;

    return NTC_OK;
}