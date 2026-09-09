#include "ntc.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

Ntc_Sta_t Ntc_Init(Ntc_Obj_t *obj, Ntc_Conf_t *conf)
{
    NTC_CHECKPTR(obj);
    NTC_CHECKPTR(conf);

    memset((void*)obj,0,sizeof(Ntc_Obj_t));

    obj->conf = (*conf);

    return NTC_OK;
}

Ntc_Sta_t Ntc_CalTempture(Ntc_Obj_t *obj, uint16_t adc, float *buffer)
{
    NTC_CHECKPTR(obj);

    if (!obj->conf.adcMax)
        return NTC_RESERR;

    obj->Voltage = ((float)adc / (float)obj->conf.adcMax) * obj->conf.Vref;

    if (obj->Voltage >= obj->conf.Vref)
        return NTC_REFERR;

    obj->R = (obj->conf.R_fixed * obj->Voltage) / (obj->conf.Vref - obj->Voltage);

    *buffer = (1.0f / ((1.0f / 298.15f) + (1.0f / obj->conf.Bvalue) * logf(obj->R / obj->conf.R25))) - 273.15f;
    return NTC_OK;
}

Ntc_Sta_t Ntc_Modify(Ntc_Obj_t *obj, Ntc_Conf_t *conf)
{
    NTC_CHECKPTR(obj);
    NTC_CHECKPTR(conf);

    obj->conf = (*conf);

    return NTC_OK;
}

Ntc_Sta_t Ntc_Delete(Ntc_Obj_t *obj)
{
    NTC_CHECKPTR(obj);

    memset(obj,0,sizeof(Ntc_Obj_t));

    return NTC_OK;
}

Ntc_Sta_t Ntc_CalcResistance(Ntc_Obj_t *obj, uint16_t adc, float *result)
{
    NTC_CHECKPTR(obj);

    if (!obj->conf.adcMax)
        return NTC_RESERR;
        
    obj->Voltage = ((float)adc / (float)obj->conf.adcMax) * obj->conf.Vref;

    if (obj->Voltage >= obj->conf.Vref)
        return NTC_REFERR;

    obj->R = (obj->conf.R_fixed * obj->Voltage) / (obj->conf.Vref - obj->Voltage);
    *result = obj->R;
    return NTC_OK;
}

Ntc_Sta_t Ntc_ResToTemp(Ntc_Obj_t *obj, float res, float *buffer)
{
    NTC_CHECKPTR(obj);

    if (!obj->conf.adcMax)
        return NTC_RESERR;

    *buffer = (1.0f / ((1.0f / 298.15f) + (1.0f / obj->conf.Bvalue) * logf(res / obj->conf.R25))) - 273.15f;
    return NTC_OK;
}
