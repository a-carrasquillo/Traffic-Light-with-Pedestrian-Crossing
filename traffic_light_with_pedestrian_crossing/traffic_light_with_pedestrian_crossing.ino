//right light of primary road
int greenRP = 0;
int yellowRP = 1;
int redRP = 2;

//left light of primary road, SOLO
int greenLP = 3;
int yellowLP = 4;
int redLP = 5;

//right light of secondary road
int greenRS = 6;
int yellowRS = 7;
int redRS = 8;

//left light of secondary road, SOLO
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
  //right light of primary road
  pinMode(greenRP,OUTPUT);
  pinMode(yellowRP,OUTPUT);
  pinMode(redRP,OUTPUT);
  //left light of primary road, SOLO
  pinMode(greenLP,OUTPUT);
  pinMode(yellowLP,OUTPUT);
  pinMode(redLP,OUTPUT);
  //right light of secondary road
  pinMode(greenRS,OUTPUT);
  pinMode(yellowRS,OUTPUT);
  pinMode(redRS,OUTPUT);
  //left light of secondary road, SOLO
  pinMode(greenLS,OUTPUT);
  pinMode(yellowLS,OUTPUT);
  pinMode(redLS,OUTPUT);
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
     //turn off solo
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
    //turn off solo
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
  //delay(20000);
  return;
}
int turnGreen(int red, int green, int button, int redSolo, int greenSolo, int pedestrian)
{
  //turn red off
  //digitalWrite(red,LOW);
  if(pedestrian==0)
  {
    digitalWrite(redSolo,LOW);
    delay(250);
    digitalWrite(red, HIGH);
    //turn on green
    //digitalWrite(green,HIGH);
    solo(greenSolo);
    delay(3000);
  }
  else
  {//pedestrian crossing
    digitalWrite(redSolo,LOW);
    digitalWrite(greenSolo, HIGH);
  }
  //delay(20000);
  
  digitalWrite(red,LOW);
  delay(250);
  digitalWrite(green,HIGH);
  int state = 0;
  for(int i=1; i<21; i++){
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

void solo(int green)
{
  for(int i = 1; i<21; i++)
  {
    digitalWrite(green, LOW);
    //blinking green 
    delay(500);
    digitalWrite(green,HIGH);
    delay(500);
  }
  return;
}
