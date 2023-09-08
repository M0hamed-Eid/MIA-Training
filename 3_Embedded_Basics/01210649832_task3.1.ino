#define TRIGGER_PIN_0 2
#define ECHO_PIN_0 3

#define TRIGGER_PIN_90 4
#define ECHO_PIN_90 5

#define TRIGGER_PIN_180 6
#define ECHO_PIN_180 7

#define TRIGGER_PIN_270 8
#define ECHO_PIN_270 9

#define CHAMBER_WIDTH 500
#define CHAMBER_HEIGHT 600

float x = 0;
float y = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN_0, OUTPUT);
  pinMode(ECHO_PIN_0, INPUT);
  pinMode(TRIGGER_PIN_90, OUTPUT);
  pinMode(ECHO_PIN_90, INPUT);
  pinMode(TRIGGER_PIN_180, OUTPUT);
  pinMode(ECHO_PIN_180, INPUT);
  pinMode(TRIGGER_PIN_270, OUTPUT);
  pinMode(ECHO_PIN_270, INPUT);
}

void loop() {
  int distance_0 = measureDistance(TRIGGER_PIN_0, ECHO_PIN_0);
  int distance_90 = measureDistance(TRIGGER_PIN_90, ECHO_PIN_90);
  int distance_180 = measureDistance(TRIGGER_PIN_180, ECHO_PIN_180);
  int distance_270 = measureDistance(TRIGGER_PIN_270, ECHO_PIN_270);

  x += distance_0 - distance_180;
  y += distance_90 - distance_270;

  if (x < 0) {
    x = 0;
  }
  if (x > CHAMBER_WIDTH) {
    x = CHAMBER_WIDTH;
  }
  if (y < 0) {
    y = 0;
  }
  if (y > CHAMBER_HEIGHT) {
    y = CHAMBER_HEIGHT;
  }

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" cm, Y: ");
  Serial.print(y);
  Serial.println(" cm");

  delay(1000);
}

int measureDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.034 / 2;

  return distance;
}
