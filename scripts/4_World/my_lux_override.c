// --------------------------------------------------
// LuxWeatherConfig.class
// --------------------------------------------------
class LuxWeatherConfig
{
    float ClearWeatherChance;
    float BadWeatherChance;
    float BadWeatherSuddenChance;

    float TempSaltWater;
    float TempWater;
    float TempStillWater;
    float TempRiverWater;
    float TempFreshWater;
    float TempCleanWater;

    float MinEnvTemp;
    float MaxEnvTemp;

    void LuxWeatherConfig()
    {
        // Valores padrão
        ClearWeatherChance = 90;
        BadWeatherChance = 40;
        BadWeatherSuddenChance = 5;

        TempSaltWater = 25;
        TempWater = 25;
        TempStillWater = 25;
        TempRiverWater = 20;
        TempFreshWater = 20;
        TempCleanWater = 15;

        MinEnvTemp = 6;
        MaxEnvTemp = 10;
    }
}

// --------------------------------------------------
// Modded LuxData
// --------------------------------------------------
modded class LuxData
{
    static string FILE_PATH_CONFIG;
    static ref LuxWeatherConfig WeatherConfig;
		 
    // Inicializa o arquivo JSON
    // -----------------------------
    static void InitWeatherConfig()
    {
        if (!GetGame().IsServer())
            return;

        string folder = GetHFProfileFolder() + "Lux\\";
        if (!FileExist(folder))
            MakeDirectory(folder);
		

        FILE_PATH_CONFIG = folder + "WeatherConfig.json";

        if (FileExist(FILE_PATH_CONFIG))
        {
            WeatherConfig = new LuxWeatherConfig();
            JsonFileLoader<LuxWeatherConfig>.JsonLoadFile(FILE_PATH_CONFIG, WeatherConfig);
            Print("[LuxWeather] Configuração carregada do arquivo JSON.");
        }
        else
        {
            WeatherConfig = new LuxWeatherConfig();
            JsonFileLoader<LuxWeatherConfig>.JsonSaveFile(FILE_PATH_CONFIG, WeatherConfig);
            Print("[LuxWeather] Arquivo JSON criado com valores padrão.");
        }
    }

    // -----------------------------
    // Override dos métodos usando JSON
    // -----------------------------
    override void SetupWeatherSettings()
    {
        super.SetupWeatherSettings();

        if (!WeatherConfig)
            InitWeatherConfig();

        m_WeatherDefaultSettings.m_ClearWeatherChance = WeatherConfig.ClearWeatherChance;
        m_WeatherDefaultSettings.m_BadWeatherChance = WeatherConfig.BadWeatherChance;
        m_WeatherDefaultSettings.m_BadWeatherSuddenChance = WeatherConfig.BadWeatherSuddenChance;
    }

    override void SetupLiquidTemperatures()
    {
        super.SetupLiquidTemperatures();

        if (!WeatherConfig)
            InitWeatherConfig();

        m_LiquidSettings.m_Temperatures[LIQUID_SALTWATER] = WeatherConfig.TempSaltWater;
        m_LiquidSettings.m_Temperatures[LIQUID_WATER] = WeatherConfig.TempWater;
        m_LiquidSettings.m_Temperatures[LIQUID_STILLWATER] = WeatherConfig.TempStillWater;
        m_LiquidSettings.m_Temperatures[LIQUID_RIVERWATER] = WeatherConfig.TempRiverWater;
        m_LiquidSettings.m_Temperatures[LIQUID_FRESHWATER] = WeatherConfig.TempFreshWater;
        m_LiquidSettings.m_Temperatures[LIQUID_CLEANWATER] = WeatherConfig.TempCleanWater;
    }

    override float CalcBaseEnvironmentTemperature(float monthday, float daytime)
    {
        if (!WeatherConfig)
            InitWeatherConfig();

        float minTemp = WeatherConfig.MinEnvTemp;
        float maxTemp = WeatherConfig.MaxEnvTemp;
        float i;

        if(daytime <= 12) {
            i = daytime / 12;
            return Math.Lerp(minTemp, maxTemp, i);
        } else {
            i = (daytime - 12) / 12;
            return Math.Lerp(maxTemp, minTemp, i);
        }
    }

    // -----------------------------
    // Retorna ou cria a pasta HF
    // -----------------------------
    static string GetHFProfileFolder()
    {
        string folder;

        if (GetGame().IsServer() && FileExist("$serverprofile:"))
            folder = "$serverprofile:\\HF\\";
        else
            folder = "$profile:\\HF\\";

        if (!FileExist(folder))
            MakeDirectory(folder);

        return folder;
    }
}
