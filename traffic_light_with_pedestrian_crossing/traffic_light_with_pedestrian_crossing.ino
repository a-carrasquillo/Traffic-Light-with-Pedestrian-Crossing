/*
In this project, we look to simulate an intersection 
of a primary road with a secondary one. Every road 
has four tracks, of which two are solos. 
Each road has a pedestrian button than turns that 
road traffic light to red and the other one 
can only go forward, the solo is not activated 
until the pedestrian crosses.
*/
//Global Variables
//right traffic light of primary road
//RP stands for Right Primary
int greenRP = 0;
int yellowRP = 1;
int redRP = 2;

//left traffic light of primary road, SOLO
//LP stands for Left Primary
int greenLP = 3;
int yellowLP = 4;
int redLP = 5;

//right traffic light of secondary road
//RS stands for Right Secondary
int greenRS = 6;
int yellowRS = 7;
int redRS = 8;

//left traffic light of secondary road, SOLO
//LS stands for Left Secondary
int greenLS = 9;
int yellowLS = 10;
int redLS = 11;

//pushbuttons
int primaryB = 12;
int secondaryB = 13;

//pedestrian state
int state1=0;
int state2=0;

void setup() {
  //pushbuttons
  pinMode(primaryB, INPUT);
  pinMode(secondaryB,INPUT);
  
  //right traffic light of primary road
  pinMode(greenRP,OUTPUT);
  pinMode(yellowRP,OUTPUT);
  pinMode(redRP,OUTPUT);
  
  //left traffic light of primary road, SOLO
  pinMode(greenLP,OUTPUT);
  pinMode(yellowLP,OUTPUT);
  pinMode(redLP,OUTPUT);
  
  //right traffic light of secondary road
  pinMode(greenRS,OUTPUT);
  pinMode(yellowRS,OUTPUT);
  pinMode(redRS,OUTPUT);
  
  //left traffic light of secondary road, SOLO
  pinMode(greenLS,OUTPUT);
  pinMode(yellowLS,OUTPUT);
  pinMode(redLS,OUTPUT);

  //Initial state of secondary road
  //turning red the secondary road
  digitalWrite(redLS, HIGH);
  digitalWrite(redRS, HIGH);
}

void loop() {
  if(state2==0)
  {
    //turn on primary road
    state1 = turnGreen(redRP, greenRP, primaryB, redLP, greenLP, state2);
    //turn off primary road
    turnRed(redRP, yellowRP, greenRP, redLP, yellowLP, greenLP);
    
    delay(4000);
  }
  else
  {//pedestrian crossing in secondary road
    //turn green, and send that the pedestrian is crossing
    state1 = turnGreen(redRP, greenRP, primaryB, redLP, greenLP, state2);
    //turn off primary road
    turnRed(redRP, yellowRP, greenRP, redLP, yellowLP, greenLP);
    delay(1000);
    digitalWrite(redLP,LOW);
    //turn the solo, because they were not able to cross because of the pedestrian
    solo(greenLP);
    
    delay(4000);
    
    //turn off green
    digitalWrite(greenLP,LOW);
    delay(250);
    //turn on yellow
    digitalWrite(yellowLP,HIGH);
    delay(6000);
    //turn off yellow
    digitalWrite(yellowLP,LOW);
    delay(250);
    //turn on red
    digitalWrite(redLP,HIGH);
    state2 = 0;//reset
    delay(4000);
  }

  
  if(state1==0)
  {
    //turn on secondary road
    state2 = turnGreen(redLS, greenLS, secondaryB, redRS, greenRS, state1);
    //turn off secondary road
    turnRed(redLS, yellowLS, greenLS, redRS, yellowRS, greenRS);
    delay(4000);
  }
  else
  {//pedestrian crossing primary road
    state2 = turnGreen(redLS, greenLS, secondaryB, redRS, greenRS, state1);
    //turn off secondary road
    turnRed(redLS, yellowLS, greenLS, redRS, yellowRS, greenRS);
    delay(1000);
    digitalWrite(redRS,LOW);
    
    solo(greenRS);
    
    //turn off green
    digitalWrite(greenRS,LOW);
    delay(250);
    //turn on yellow
    digitalWrite(yellowRS,HIGH);
    delay(6000);
    //turn off yellow
    digitalWrite(yellowRS,LOW);
    delay(250);
    //turn on red
    digitalWrite(redRS,HIGH);
    state1 = 0;//reset
    delay(4000);
  }
  
}

//Function that helps turn a road traffic light to red
void turnRed(int red,int yellow, int green, int redSolo, int yellowSolo, int greenSolo)
{
  //turn off green
  digitalWrite(green,LOW);
  digitalWrite(greenSolo,LOW);
  delay(250);
  
  //turn on yellow
  digitalWrite(yellow,HIGH);
  digitalWrite(yellowSolo,HIGH);
  delay(6000);
  
  //turn off yellow
  digitalWrite(yellow,LOW);
  digitalWrite(yellowSolo,LOW);
  delay(250);
  
  //turn on red
  digitalWrite(red,HIGH);
  digitalWrite(redSolo,HIGH);
  
  return;
}

//Function that helps turn a road traffic light to green
int turnGreen(int red, int green, int button, int redSolo, int greenSolo, int pedestrian)
{
  if(pedestrian==0)
  {
    digitalWrite(redSolo,LOW);
    delay(250);
    digitalWrite(red, HIGH);
    //turn on green
    solo(greenSolo);
    delay(3000);
  }
  else
  {//pedestrian crossing
    digitalWrite(redSolo,LOW);
    digitalWrite(greenSolo, HIGH);
  }
  
  digitalWrite(red,LOW);
  delay(250);
  digitalWrite(green,HIGH);
  
  int state = 0;
  
  for(int i=1; i<21; i++)
  {
    state = digitalRead(button);
    if (state == 0){
      delay(1000);
    }
    else if(state == 1){
      //pedestrian crossing
      delay(1000);
      return state;
    }
  }//end of FOR
  return state;
}

//Function that helps turn on the SOLO
void solo(int green)
{
  for(int i = 1; i<21; i++)
  {
    //blinking green 
    digitalWrite(green, LOW);
    delay(500);
    digitalWrite(green,HIGH);
    delay(500);
  }
  return;
}
