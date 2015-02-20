
int led = 13;

class PassiveInfraredSensor {
  int _input_pin;
  
  public:
  
  PassiveInfraredSensor(const int input_pin) {
    _input_pin = input_pin;
    pinMode(_input_pin, INPUT);
  }
  
  const bool motion_detected() const {
    return digitalRead(_input_pin) == HIGH;
  }
};

//Ping class contains all login for Pinging
class Ping {
  //since theres only two directions, its easiest to just say false for left, true for right
  bool _isRight;
  //these are both internal variables for the motion class
  int _inputPingPin; 
  
  long _duration, _inches;
  
  public:
  //this may need an output pin,not sure
  Ping(const int inputPingPin) {
    //this is setting the internal variable to the given
    _inputPingPin = inputPingPin;
    
    pinMode(_inputPingPin, INPUT);
  }
  
  void turnPinger(char direction){
    
    if (direction == 'left') {
     //move the pinger to the left 
    } else if (direction == 'right'){
    //move it to the right
    }
     
  }
  
  //taken from http://arduino.cc/en/Tutorial/ping
  long getDistance(){
    pinMode(_inputPingPin, OUTPUT);
    digitalWrite(_inputPingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_inputPingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_inputPingPin, LOW);
  
    pinMode(_inputPingPin, INPUT);
    _duration = pulseIn(_inputPingPin, HIGH);
    
    _inches = _microsecondsToInches(_duration); 
    return _inches;   
  }
  
  private:
  
  long _microsecondsToInches(long microseconds){
    return microseconds / 74 / 2;
  
  }
  
    
  
};

class Motion{
//Motion class will contain all logic for motion. 
//thats turning the bot and moving it and stopping it when it hits something
//the accelerometer stuff goes here as well as the motor stuff
};

//use input pin 2
PassiveInfraredSensor left(2);
//use input pin 3
PassiveInfraredSensor right(3);
//use input pin 7
Ping pinger(7);

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  
  long distanceToObject; 
  
  char most_recent;
  bool left_movement;
  bool right_movement;
  
  //wait until movement has stopped for 2 secs before actually moving that way.
  for (int i = 0; i <= 1; i++) {
     left_movement = left.motion_detected();
     right_movement = right.motion_detected();
    if (left_movement || right_movement) {
      i = 0;
      //ternary operator, very slick.
      most_recent = (left_movement ? 'left' : 'right');
      delay(1000);
      continue;
    } else {
      i++;
      delay(1000);
      continue;
    }
  }
  //after no movement for 2 seconds,
  //if there has been any movement at all since the last time you moved
  //explicit checks on value.
  if (!most_recent == 'left' || !most_recent == 'right'){
    pinger.turnPinger(most_recent);
    distanceToObject = pinger.getDistance();
    
    Serial.print('Recent movement on the ' 
    + most_recent + '. Distance of ' + char(distanceToObject) + 'inches.');
   //ideally, move the bot towards the most recent movement 
  }
  Serial.print('No motion Detected');
  delay(1000);
  
}
