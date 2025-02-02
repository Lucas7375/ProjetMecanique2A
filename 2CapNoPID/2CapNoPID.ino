// 一共两个马达， 两个传感器，前轮两个珠子 xD，后轮各两个马达

// Define Motor Pin
#define left_motor_pin 5
#define right_motor_pin 6

// Define Sensor Pin
#define left_sensor_pin 3
#define right_sensor_pin 4

void motorPinInit();

// Create movement function
void go();
void _stop();
void turnLeft();
void turnRight();

// Init tmp
int tmp = 2000;

// Init output value
int error = 0;

// A tableau with 2 sensors
int sensor[2] = {0, 0};

// Read Sensors' first value
int getSensorValue(void);

void setup()
{
  // put your setup code here, to run once:
  // Set port 9600
  Serial.begin(9600);

  // Init sensor
  sensorPinInit();

  // Init motor
  motorPinInit();
}

void loop()
{
  // put your main code here, to run repeatedly:
  static int value = 0;

  // Read sensor value
  value = getSensorValue();
  switch (value)
  {
    // Move forward
  case 0:
    aller();
    break;

    // Move right
  case -1:
    aPetitDroite();
    break;

    // Move left
  case 1:
    aPetitGauche();
    break;

    // Stop
  default:
    _stop();
    break;
  }
}

// Init sensor model
void sensorPinInit()
{
  pinMode(SENSOR_LEFT_PIN, INPUT);
  pinMode(SENSOR_RIGHT_PIN, INPUT);
}

// Init motor model
void motorPinInit()
{
  pinMode(MOTOR_LEFT_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_PIN, OUTPUT);
}

// Function stop
// Feature: Stop the vehicle
void _stop()
{
  analogWrite(MOTOR_LEFT_PIN, 0);
  analogWrite(MOTOR_RIGHT_PIN, 0);
}

// Function aller
// Feature: Make vehicle move forward
void aller()
{
  analogWrite(MOTOR_LEFT_PIN, 50);
  analogWrite(MOTOR_RIGHT_PIN, 50);
}

// Function aPetitGauche
// Feature: Make vehicle turn left
void aPetitGauche()
{
  analogWrite(MOTOR_LEFT_PIN, 30);
  analogWrite(MOTOR_RIGHT_PIN, 60);

  delay(tmp);
  analogWrite(MOTOR_LEFT_PIN, 20);
  analogWrite(MOTOR_RIGHT_PIN, 20);
  delay(tmp);
}

// Function aPetitDroite
// Feature: Make vehicle turn right
void aPetitDroite()
{
  analogWrite(MOTOR_LEFT_PIN, 60);
  analogWrite(MOTOR_RIGHT_PIN, 30);

  delay(tmp);
  analogWrite(MOTOR_LEFT_PIN, 20);
  analogWrite(MOTOR_RIGHT_PIN, 20);
  delay(tmp);
}

// Function Read Sensors' Values
int getSensorValue()
{
  // Read semsors' signals
  sensor[0] = digitalRead(SENSOR_LEFT_PIN);
  sensor[1] = digitalRead(SENSOR_RIGHT_PIN);
  if (sensor[0] == 1 && sensor[1] == 1)
  {
    error = 0; // 11 Arreter
  }
  else if (sensor[0] == 1 && sensor[1] == 0)
  {
    error = -1; // 10 Droite
  }
  else if (sensor[0] == 0 && sensor[1] == 1)
  {
    error = 1; // 01 Gauche
  }
  else if (sensor[0] == 0 && sensor[1] == 0)
  {
    error = 0; // 00 Aller (Error)
  }
  return error;
}