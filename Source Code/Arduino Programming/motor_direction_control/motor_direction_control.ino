//  Motor 1 Details
volatile int M1_C1 = 7;
volatile int M1_C2 = 6;

volatile long encoderCount_M1 = 0;
volatile int encoderDirection_M1 = 0;

int previousStateA_M1 = 0;
int previousStateB_M1 = 0;

const int M1_1 = 9;
const int M1_2 = 8;
const int M1_en = 10;

//  Motor 2 details

const int M2_C1 = 3; 
const int M2_C2 = 2;

volatile long encoderCount_M2 = 0;
volatile int encoderDirection_M2 = 0;

int previousStateA_M2 = 0;
int previousStateB_M2 = 0;

const int M2_1 = 12;
const int M2_2 = 13;
const int M2_en = 11;

volatile int lastEncoded_2 = 0;
volatile int lastEncoded_1 = 0;

// Function declaration
void handle_motor_speed(String);
void provide_encoder_values();
void set_speed(int,int);
void forward();
void backward();
void stop_motor();
void leftward();
void rightward();

void setup() {
  Serial.begin(9600);

  // Motor 1 Pins related

  pinMode(M1_C1,INPUT_PULLUP);
  pinMode(M1_C2,INPUT_PULLUP);

  // Enable PCIE2 Bit3 = 1 (Port D)
  PCICR |= B00000100;
  // Select PCINT23 Bit7 = 1 (Pin D7)
  PCMSK2 |= B11000000;

  pinMode(M1_1,OUTPUT);
  pinMode(M1_2,OUTPUT);
  pinMode(M1_en,OUTPUT);


  //  Motor2 pins related
  pinMode(M2_C1, INPUT_PULLUP);
  pinMode(M2_C2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(M2_C1), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(M2_C2), updateEncoder, CHANGE);

  pinMode(M2_1,OUTPUT);
  pinMode(M2_2,OUTPUT);
  pinMode(M2_en,OUTPUT);
  
}

void loop() {

  static String command; // Static variable to store the received data between loop iterations

  while (Serial.available() > 0) {
    char incomingChar = Serial.read(); 
    
//     Serial.println(incomingChar);
     
    if (incomingChar == '\n') { 
      
      if(command[0] == 'm'){
        handle_motor_speed(command);
        Serial.println("ok");
   }

     else if(command[0] == 'e'){
      provide_encoder_values();
//      Serial.println(String(encoderCount_M1)+" "+String(encoderCount_M3));
      
    }
    command = "";
    }
      
    else {
      command += incomingChar;
    }

   
  
}



}

//  Motor1 interrupt service routine

void handle_motor_speed(String s){
  if(s.length() > 0){
  int index = s.indexOf(' ');
  int left_motor_speed = s.substring(1,index).toInt();
  int right_motor_speed = s.substring(index+1).toInt();
  set_speed(left_motor_speed,right_motor_speed);

  }
  
}

void provide_encoder_values(){
//  Serial.println(String(encoderCount_M1)+" "+String(encoderCount_M3));
Serial.print(encoderCount_M1);
Serial.print(" ");
Serial.println(encoderCount_M2);
}

void forward(){
//  Serial.println(/"Moving forward..");
  digitalWrite(M1_1,HIGH);
  digitalWrite(M1_2,LOW);
  digitalWrite(M2_1,HIGH);
  digitalWrite(M2_2,LOW);
  
}

void backward(){
//  Serial.println/("moving backward");
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,HIGH);
  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,HIGH);
}

void stop_motor(){
//  Serial.println/("Stop...");
  analogWrite(M1_en,0);
  analogWrite(M2_en,0);
  digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,LOW);
  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,LOW);

}

void leftward(){
//  Serial/.println("moving leftward..");
   digitalWrite(M1_1,LOW);
  digitalWrite(M1_2,HIGH);
  digitalWrite(M2_1,HIGH);
  digitalWrite(M2_2,LOW);
}

void rightward(){
//  Serial/.println("moving rightward...");
  digitalWrite(M1_1,HIGH);
  digitalWrite(M1_2,LOW);
  digitalWrite(M2_1,LOW);
  digitalWrite(M2_2,HIGH);
}

void set_speed(int left_motor_speed,int right_motor_speed){

  if(left_motor_speed > 0 and right_motor_speed > 0){
    forward();
  }

  else if(left_motor_speed < 0 and right_motor_speed < 0){
    backward();
  }

  else if(left_motor_speed > 0 and right_motor_speed < 0){
    rightward();
  }

  else if(left_motor_speed < 0 and right_motor_speed > 0){
    leftward();
  }

  left_motor_speed = abs(left_motor_speed);
  right_motor_speed = abs(right_motor_speed);

  analogWrite(M1_en,left_motor_speed);
  analogWrite(M2_en,right_motor_speed);
}




ISR (PCINT2_vect)
{
 
  // int currentStateA_M1 = digitalRead(M1_C1);
  // int currentStateB_M1 = digitalRead(M1_C2);
 
  // if (currentStateA_M1 != previousStateA_M1)
  // {
	// if (currentStateA_M1 == currentStateB_M1)
	// {
  // 	encoderCount_M1++;
  // 	encoderDirection_M1 = 1;  // Clockwise rotation
	// }
	// else
	// {
  // 	encoderCount_M1--;
  // 	encoderDirection_M1 = -1;  // Counter-clockwise rotation
	// }
  // }

  // else if (currentStateB_M1 != previousStateB_M1){
	// if (currentStateA_M1 == currentStateB_M1)
	// {
  // 	encoderCount_M1--;
  // 	encoderDirection_M1 = -1;  // Counter-clockwise rotation
	// }
	// else
	// {
  // 	encoderCount_M1++;
  // 	encoderDirection_M1 = 1;  // Clockwise rotation
	// }
  // }
 
  // // Update previous state variables

  // previousStateA_M1 = currentStateA_M1;
  // previousStateB_M1 = currentStateB_M1;
  // Serial.print("Motor 1 = ");
  // Serial.println(encoderCount_M1);

  int MSB = digitalRead(M1_C1); //MSB = most significant bit
  int LSB = digitalRead(M1_C2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded_1 << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderCount_M1 --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderCount_M1 ++;

  lastEncoded_1 = encoded; //store this value for next time



 
}



//Motor2 Interrupt Service routine

void updateEncoder() {
  // // Read the state of the encoder pins
  // int currentStateA_M2 = digitalRead(M2_C1);
  // int currentStateB_M2 = digitalRead(M2_C2);
  // // Serial.print("A = ");
  // // Serial.println(currentStateA_M1);
  // // Serial.print("B = ");
  // // Serial.println(currentStateB_M1);

  
  // if (currentStateA_M2 != previousStateA_M2)
  // {
	// if (currentStateA_M2 == currentStateB_M2)
	// {
  // 	encoderCount_M2++;
  // 	encoderDirection_M2 = 1;  // Clockwise rotation
	// }
	// else
	// {
  // 	encoderCount_M2--;
  // 	encoderDirection_M2 = -1;  // Counter-clockwise rotation
	// }
  // }

  // else if (currentStateB_M2 != previousStateB_M2){
	// if (currentStateA_M2 == currentStateB_M2)
	// {
  // 	encoderCount_M2--;
  // 	encoderDirection_M2 = -1;  // Counter-clockwise rotation
	// }
	// else
	// {
  // 	encoderCount_M2++;
  // 	encoderDirection_M2 = 1;  // Clockwise rotation
	// }
  // }
 
  // // Update previous state variables

  // previousStateA_M2 = currentStateA_M2;
  // previousStateB_M2 = currentStateB_M2;

  // Serial.print("Motor 2 = ");
  // Serial.println(encoderCount_M2);
  
  int MSB = digitalRead(M2_C1); //MSB = most significant bit
  int LSB = digitalRead(M2_C2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded_2 << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderCount_M2 --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderCount_M2 ++;

  lastEncoded_2 = encoded; //store this value for next time


}


