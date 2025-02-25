/*This sketch is a simple version of the famous Simon Says game. You can use it and improved it adding
levels and everything you want to increase the diffuculty!

There are five buttons connected to A0, A1, A2, A3 and A4.
The buttons from A0 to A3 are used to insert the right sequence while A4 to start the game.

When a wrong sequence is inserted all the leds will blink for three time very fast otherwhise the
inserted sequence is correct.

Hardware needed:
Hardware needed:
1X Arduino Uno
5x pushbuttons
1x Blue led
1x Yellow led
1x Red led
1x Green Led
4x 1k resistors
4x 10k resisors
10x jumpers
1X Buzzer
*/
int velocity = 500;
int vchange = -20;
int error_spot = -1;
int beeplong = 160;

const int MAX_LEVEL = 25; //velocity/abs(vchange);
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;
const int BUZZER = 12;


void setup() {
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);

pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(BUZZER, OUTPUT);

digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
}

void loop()
{
if (level == 1)
generate_sequence();//generate a sequence;

if (digitalRead(A4) == LOW || level != 1) //If start button is pressed or you're winning
{
show_sequence();    //show the sequence
get_sequence();     //wait for your sequence
}
}

void show_sequence()
{
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);

for (int i = 0; i < level; i++)
{
if(error_spot==i)
{
beeplong = 640;
}
digitalWrite(sequence[i], HIGH);
if (sequence[i]==2)
{
for(int k=0;k<beeplong;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(1);//wait for 1ms
   }
    //output another freque
}
if (sequence[i]==3)
{
for(int k=0;k<beeplong/2;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(2);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(2);//wait for 1ms
   }
    //output another freque
}
if (sequence[i]==4)
{
for(int k=0;k<beeplong/3;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(3);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(3);//wait for 1ms
   }
    //output another freque
}
if (sequence[i]==5)
{
for(int k=0;k<beeplong/4;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(4);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(4);//wait for 1ms
   }
    //output another freque
}

delay(velocity);
digitalWrite(sequence[i], LOW);
delay(200);
beeplong = 160;
}
}

void get_sequence()
{
int flag = 0; //this flag indicates if the sequence is correct

for (int i = 0; i < level; i++)
{
flag = 0;
while(flag == 0)
{
if (digitalRead(A0) == LOW)
{
digitalWrite(5, HIGH);
for(int k=0;k<40;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(4);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(4);//wait for 1ms
   }
your_sequence[i] = 5;
flag = 1;
delay(200);
if (your_sequence[i] != sequence[i])
{
error_spot = i;
wrong_sequence();
return;
}
digitalWrite(5, LOW);
}

if (digitalRead(A1) == LOW)
{
digitalWrite(4, HIGH);
for(int k=0;k<53;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(3);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(3);//wait for 1ms
   }
your_sequence[i] = 4;
flag = 1;
delay(200);
if (your_sequence[i] != sequence[i])
{
error_spot = i;
wrong_sequence();
return;
}
digitalWrite(4, LOW);
}

if (digitalRead(A2) == LOW)
{
digitalWrite(3, HIGH);
your_sequence[i] = 3;
for(int k=0;k<80;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(2);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(2);//wait for 1ms
   }
flag = 1;
delay(200);
if (your_sequence[i] != sequence[i])
{
error_spot = i;
wrong_sequence();
return;
}
digitalWrite(3, LOW);
}

if (digitalRead(A3) == LOW)
{
digitalWrite(2, HIGH);
your_sequence[i] = 2;
for(int k=0;k<160;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(1);//wait for 1ms
   }
flag = 1;
delay(200);
if (your_sequence[i] != sequence[i])
{
error_spot = i;
wrong_sequence();
return;
}
digitalWrite(2, LOW);
}
}
}
right_sequence();
}

void generate_sequence()
{
randomSeed(millis()); //in this way is really random!!!

for (int i = 0; i < MAX_LEVEL; i++)
{
sequence[i] = random(2,6);
}
//for (int k = 0; k < MAX_LEVEL; k++)
//{
//BUZZERn[k] = sequence[k];
//}
}
void wrong_sequence()
{
for (int i = 0; i < 3; i++)
{
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
digitalWrite(5, HIGH);
for(int k=0;k<15;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(5);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(5);//wait for 1ms
   }
delay(250);
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
delay(250);
}
show_sequence();
level = 1;
velocity = 500;
error_spot=-1;
}

void right_sequence()
{
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
delay(250);

digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
digitalWrite(5, HIGH);
for(int k=1;k<1000;k++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(abs(k*sin(1/k)));//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(abs(k*sin(1/k)));//wait for 1ms
   }
delay(500);
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
delay(500);

if (level < MAX_LEVEL);
level++;

velocity += vchange; //increase difficulty
}