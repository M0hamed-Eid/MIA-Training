// Define pins for the encoder A and B signals
const int encoderPinA = 2; 
const int encoderPinB = 3;

// Variables to keep track of encoder state
volatile long encoderCount = 0;
volatile int lastEncoded = 0;

// Low-pass filter variables
const float fc = 10.0; // Set the desired cutoff frequency (in Hz)
const float dt = 0.001; // Sample time (1 ms)
const float alpha = (2 * 3.14159265359 * fc * dt) / (2 * 3.14159265359 * fc * dt + 1);

void setup() {
  // Initialize the encoder pins as inputs
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  // Attach interrupt handlers for the A and B signals
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read and print the filtered encoder count
  long filteredCount = lowPassFilter(encoderCount);
  Serial.println("Filtered Count: " + String(filteredCount));

  // You can add additional code here to control WALL-E based on the encoder count
}

void updateEncoder() {
  int MSB = digitalRead(encoderPinA);
  int LSB = digitalRead(encoderPinB);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderCount++;
  }
  else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderCount--;
  }

  lastEncoded = encoded;
}

long lowPassFilter(long input) {
  static long filteredValue = 0;
  filteredValue = (1 - alpha) * filteredValue + alpha * input;
  return filteredValue;
}
