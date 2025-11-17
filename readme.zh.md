
---

[English](./readme.md)

## 📗 **中文使用文档**

### 📘 简介

`NTC` 是一个用于通过热敏电阻（NTC）计算温度的轻量级库。
只需提供 ADC 采样值和分压参数，即可计算实时温度。支持初始化、参数修改与资源释放。

---

### ⚙️ 功能特点

* 结构清晰，API 简单
* 支持动态修改参数
* 使用经典 B 值法计算温度
* 可直接应用于 MCU 环境（S32K、STM32、ESP32 等）

---

### 🧩 函数说明

#### **1. 初始化函数**

```c
Ntc_Sta_t Ntc_Init(Ntc_Handle_t *handle, Ntc_Conf_t *conf);
```

功能：创建并初始化一个 NTC 对象
返回：`NTC_OK` 成功，`NTC_ERR` 失败（如指针为空或重复初始化）

---

#### **2. 温度计算**

```c
Ntc_Sta_t Ntc_CalTempture(Ntc_Handle_t handle, uint16_t adc, float *buffer);
```

功能：根据 ADC 值计算温度（摄氏度）
参数：

* `handle`：初始化后的 NTC 句柄
* `adc`：ADC 转换结果
* `buffer`：输出温度值的地址
  返回：`NTC_OK` 成功

---

#### **3. 修改参数**

```c
Ntc_Sta_t Ntc_Modify(Ntc_Handle_t *handle, Ntc_Conf_t *conf);
```

功能：动态修改 NTC 的配置参数
返回：`NTC_OK` 成功

---

#### **4. 得到阻值**

```c
Ntc_Sta_t Ntc_CalRes(Ntc_Handle_t handle, uint16_t adc, float *result);
```

功能: 得到adc对应的电阻阻值
返回: `NTC_OK` 成功


#### **5. 删除对象**

```c
Ntc_Sta_t Ntc_Delete(Ntc_Handle_t *handle);
```

功能：释放句柄内存
返回：`NTC_OK` 成功

---

### ⚙️ 配置结构体说明

```c
typedef struct 
{
    uint32_t adcMax;     // ADC最大值，例如4095
    float Vref;          // ADC参考电压
    uint16_t Bvalue;     // 热敏电阻的B常数
    uint32_t R_fixed;    // 分压电路中的固定电阻值(Ω)
    uint16_t R25;        // 热敏电阻在25°C时的阻值(Ω)
} Ntc_Conf_t;
```

---

### 💡 示例代码

```c
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
    printf("当前温度: %.2f °C\n", temp);
    printf("当前阻值: %.2f Ω\n",res);

    Ntc_Delete(&ntc);
}
```

---