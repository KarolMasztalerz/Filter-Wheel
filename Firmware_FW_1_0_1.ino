  int stepPin= 3;
  int dirPin= 2;
  int MS1=8;
  int MS2=7;
  int MS3=6;  
  int v=-1;
  int prevDir=0;
  int filterNo=8;
  int cFilter=1;
  #define LEFT 49
  #define RIGHT 50
  #define CHANGENO 51
  #define getInfo 48


void setup() {
 pinSetup();
 serialSetup();
 delay (100);

 
 
}

void loop() {
 
         if(Serial.available()>0)
            { 
               v=Serial.read();  
            } 



if (v==RIGHT||v==LEFT)
{
          directionSet();
            filterChange();
            Serial.println("Filter changed");
          v=200;
}
else if (v==CHANGENO)
{    v=200; //sets V to arbitary number to prevent stack overflow due to infinite reiteration of command.
  filterNoSetup(); //next input sets the number of filters in the filter wheel.
  return 0;
}
else if (v==getInfo)
{
  getInformation(); //gets information about firmware and state.
}
else (Serial.println("-1"));


}



/////////////////////////////////
void serialSetup()
{
  Serial.begin (9600) ; //starts a COM Port, Baud rate 9600.
}



/////////////////////////////////

void pinSetup()
{  
  pinMode(3, OUTPUT); //stepPin
  pinMode(2, OUTPUT); //dirPin
  pinMode(6, OUTPUT); //MS3
  pinMode(7, OUTPUT); //MS2
  pinMode(8, OUTPUT); //MS1
}


////////////////////////////////

void directionSet()
{ if(prevDir!=v){
    if (v==RIGHT) //checks for rotation=right
        {
          digitalWrite (dirPin, LOW); Serial.println("0"); //sets direction of slew to RIGHT;
          cFilter++;
        }
   else if (v==LEFT)    
        {
           digitalWrite(dirPin,HIGH);Serial.println("0"); //sets direction of slew to LEFT;
          cFilter--;
        }
        
        prevDir=v;
}
}



void filterChange()
{
   digitalWrite (MS1, HIGH); //uses halfsteps instead of fullsteps
  
  digitalWrite (MS2, LOW);  //uses halfsteps instead of fullsteps
  
  digitalWrite (MS3, LOW);  //uses halfsteps instead of fullsteps
  
            for (int i=0;i<(360/filterNo)/0.9;i++) //filter change, 360/filter amount degrees in halfsteps each 0.9 degree.
            {
                digitalWrite(stepPin, HIGH);
                delay (8);
                digitalWrite(stepPin ,LOW);
                delay (8);
                
                
            }
            Serial.println("0");
            
}


void filterNoSetup(){
 
   while (!Serial.available());
   filterNo=Serial.parseInt();
 
}

void getInformation()
{
  Serial.println("COM diagnosis: Successful");
  Serial.println("Firmware version: 1.0.0");
}


