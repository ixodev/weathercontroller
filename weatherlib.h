#define _TEMPERATURE_ 0
#define _PRESSURE_ 1
#define _NORMALIZED_PRESSURE_ 2
#define _HUMIDITY_ 3
#define _ALTITUDE_ 4
#define _DEW_POINT_ 5
#define _WEATHER_ 6
#define _MAX_ 6
#define _MIN_ 0
#define MAGNUS_A 17.27
#define MAGNUS_B 237.7
#define SEA_LEVEL_PRESSURE 1013.25
#define ALTITUDE 519 // on travaille à altitude fixe

// Les fonctions marquées par la macro WEATHERAPI sont des fonctions appartenant à l'ensemble des fonctions permettant de communiquer avec BME680
// Ca ne change rien mais on ca aide dans le code à la relecture
#define WEATHERAPI
// Pour éviter de répeter DFRobot_BME680_I2C* bme
// Car toutes les fonctions WEATHERAPI ont besoin de communiquer avec le capteur
#define WEATHERAPIPARAM DFRobot_BME680_I2C* bme

float actual_pressure = 0;

float WEATHERAPI temperature(WEATHERAPIPARAM){
  float value = bme->readTemperature()/100;
  return value;
}

float WEATHERAPI pressure(WEATHERAPIPARAM) {
  float value = bme->readPressure()/100;
  return value;
}

float WEATHERAPI humidity(WEATHERAPIPARAM) {
  return bme->readHumidity()/1000;
}

float WEATHERAPI normalized_pressure(WEATHERAPIPARAM) {
  return pressure(bme) * pow(1 - (0.0065 * ALTITUDE) / (288.15), -5.255);
}


float WEATHERAPI dew_point(WEATHERAPIPARAM) {
  //float dew_temperature = MAGNUS_B * alpha(temp, humidity) / (MAGNUS_A - alpha(temp, humidity));
  //return dew_temperature;
  float value = pow(humidity(bme), 1/8) * (112 + 0.9) + 0.1 * temperature(bme) - 112;
  return value;
}

float WEATHERAPI altitude(WEATHERAPIPARAM) {
  return bme->readAltitude();
}

float WEATHERAPI weather(WEATHERAPIPARAM) {
  if(millis() % 1000 == 0) {
    float pression = pressure(bme);
    float difference = pression - actual_pressure;
    actual_pressure = pression;
    return difference;
  }
  return 0;
}

String keys[7] {"temperature", "pressure", "normalized pressure", "humidity", "altitude", "dew point", "weather"};
String units[7] {String((char)223) + String("C"), "hPa", "hPa", "%", "m", String((char)223) + String("C"), ""};
float (*weatherlib[7])(WEATHERAPIPARAM) = {&temperature, &pressure, &normalized_pressure, &humidity, &altitude, &dew_point, &weather};

