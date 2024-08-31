#include "AccelStepper.h"

// 電機步進方式定義
#define FULLSTEP 4  // 全步進模式

// 定義步進電機引腳
#define MOTOR_BYJ_1_PIN1 8   // 一号28BYJ48連接的ULN2003電機驅動板引腳 in1
#define MOTOR_BYJ_1_PIN2 9   // 一号28BYJ48連接的ULN2003電機驅動板引腳 in2
#define MOTOR_BYJ_1_PIN3 10  // 一号28BYJ48連接的ULN2003電機驅動板引腳 in3
#define MOTOR_BYJ_1_PIN4 11  // 一号28BYJ48連接的ULN2003電機驅動板引腳 in4

#define MOTOR_BYJ_2_PIN1 28  // 二号28BYJ48連接的ULN2003電機驅動板引腳 in1
#define MOTOR_BYJ_2_PIN2 26  // 二号28BYJ48連接的ULN2003電機驅動板引腳 in2
#define MOTOR_BYJ_2_PIN3 24  // 二号28BYJ48連接的ULN2003電機驅動板引腳 in3
#define MOTOR_BYJ_2_PIN4 22  // 二号28BYJ48連接的ULN2003電機驅動板引腳 in4

#define OPEN_ANGLE -2048  // 定義打開角度

// 定義兩個步進電機對象
AccelStepper door_open_stepper1(FULLSTEP, MOTOR_BYJ_1_PIN1, MOTOR_BYJ_1_PIN3, MOTOR_BYJ_1_PIN2, MOTOR_BYJ_1_PIN4);
AccelStepper door_open_stepper2(FULLSTEP, MOTOR_BYJ_2_PIN1, MOTOR_BYJ_2_PIN3, MOTOR_BYJ_2_PIN2, MOTOR_BYJ_2_PIN4);

// 定義訊號變數
bool isAtCorrectPosition = false;  // 初始狀態為未到達正確位置

void setup() {
  // 設定電機最大速度和加速度
  door_open_stepper1.setMaxSpeed(500.0);
  door_open_stepper1.setAcceleration(50.0);
  door_open_stepper2.setMaxSpeed(500.0);
  door_open_stepper2.setAcceleration(50.0);

  // 初始化其他系統設定（如按鈕、感測器等）
  // 這部分根據您的整個系統來設定
}

void loop() {
  // 其他系統的程式碼部分，例如控制盒子移動到正確位置
  // 當盒子移動到正確位置時，設定 isAtCorrectPosition 為 true
  // 例如：
  // if (/* 判斷盒子到達正確位置 */) {
  //   isAtCorrectPosition = true;
  // }

  // 假設這裡有一段程式碼會在適當時候將 isAtCorrectPosition 設為 true
  // 例如：
  // simulateArrival(); // 模擬盒子到達位置

  // 控制底部活版門開合
  controlHatch();

  // 執行步進電機運行
  door_open_stepper1.run();
  door_open_stepper2.run();
}

// 控制底部活版門開合的函數
void controlHatch() {
  if (isAtCorrectPosition) {
    if (door_open_stepper1.currentPosition() == 0 && door_open_stepper2.currentPosition() == 0) {
      // 打開活版門
      door_open_stepper1.moveTo(OPEN_ANGLE);
      door_open_stepper2.moveTo(OPEN_ANGLE);
      delay(500);  // 短暫延遲，確保命令被執行
    } 
    else if (door_open_stepper1.currentPosition() == OPEN_ANGLE && door_open_stepper2.currentPosition() == OPEN_ANGLE) {
      // 關閉活版門
      door_open_stepper1.moveTo(0);
      door_open_stepper2.moveTo(0);
      delay(500);  // 短暫延遲，確保命令被執行
      // 活版門關閉後，可以重置訊號狀態，等待下一次操作
      isAtCorrectPosition = false;
    }
  }
}

// 模擬盒子到達正確位置的函數（僅供測試，實際應根據系統需求實現）
void simulateArrival() {
  // 這裡可以加入條件判斷，例如感測器讀取等
  // 當條件滿足時，設定 isAtCorrectPosition 為 true
  // 例如：
  // if (sensorValue > threshold) {
  //   isAtCorrectPosition = true;
  // }
}
