
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
  
  void turnPinger(bool direction){
    //code for turning the pinger left or right
    //i've seen that thing move.
    //no idea how it worked
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
  
  //theres a lot of repitition here. I'm certian theres a more concise way to write this.
  if (left.motion_detected()) {
    pinger.turnPinger(false);
    distanceToObject = pinger.getDistance();
    Serial.print('Movement Detected on the left, inches: ');
    Serial.print(distanceToObject);
    //move towards movement
  }
  if (right.motion_detected()) {
    pinger.turnPinger(true);
    distanceToObject = pinger.getDistance();
    Serial.print('Movement Detected on the right, inches: ');
    Serial.print(distanceToObject);
    //movetowards movement
  } 
  Serial.print('No motion Detected');
  delay(1000);
  
}
