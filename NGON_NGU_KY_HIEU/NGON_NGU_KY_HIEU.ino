// Khai báo các chân cảm biến và ngưỡng
const int sensorPins[] = {A4, A3, A2, A1, A0}; // Các chân cảm biến cho ngón tay
int sensorValues[5];
const int threshold = 800; // Ngưỡng để xác định khi ngón tay cong hay thẳng

void setup() {
  // Khởi tạo Serial Monitor
  Serial.begin(9600);
  
  // Thiết lập các chân cảm biến là đầu vào
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {
  // Đọc giá trị từ các cảm biến
  for (int i = 0; i < 5; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    Serial.print(sensorValues[i]);
    Serial.print("    ");
  }
  Serial.println();

  // Kiểm tra và hiển thị chữ cái nhận diện
  if (isA()) {
    Serial.println("Chữ A");
  } else if (isB()) {
    Serial.println("Chữ B");
  } else if (isC()) {
    Serial.println("Chữ C");
  } else if (isD()) {
    Serial.println("Chữ D");
  } else if (isF()) {
    Serial.println("Chữ F");
  } else if (isG()) {
    Serial.println("Chữ G");
  } else if (isH()) {
    Serial.println("Chữ H");
  } else if (isI()) {
    Serial.println("Chữ I");
  } else if (isK()) {
    Serial.println("Chữ K");
  } else if (isL()) {
    Serial.println("Chữ L");
  } else if (isW()) {
    Serial.println("Chữ W");
  } else {
    Serial.println("Không nhận diện được chữ cái.");
  }

  delay(500); // Thêm một độ trễ để tránh in quá nhanh
}

// Hàm nhận diện chữ A 
// Chữ A: Ngón cái thẳng, các ngón còn lại cong
bool isA() {
  return (sensorValues[0] < threshold && 
          sensorValues[1] > threshold && 
          sensorValues[2] > threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] > threshold);
}

// Chữ B: Ngón cái cong, các ngón còn lại thẳng
bool isB() {
  return (sensorValues[0] > threshold && 
          sensorValues[1] < threshold && 
          sensorValues[2] < threshold && 
          sensorValues[3] < threshold && 
          sensorValues[4] < threshold);
}

// Chữ C: Tất cả ngón tay cong
bool isC() {
  return (sensorValues[0] > threshold && 
          sensorValues[1] > threshold && 
          sensorValues[2] > threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] > threshold);
}

// Chữ D: Ngón cái, ngón trỏ, ngón giữa cong, ngón đeo nhẫn cong, ngón út thẳng
bool isD() {
  return (sensorValues[0] > threshold && 
          sensorValues[1] > threshold && 
          sensorValues[2] > threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] < threshold);
}

// Chữ F: Ngón cái, ngón trỏ cong, các ngón còn lại thẳng
bool isF() {
  return (sensorValues[0] > threshold && 
          sensorValues[1] > threshold && 
          sensorValues[2] < threshold && 
          sensorValues[3] < threshold && 
          sensorValues[4] < threshold);
}

// Chữ G: Ngón cái cong, ngón trỏ thẳng, các ngón còn lại cong
bool isG() {
  return (sensorValues[0] > threshold && 
          sensorValues[1] < threshold && 
          sensorValues[2] > threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] > threshold);
}

// Chữ H: Ngón cái cong, ngón trỏ và ngón giữa thẳng, ngón đeo nhẫn và ngón út cong
bool isH() {
  return (sensorValues[0] > threshold && 
          sensorValues[1] < threshold && 
          sensorValues[2] < threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] > threshold);
}

// Chữ I: Ngón cái thẳng, ngón trỏ và ngón giữa cong, ngón đeo nhẫn và ngón út thẳng
bool isI() {
  return (sensorValues[0] < threshold && 
          sensorValues[1] > threshold && 
          sensorValues[2] > threshold && 
          sensorValues[3] < threshold && 
          sensorValues[4] < threshold);
}

// Chữ K: Ngón cái, ngón trỏ, ngón giữa thẳng, ngón đeo nhẫn và ngón út cong
bool isK() {
  return (sensorValues[0] < threshold && 
          sensorValues[1] < threshold && 
          sensorValues[2] < threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] > threshold);
}

// Chữ L: Ngón cái thẳng, ngón trỏ thẳng, các ngón còn lại cong
bool isL() {
  return (sensorValues[0] < threshold && 
          sensorValues[1] < threshold && 
          sensorValues[2] > threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] > threshold);
}

// Chữ W: Ngón cái cong, ngón trỏ và ngón giữa thẳng, ngón đeo nhẫn cong
bool isW() {
  return (sensorValues[0] > threshold && 
          sensorValues[1] < threshold && 
          sensorValues[2] < threshold && 
          sensorValues[3] > threshold && 
          sensorValues[4] < threshold);
}
