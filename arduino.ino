int motorright = 9;                                                              
int motorrightdir  = 7;
int motorleft = 10;
int motorleftdir  = 8;

long duration;
int distance;
bool isForward = false;

const int echoPinLeft = 13;
const int trigPinLeft = 11;

const int echoPinFront = 4;
const int trigPinFront = 5;

const int echoPinRight = 2;
const int trigPinRight = 3;

//For serial receive.
const byte numChars = 11;
char receivedChars[numChars]; // an array to store the received data
String received; //The data as a string
boolean newData = false;

void setup() {
  pinMode(motorright, OUTPUT);                                                      
  pinMode(motorleft, OUTPUT);     
  pinMode(motorrightdir, OUTPUT);  
  pinMode(motorleftdir, OUTPUT);  

  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinFront, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinFront, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); //normal printing
}

void loop() 
{
  if(isForward) forward(120);
  int left = ultrasonic(echoPinLeft,trigPinLeft);
  int front = ultrasonic(echoPinFront,trigPinFront);
  int right = ultrasonic(echoPinRight,trigPinRight);
  if(left > 99) {
    left = 99;
  }
  if(front > 99) {
    front = 99;
  }
  if(right > 99) {
    right = 99;
  }
  String a,b,c = "";
  if(left < 10) {
    a = "0";
  }
  if(front < 10) {
    b = "0";
  }
  if(right < 10) {
    c = "0";
  }
  String message = "";
  message = message + "[" + a + left + "cm," + b + front + "cm," + c + right + "cm]\n";
  Serial.print(message);
  delay(50);
  recvWithEndMarker();
  processCommand();              
}

int ultrasonic(int echoPin, int trigPin) {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
return distance;
}

void processCommand() {
 if (newData == true)
 {
  String instruction = received.substring(0,5);
  String data = received.substring(6,10);
  if(instruction == "MOVEF") {
    forward(data.toInt());
    isForward = true;
  } else {
    isForward = false;
  }
  if(instruction == "MOVEB") backward(data.toInt());
  if(instruction == "TURNR") rightward(data.toInt());
  if(instruction == "TURNL") leftward(data.toInt());
  if(instruction == "BACKP") backpivot(data.toInt());
  newData = false;
 }
}

void recvWithEndMarker() 
{
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 while (Serial.available() > 0 && newData == false) 
 {
  rc = Serial.read();

  if (rc != endMarker) 
  {
    receivedChars[ndx] = rc;
    ndx++;
    if (ndx >= numChars) 
    {
      ndx = numChars - 1;
    }
 }
 else 
  {
  receivedChars[ndx] = '\0'; // terminate the string
  received = String(receivedChars);
  ndx = 0;
  newData = true;
  }
 }
}


void forward(int velocity)
{
digitalWrite(motorrightdir, LOW);
analogWrite(motorright,velocity); 
digitalWrite(motorleftdir, LOW);
analogWrite(motorleft, velocity); 

}

void backward(int velocity)
{
digitalWrite(motorrightdir, HIGH);
analogWrite(motorright,velocity); 
digitalWrite(motorleftdir, HIGH);
analogWrite(motorleft, velocity);

}

void leftward(int duration)
{
  digitalWrite(motorleftdir, HIGH);
  digitalWrite(motorrightdir, LOW);
  analogWrite(motorleft,180);
  analogWrite(motorright,180);
  delay(duration/3);
}

void rightward(int duration)
{
  digitalWrite(motorleftdir, LOW);
  digitalWrite(motorrightdir, HIGH);
  analogWrite(motorleft,180);
  analogWrite(motorright,180);
  delay(duration/3);
}

void backpivot(int velocity)
{
  backward(120);
  delay(50);
  stop();
  if(velocity == 180) {
    leftward(120);
  } else {
    rightward(120);
  }
  delay(100);
}

void stop()
{
analogWrite(motorright, 0); 
analogWrite(motorleft, 0);   
}