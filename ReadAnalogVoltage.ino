/*

  Using 12k Ohm and 5k Ohm voltage divider.
  Voltage Ratio 17V/5V = 3.4
  5v Voltage Reference / 1023 = 0.004888
 
 */
int starts = 0; 
unsigned long duration;

int pin = 6; //Rx Pulse reading
int led = 11; //Green
int led2 = 9; //Blue
int led3 = 10; //Red

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  //Serial.begin(9600);
}

void loop()  
{  
  receivercheck();  
  celldetect();
  voltagemonitor();  
}

void receivercheck()
{
    duration = pulseIn(pin, HIGH);
    while(duration < 900)
    {
      duration = pulseIn(pin, HIGH);
      analogWrite(led, 100);
      digitalWrite(led3, HIGH);
      delay(350);
      digitalWrite(led, LOW);
      digitalWrite(led3, LOW);
      delay(50);    
    }
}


//Monitor voltage and reports using LED.
void voltagemonitor()  {
  int sensorValue = analogRead(A0);
  float voltage = (sensorValue * 0.004888)* 3.32;

  if(voltage <= 1)
  {
    //do nothing
  }  
  else if(voltage <= (4.2*2)) //Handles 2 Cells lipo
  {  
    if(voltage <= (3.62*2))
    {
      for(int i=0; i<4; i++)
      {
        digitalWrite(led3, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);        
        delay(50);
      }  
    } 
    else if(voltage <= (3.65*2)) 
    { 
      for(int i=0; i<2; i++)
      {
        digitalWrite(led3, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);        
        delay(50);
      }
      delay(500);
    }   
    else if(voltage <= (3.75*2)) //3.7/cells
    {
      for(int i=0; i<2; i++)
      {
        analogWrite(led, 100); 
        digitalWrite(led3, HIGH);        
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);        
        delay(50);
      }
      delay(2500);
    }   
    else if(voltage <= (4.1*2))   
    {
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);       
        delay(3000);
     }    
  }
    
  // //Handles 3 Cell Lipo.
  else if(voltage <= (4.2*3)) 
  {  
    if(voltage <= (3.62*3))
    {
      for(int i=0; i<4; i++)
      {
        digitalWrite(led3, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);        
        delay(50);
      }  
    } 
    else if(voltage <= (3.65*3)) 
    { 
      for(int i=0; i<2; i++)
      {
        digitalWrite(led3, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);        
        delay(50);
      }
      delay(500);
    }   
    else if(voltage <= (3.75*3)) //3.7/cells
    {
      for(int i=0; i<2; i++)
      {
        analogWrite(led, 100);
        digitalWrite(led3, HIGH);        
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);        
        delay(50);
      }
      delay(2500);
    }   
    else if(voltage <= (4.1*3))   
    {
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(led2, LOW);        
        digitalWrite(led3, LOW);       
        delay(3000);
     }    
  }
}

//Detect number of Cells and Blink LED based on number of Lipo Cells Only done Once.
void celldetect() {
  int sensorValue = analogRead(A0);
  float voltage = (sensorValue * 0.004888)* 3.32;
  
  if(voltage <= 8.4 && starts ==0)
  { 
    delay(2000);
    for(int i=0; i<2; i++)
    {
      digitalWrite(led2, HIGH);
      delay(200);
      digitalWrite(led2, LOW);
      delay(200);
    }
    starts=1;
    delay(1000);
  }  
  else if(voltage <= 12.6 && starts == 0)
  { 
    for(int i=0; i<3; i++)
    {
      digitalWrite(led2, HIGH);
      delay(200);
      digitalWrite(led2, LOW);
      delay(200);
    } 
    starts=1;
    delay(1000);
  }  
  delay(20);
}
