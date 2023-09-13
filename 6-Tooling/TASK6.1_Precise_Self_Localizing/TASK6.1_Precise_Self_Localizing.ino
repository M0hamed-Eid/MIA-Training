#include <Wire.h>

#define MPU6050_ADDRESS 0x68 // MPU6050 I2C address
#define GYRO_CONFIG 0x1B     // Gyroscope configuration register
#define SMPLRT_DIV 0x19       // Sample rate divider register
#define GYRO_XOUT_H 0x43      // Gyro X-axis high byte register
#define GYRO_XOUT_L 0x44      // Gyro X-axis low byte register
#define GYRO_YOUT_H 0x45      // Gyro Y-axis high byte register
#define GYRO_YOUT_L 0x46      // Gyro Y-axis low byte register
#define GYRO_ZOUT_H 0x47      // Gyro Z-axis high byte register
#define GYRO_ZOUT_L 0x48      // Gyro Z-axis low byte register

float gyroScale = 131.0; // Gyroscope sensitivity (LSB/degrees per second)
float yawAngle = 0.0;   // Yaw angle in degrees

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  // Initialize MPU6050
  setupMPU6050();
}

void loop()
{
  // Read gyroscope data
  int16_t gyroX = readWord2C(GYRO_XOUT_H);
  int16_t gyroY = readWord2C(GYRO_YOUT_H);
  int16_t gyroZ = readWord2C(GYRO_ZOUT_H);

  // Calculate time interval
  static unsigned long prevTime = millis();
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - prevTime) / 1000.0; // Convert to seconds
  prevTime = currentTime;

  // Calculate yaw angle using gyroscope data
  yawAngle += gyroZ / gyroScale * deltaTime;

  // Print yaw angle
  Serial.print("Yaw Angle: ");
  Serial.print(yawAngle);
  Serial.println(" degrees");

  delay(100);
}

void setupMPU6050()
{
  // Set sample rate divider (Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV))
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(SMPLRT_DIV);
  Wire.write(0); // Set divider to 0 (gyro output rate = 8 kHz)
  Wire.endTransmission();

  // Set gyroscope full scale range (±250 degrees/sec)
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(GYRO_CONFIG);
  Wire.write(0); // FS_SEL = 0 (±250 degrees/sec)
  Wire.endTransmission();
}

int16_t readWord2C(int reg)
{
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDRESS, 2, true);

  int16_t value = Wire.read() << 8 | Wire.read();
  if (value >= 0x8000)
  {
    return -(65535 - value + 1);
  }
  return value;
}
