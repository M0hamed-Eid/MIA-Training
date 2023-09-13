# MPU6050 Sensor Data Retrieval and Filtering

This document explains the code for interfacing with the MPU6050 sensor, retrieving the yaw angle, and discusses filtering considerations when dealing with noisy environments.

## MPU6050 Sensor Code Documentation

The provided code interfaces with the MPU6050 sensor and calculates the yaw angle based on gyroscope data. Below is a brief overview of the code:

- **Setup:**
  - The code sets up the Arduino environment and initializes the Wire library for I2C communication.
  - It defines constants for the MPU6050 register addresses, gyroscope sensitivity, and yaw angle.
  - The `setup` function initializes the MPU6050 and serial communication.

- **Loop:**
  - In the `loop` function, it continuously reads gyroscope data, calculates the yaw angle, and prints it to the serial monitor.
  - It calculates the yaw angle using integration and adjusts for time intervals between readings.

- **MPU6050 Setup:**
  - The `setupMPU6050` function configures the MPU6050 by setting the sample rate divider and gyroscope full-scale range.
  - Sample rate divider is set to 0, resulting in a gyro output rate of 8 kHz.
  - Gyroscope full-scale range is set to ±250 degrees per second.

- **Read Word 2C:**
  - The `readWord2C` function reads a 16-bit signed value from two consecutive registers, which is used for reading gyroscope data.

## Filtering in Noisy Environments

In noisy environments, sensor data can be corrupted by high-frequency noise. Filtering is used to reduce noise and improve the accuracy of sensor measurements. For the MPU6050 sensor, it's recommended to use a low-pass filter to attenuate high-frequency noise.

### Filter Type

The MPU6050 sensor has an internal Digital Low Pass Filter (DLPF) that can be configured to filter out noise. The DLPF is a Finite Impulse Response (FIR) filter that can be set to different cutoff frequencies.

### Recommended Cutoff Frequency

The recommended cutoff frequency depends on your specific application and the noise characteristics of your environment. However, the MPU6050 datasheet provides guidance on typical cutoff frequencies:

- **DLPF Configuration:** The MPU6050 allows you to select the DLPF configuration based on your desired cutoff frequency. You can choose from a range of values like 5 Hz, 10 Hz, 20 Hz, 42 Hz, and 98 Hz, depending on your requirements.

- **DLPF Setting:** You can set the DLPF using the `DLPF_CFG` register (Register 0x1A) in the MPU6050. The specific register values correspond to different cutoff frequencies as documented in the datasheet.

## Question

It's important to experiment and choose the cutoff frequency that best suits your application while balancing noise reduction with sensor responsiveness. In noisy environments, The filter should be used in this case is Low Pass Filter and its maximum frequency value is 400kHz and the cutoff frequency is 
400 / (2 * pi) = 282.8 KHz
