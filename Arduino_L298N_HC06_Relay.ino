// กำหนดหมายเลขพินสำหรับ L298N
const int motorAForward = 5; // IN1
const int motorABackward = 6; // IN2
const int motorBForward = 9; // IN3
const int motorBBackward = 10; // IN4
const int motorAPWM = 3; // ENA
const int motorBPWM = 11; // ENB

const int relay1Pin = 12;

// ตัวแปรสำหรับการควบคุมความเร็ว
int motorSpeed = 180; // ความเร็วเริ่มต้นสูงสุด

void setup() {
  // ตั้งค่าพินที่เชื่อมต่อกับ L298N เป็น OUTPUT
  pinMode(motorAForward, OUTPUT);
  pinMode(motorABackward, OUTPUT);
  pinMode(motorBForward, OUTPUT);
  pinMode(motorBBackward, OUTPUT);
  pinMode(motorAPWM, OUTPUT);
  pinMode(motorBPWM, OUTPUT);
  pinMode(relay1Pin, OUTPUT);
   digitalWrite(relay1Pin, LOW);

  // เริ่มต้นการสื่อสาร Serial กับ Bluetooth โมดูล
  Serial.begin(9600); // ความเร็วการสื่อสารที่ใช้กับ HC-06
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read(); // อ่านคำสั่งที่ได้รับ

    switch (command) {
      case 'F': // ไปข้างหน้า
        forward();
        break;
      case 'B': // ถอยหลัง
        backward();
        break;
      case 'L': // เลี้ยวซ้าย
        left();
        break;
      case 'R': // เลี้ยวขวา
        right();
        break;
      case 'G': // ไปข้างหน้าและเลี้ยวซ้าย
        forwardLeft();
        break;
      case 'I': // ไปข้างหน้าและเลี้ยวขวา
        forwardRight();
        break;
      case 'H': // ถอยหลังและเลี้ยวซ้าย
        backwardLeft();
        break;
      case 'J': // ถอยหลังและเลี้ยวขวา
        backwardRight();
        break;
      case 'S': // หยุด
        stop();
        break;

      case 'W': // เปิด Relay
        digitalWrite(relay1Pin, HIGH);
        stop();
        break;

      case 'w': // ปิด Relay
         digitalWrite(relay1Pin, LOW);
        stop();
        break;
      
      default:
        stop(); // คำสั่งที่ไม่รู้จัก
        break;
    }
  }
}

void forward() {
  // หมุนมอเตอร์ A และ B ไปข้างหน้า
  digitalWrite(motorAForward, HIGH);
  digitalWrite(motorABackward, LOW);
  digitalWrite(motorBForward, HIGH);
  digitalWrite(motorBBackward, LOW);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void backward() {
  // หมุนมอเตอร์ A และ B ถอยหลัง
  digitalWrite(motorAForward, LOW);
  digitalWrite(motorABackward, HIGH);
  digitalWrite(motorBForward, LOW);
  digitalWrite(motorBBackward, HIGH);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void right() {
  // เลี้ยวขวา (หมุนมอเตอร์ A ถอยหลังและ B ไปข้างหน้า)
  digitalWrite(motorAForward, LOW);
  digitalWrite(motorABackward, HIGH);
  digitalWrite(motorBForward, HIGH);
  digitalWrite(motorBBackward, LOW);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void left() {
  // เลี้ยวซ้าย (หมุนมอเตอร์ A ไปข้างหน้าและ B ถอยหลัง)
  digitalWrite(motorAForward, HIGH);
  digitalWrite(motorABackward, LOW);
  digitalWrite(motorBForward, LOW);
  digitalWrite(motorBBackward, HIGH);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void forwardLeft() {
  // ไปข้างหน้าและเลี้ยวซ้าย (มอเตอร์ A ไปข้างหน้าและ B ถอยหลัง)
  digitalWrite(motorAForward, HIGH);
  digitalWrite(motorABackward, LOW);
  digitalWrite(motorBForward, LOW);
  digitalWrite(motorBBackward, LOW);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void forwardRight() {
  // ไปข้างหน้าและเลี้ยวขวา (มอเตอร์ A ไปข้างหน้าและ B ไปข้างหน้า)
  digitalWrite(motorAForward, LOW);
  digitalWrite(motorABackward, LOW);
  digitalWrite(motorBForward, HIGH);
  digitalWrite(motorBBackward, LOW);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void backwardLeft() {
  // ถอยหลังและเลี้ยวซ้าย (มอเตอร์ A ถอยหลังและ B ถอยหลัง)
  digitalWrite(motorAForward, LOW);
  digitalWrite(motorABackward, HIGH);
  digitalWrite(motorBForward, LOW);
  digitalWrite(motorBBackward, LOW);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void backwardRight() {
  // ถอยหลังและเลี้ยวขวา (มอเตอร์ A ถอยหลังและ B ไปข้างหน้า)
  digitalWrite(motorAForward, LOW);
  digitalWrite(motorABackward, LOW);
  digitalWrite(motorBForward, LOW);
  digitalWrite(motorBBackward, HIGH);
  analogWrite(motorAPWM, motorSpeed);
  analogWrite(motorBPWM, motorSpeed);
}

void stop() {
  // หยุดมอเตอร์ทั้งหมด
  digitalWrite(motorAForward, LOW);
  digitalWrite(motorABackward, LOW);
  digitalWrite(motorBForward, LOW);
  digitalWrite(motorBBackward, LOW);
  analogWrite(motorAPWM, 0);
  analogWrite(motorBPWM, 0);
}
