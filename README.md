# 🌦️ LuxWeather – Clima e Temperaturas Configuráveis por JSON para DayZ

Mod de **scripts (Enforce Script)** para **DayZ Standalone** que permite **configurar via arquivo JSON** o clima e as temperaturas do mod **Lux**: chance de tempo bom/ruim, temperatura dos líquidos e temperatura ambiente ao longo do dia, sem precisar editar scripts nem reempacotar o mod.

---

## 📦 Dependência

- **Mod Lux**, que fornece a classe `LuxData` (addon `TemScriptsMod`). Este repositório contém apenas o código do LuxWeather, que estende essa classe via `modded class`.

---

## ✨ Funcionalidades

- ⚙️ **Configuração por JSON**, criada automaticamente com valores padrão na primeira execução
- ☁️ **Controle do clima:** chance de tempo limpo, de tempo ruim e de mudança súbita para tempo ruim
- 💧 **Temperatura dos líquidos:** água salgada, água comum, parada, de rio, fresca e limpa
- 🌡️ **Temperatura ambiente:** curva diária entre uma temperatura mínima e uma máxima
- 🧩 Usa `modded class`, sem substituir arquivos do mod original

---

## ⚙️ Como funciona

| Método | Comportamento |
|---|---|
| `InitWeatherConfig()` | Carrega o `WeatherConfig.json` ou cria o arquivo com valores padrão |
| `SetupWeatherSettings()` | Aplica as chances de clima do JSON |
| `SetupLiquidTemperatures()` | Aplica as temperaturas dos líquidos do JSON |
| `CalcBaseEnvironmentTemperature()` | Calcula a temperatura ambiente: sobe da mínima (0h) até a máxima (12h) e desce até a mínima (24h) |
| `GetHFProfileFolder()` | Retorna (e cria, se preciso) a pasta `HF` no perfil do servidor |

---

## 🗂️ Arquivo de configuração

Criado automaticamente em:

```
$serverprofile:\HF\Lux\WeatherConfig.json
```

### Valores padrão

```json
{
    "ClearWeatherChance": 90.0,
    "BadWeatherChance": 40.0,
    "BadWeatherSuddenChance": 5.0,
    "TempSaltWater": 25.0,
    "TempWater": 25.0,
    "TempStillWater": 25.0,
    "TempRiverWater": 20.0,
    "TempFreshWater": 20.0,
    "TempCleanWater": 15.0,
    "MinEnvTemp": 6.0,
    "MaxEnvTemp": 10.0
}
```

| Campo | Descrição |
|---|---|
| `ClearWeatherChance` | Chance de tempo limpo |
| `BadWeatherChance` | Chance de tempo ruim |
| `BadWeatherSuddenChance` | Chance de mudança súbita para tempo ruim |
| `TempSaltWater` | Temperatura da água salgada |
| `TempWater` | Temperatura da água comum |
| `TempStillWater` | Temperatura da água parada |
| `TempRiverWater` | Temperatura da água de rio |
| `TempFreshWater` | Temperatura da água fresca |
| `TempCleanWater` | Temperatura da água limpa |
| `MinEnvTemp` | Temperatura ambiente mínima (início e fim do dia) |
| `MaxEnvTemp` | Temperatura ambiente máxima (meio-dia) |

> As chances de clima seguem o significado definido pelo mod Lux.

---

## 📁 Estrutura do projeto

```
MyLuxWeatherOverride/
├── config.cpp
└── scripts/
    └── 4_World/
        └── LuxData.c
```

> Ajuste os nomes conforme os arquivos reais do seu projeto.

---

## 🧰 Tecnologias

- Enforce Script (DayZ)
- `JsonFileLoader` para persistência
- `modded class`

---

## 👤 Autor

Desenvolvido por **HF**.
