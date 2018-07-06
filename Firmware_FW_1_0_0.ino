  int stepPin= 3;
  int dirPin= 2;
  int MS1=8;
  int MS2=7;
  int MS3=6;  
  int v=-1;
  int prevDir=0;
  int filterNo=0;
  #define LEFT 49
  #define RIGHT 50
  #define CHANGENO 51
  #define getInfo 0


void setup() {
 pinSetup();
 serialSetup();
 delay (100);
 Serial.println("READY TO GO");
 
 
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
          v=0;
}
else if (v==CHANGENO)
{
  filterNoSetup();
}
else if (v==getInfo)
{
  getInformation();
}



}



/////////////////////////////////
void serialSetup()
{
  Serial.begin (9600) ;
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
    if (v==RIGHT) //checks for rotation=left
        {
          digitalWrite (dirPin, LOW); Serial.println("Direction set to right"); //sets direction of slew to RIGHT;
        }
   else if (v==LEFT)    
        {
           digitalWrite(dirPin,HIGH);Serial.println("Direction set to left"); //sets direction of slew to LEFT;
          
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
            Serial.println("Filter changed");
}


void filterNoSetup(){
 
     while (!Serial.available()){
  }
   filterNo=Serial.parseInt();
}

void getInformation()
{
  Serial.println("COM diagnosis: Successful";)
  Serial.println("Firmware version: 1.0.0";)
}


