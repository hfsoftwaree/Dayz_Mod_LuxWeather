class CfgPatches
{
    class MyLuxWeatherOverride
     {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"TemScriptsMod"};
    };
};

class CfgMods
{
    class MyLuxWeatherOverride
    {
        dir = "MyLuxWeatherOverride";
		name = "MyLuxWeatherOverride";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        author = "HF";
        version = "1.0";
        type = "mod";
        dependencies[] = { "Game", "World", "Mission" };

        class defs
        {
            class worldScriptModule
            {
				value = "";
                files[] = { "ZHF_WeatherLux/MyLuxWeatherOverride/scripts/4_World" };
            };
        };
    };
};
