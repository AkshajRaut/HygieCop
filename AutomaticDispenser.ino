int trigPin = 9;
int echoPin = 10;
int led = 13;
long duration, distance;


void setup() 
{
  Serial.begin(9600);
  pinMode(2,OUTPUT); 
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

//To initiate Ultrasonic sensor and calculate distance 

void calculate()
{
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(1000); 
}


void loop() 
{
  
  calculate();
  
 //To check if hand is detected in front of sensor and then dispense sanitizer
 
 if(distance<=10) 
  {
    digitalWrite(led, HIGH);
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    do
    {
     digitalWrite(led, LOW);
     digitalWrite(2, LOW);
     calculate();
    }
    while(distance<=10);
   }
   else 
 {
     digitalWrite(led, LOW);
     digitalWrite(2, LOW);
  }
    
}
