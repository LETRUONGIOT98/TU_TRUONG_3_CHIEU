const int sensorA = A0;
const int sensorB = A1;
const int sensorC = A2;
const int sensorD = A3;

float valueA = 0, valueB = 0, valueC = 0, valueD = 0;
float x = 0, y = 0, z = 0;
const float sensorDistance = 10.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  valueA = analogRead(sensorA);
  valueB = analogRead(sensorB);
  valueC = analogRead(sensorC);
  valueD = analogRead(sensorD);

  float fieldA = map(valueA, 0, 1023, -500, 500);
  float fieldB = map(valueB, 0, 1023, -500, 500);
  float fieldC = map(valueC, 0, 1023, -500, 500);
  float fieldD = map(valueD, 0, 1023, -500, 500);

  x = (fieldB - fieldC) / sensorDistance;
  y = (fieldA - fieldD) / sensorDistance;
  z = (fieldA + fieldB + fieldC + fieldD) / 4.0;

  // Truyền dữ liệu XYZ qua Serial
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);

  delay(500);
}
