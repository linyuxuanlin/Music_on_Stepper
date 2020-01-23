#include <math.h>

#define FR_L 2   //Left  motor: Direction
#define STEP_L 11 //Left  motor: PWM pulse, One pulse means one step for the Step Motor
#define FR_R 4   //Right motor: Direction
#define STEP_R 5 //Right motor: PWM pulse, One pulse means one step for the Step Motor
#define STOP 6   //Enable motor, Active HIGH
#define BUTTON 8

//#define FR_L   D4    //Left  motor: Direction
//#define STEP_L D0    //Left  motor: PWM pulse, One pulse means one step for the Step Motor
//#define FR_R   D7    //Right motor: Direction
//#define STEP_R D3    //Right motor: PWM pulse, One pulse means one step for the Step Motor
//#define STOP   A4    //Enable motor, Active HIGH

float tone_in = 1 ;
int ladder = 12;
float score[] = {3, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 3, 2, 2};

double tone_to_freq(float tone) {
  double num;
  int x;
  double freq;
  if (tone > 7 && tone <= 7 + ladder) {
    x = 12;
    tone -= 12;
  } else if (tone > 7 + ladder && tone <= 7 + 2 * ladder) {
    x = 24;
    tone -= 24;
  }

  if (tone == 1)
    num = 1;
  else if (tone == 1.5)
    num = 2;
  else if (tone == 2)
    num = 3;
  else if (tone == 2.5)
    num = 4;
  else if (tone == 3)
    num = 5;
  else if (tone == 4)
    num = 6;
  else if (tone == 4.5)
    num = 7;
  else if (tone == 5)
    num = 8;
  else if (tone == 5.5)
    num = 9;
  else if (tone == 6)
    num = 10;
  else if (tone == 6.5)
    num = 11;
  else if (tone == 7)
    num = 12;
  freq = 1975.5 * exp(-0.058 * (num + x));
  return freq;
}



void setup()
{

  pinMode(FR_L,   OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(STOP, OUTPUT);
  pinMode(BUTTON,INPUT);
  digitalWrite(FR_L,   LOW);
  digitalWrite(STEP_L, LOW);
  digitalWrite(STOP, LOW);
  digitalWrite(STOP, HIGH);
  Serial.begin(9600);
  /*

    Serial.println(tone_to_freq(2 + 2 * ladder));
    for (int j = 0; j < sizeof(score) / sizeof(score[0]); j++) {
    double z = tone_to_freq(score[j]);
    for (int a = 0; a < 100000; a++) {
      digitalWrite(STEP_L, HIGH);
      delayMicroseconds(z);
      digitalWrite(STEP_L, LOW);
      delayMicroseconds(z);
    }
    delay(200);
    }
  */
  
}

void loop()
{
  //digitalWrite(STOP, LOW);
  //if(digitalRead(BUTTON)==0){
   // tone_in++;
  //}
  double freq_out=tone_to_freq(tone_in);
  for (int a = 0; a < 1000; a++) {
  digitalWrite(STEP_L, HIGH);
  delayMicroseconds(freq_out);
  digitalWrite(STEP_L, LOW);
  delayMicroseconds(freq_out);
  }
  digitalWrite(STOP, LOW);
  delay(1000);
  digitalWrite(STOP, HIGH);
  tone_in++;
}


/*
  void setMotorSpeed(int speed)
  {
  unsigned int abs_speed;
  motor_speed_ = speed;
  abs_speed = abs(motor_speed_);

  if (abs_speed < min_speed_)  abs_speed = min_speed_;
  if (abs_speed > max_speed_)  abs_speed = max_speed_;

  if (motor_speed_ >= 0)
  {
    digitalWrite(FR_L,  HIGH);
    //analogWrite(STEP_L, 200, abs_speed);
    analogWrite(STEP_L, abs_speed);

  }
  else
  {
    digitalWrite(FR_L,  LOW);
    //analogWrite(STEP_L, 200, abs_speed);
    analogWrite(STEP_L, abs_speed);
  }
  }

*/

/*
  int32_t  StepMotorControl::getEncoder(void)
  {
  return motor_speed_;
  }

  void StepMotorControl::disableMotors()
  {
  digitalWrite(stop_pin_, LOW);
  is_stopped_ = true;
  motor_speed_ = 0;
  }
  bool StepMotorControl::isStopped(void)
  {
  return is_stopped_;
  }
  void StepMotorControl::setMaxSpeed(int speed)
  {
  max_speed_ = speed;
  }
  void StepMotorControl::setMinSpeed(int speed)
  {
  min_speed_ = speed;
  }
*/
