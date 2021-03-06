#include "Config.h"

Config* Config::instance;


Config::Config(string configFileName) {
    string configFilePath = "./" + configFileName;
    ifstream file(configFilePath.c_str(), ios::in);
    if(!file.is_open()) {
        cerr << "Nie mogę otworzyć pliku do odczytu: [" << configFilePath << "]" << std::endl;
        exit(0);
    }

    string line;
    int lineNumber = 2;
    int requiredValues = 19;
    while(getline(file, line)) {
        Logger::getInstance().addLineToScreen(lineNumber++, ("- " + line).c_str(), 0);

        if(line[0] == '#') {
            continue;
        }
        vector<string> lineItems = split(line, '=');
        string key = trim(lineItems[0]);
        string value = trim(lineItems[1]);

        if     (key == "vorticesCount"          ) vorticesCount             = atoi(value.c_str());
        else if(key == "vortexStrenght"         ) vortexStrenght            = atof(value.c_str());
        else if(key == "vortexMoving"           ) vortexMoving              = atoi(value.c_str());
        else if(key == "vortexRadiusMin"        ) vortexRadiusMin           = atof(value.c_str());
        else if(key == "vortexRadiusMax"        ) vortexRadiusMax           = atof(value.c_str());
        else if(key == "maxFrames"              ) maxFrames                 = atoi(value.c_str());
        else if(key == "thermalBuoyancyFactor"  ) thermalBuoyancyFactor     = atof(value.c_str());
        else if(key == "gravityFactor"          ) gravityFactor             = atof(value.c_str());
        else if(key == "windFactor"             ) windFactor                = atof(value.c_str());
        else if(key == "viscosity"              ) viscosity                 = atof(value.c_str());
        else if(key == "diffusionRate"          ) diffusionRate             = atof(value.c_str());
        else if(key == "mainSourceDensity"      ) mainSourceDensity         = atof(value.c_str());
        else if(key == "vySlow"                 ) vySlow                    = atof(value.c_str());
        else if(key == "vyMedium"               ) vyMedium                  = atof(value.c_str());
        else if(key == "vyFast"                 ) vyFast                    = atof(value.c_str());
        else if(key == "nonLinearColor"         ) nonLinearColor            = atoi(value.c_str());
        else if(key == "smokeColorThreshold"    ) smokeColorThreshold       = atof(value.c_str());
        else if(key == "splattingSuperSampling" ) splattingSuperSampling    = atoi(value.c_str());
        else if(key == "splattingDislocation"   ) splattingDislocation      = atof(value.c_str());
        else {
            cerr << "Nieznany parametr konfiguracyjny: [" << key << " = " << value << "]" << endl;
            exit(0);
        }

        requiredValues--;
    }

    if(requiredValues != 0) {
        cerr << "Brak parametów konfiguracyjnych w liczbie: " << requiredValues << endl;
        exit(0);
    }


    mainSourceVY = vySlow;
    int step = 0;
    explosionSource[step][0] = 0;          explosionSource[step++][1] = 0.0;
    explosionSource[step][0] = 12;         explosionSource[step++][1] = vySlow;
    explosionSource[step][0] = 15;         explosionSource[step++][1] = vyMedium;
    explosionSource[step][0] = 18;         explosionSource[step++][1] = vyFast;
    explosionSource[step][0] = 80;         explosionSource[step++][1] = vySlow;
    explosionSource[step][0] = 140;        explosionSource[step++][1] = vyFast;
    explosionSource[step][0] = 180;        explosionSource[step++][1] = vySlow;
    explosionSource[step][0] = 220;        explosionSource[step++][1] = vyFast;
    explosionSource[step][0] = 280;        explosionSource[step++][1] = vySlow;
    explosionSource[step][0] = maxFrames;  explosionSource[step++][1] = 0.0;
    explosionSourcePhases = sizeof(explosionSource)/sizeof(explosionSource[0]);


    file.close();

    cout << "Poprawnie odczytano config: [" << configFilePath << "]" << endl;
}
