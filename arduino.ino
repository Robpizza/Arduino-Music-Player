// 7-segment display pins
int display_a = 12;
int display_b = 13;
int display_c = 7;
int display_d = 8;
int display_e = 9;
int display_f = 11;
int display_g = 10;

// Current song
int display_count = 0;

int music_tempo = 125;
int wholenote = (60000 * 4) / music_tempo;
int divider = 0, noteDuration = 0;

// Current power state decided by the LDR
bool power_state = false;


/*******************************\
|								|
|	MUSIC LOGIC					|
|								|
/*******************************/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int music[4][180] = {
  {NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8, NOTE_F5,2, NOTE_C6,2, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,8, NOTE_C5,8, NOTE_C5,8, NOTE_F5,2, NOTE_C6,2, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,-8, NOTE_C5,16, NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C5,-8, NOTE_C5,16, NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, NOTE_C6,-8, NOTE_G5,16, NOTE_G5,2, REST,8, NOTE_C5,8, NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C6,-8, NOTE_C6,16, NOTE_F6,4, NOTE_DS6,8, NOTE_CS6,4, NOTE_C6,8, NOTE_AS5,4, NOTE_GS5,8, NOTE_G5,4, NOTE_F5,8, NOTE_C6,1},
  {NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16, NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8, NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32, NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8},
  {NOTE_FS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, REST,4, REST,8, NOTE_CS4,8, NOTE_D4,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8, NOTE_E5,-4, NOTE_DS5,8, NOTE_D5,8, REST,8, REST,4, NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_FS4,8, REST,8,NOTE_CS5,8, REST,8, NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_G4,8, NOTE_FS4,8, REST,8, NOTE_E4,8, REST,8, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_DS4,8, NOTE_D4,8}
};

void speaker_init() {
  Serial.println("Init Music");
  pinMode(6, OUTPUT);  
  Serial.println("Init Music Done");
}

void playMusic() {
  if(display_count != 0) {
    int song = display_count - 1;
    
  	int notes = sizeof(music[song]) / sizeof(music[song][0]) / 2;
  	Serial.println(notes);
  	
    for(int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      
      // BUTTONS FOR DISPLAY COUNTER
      if(digitalRead(5) == 1 || digitalRead(4) == 1 || analogRead(A5) < 300)
        break;
      // END BUTTONS
      
      divider = music[song][thisNote + 1];
      if(divider > 0) {
        noteDuration = (wholenote) / divider;
      }else if(divider < 0) {
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;
      }
      
      tone(6, music[song][thisNote], noteDuration * 0.9);
      delay(noteDuration);
      noTone(6);
    }
      
  }
}





/*******************************\
|								|
|	7-SEGMENT DISPLAY LOGIC		|
|								|
/*******************************/
void display_init() {
  Serial.println("Init Display");
  pinMode(display_a, OUTPUT);	 //A
  pinMode(display_b, OUTPUT);  //B
  pinMode(display_c, OUTPUT);  //C
  pinMode(display_d, OUTPUT);  //D
  pinMode(display_e, OUTPUT);  //E
  pinMode(display_f, OUTPUT);  //F
  pinMode(display_g, OUTPUT);  //G
  Serial.println("Init Display Done");
}

void display_show(int digit) {
  //Conditions for displaying segment a
  if(digit!=1 && digit != 4)
  	digitalWrite(display_a,HIGH);

  //Conditions for displaying segment b
  if(digit != 5 && digit != 6)
    digitalWrite(display_b,HIGH);

  //Conditions for displaying segment c
  if(digit !=2)
    digitalWrite(display_c,HIGH);

  //Conditions for displaying segment d
  if(digit != 1 && digit !=4 && digit !=7)
    digitalWrite(display_d,HIGH);

  //Conditions for displaying segment e 
  if(digit == 2 || digit ==6 || digit == 8 || digit==0)
    digitalWrite(display_e,HIGH);

  //Conditions for displaying segment f
  if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
    digitalWrite(display_f,HIGH);
  
  //Conditions for displaying segment g
  if (digit!=0 && digit!=1 && digit !=7)
    digitalWrite(display_g,HIGH);
}

void display_increase() {
  if(display_count == 4)
    display_count = 0;
  else
  	display_count++;
}

void display_decrease() {
  if(display_count == 0)
    display_count = 4;
  else
  	display_count--;
}

void turnOff()
{
  digitalWrite(display_a,LOW);
  digitalWrite(display_b,LOW);
  digitalWrite(display_c,LOW);
  digitalWrite(display_d,LOW);
  digitalWrite(display_e,LOW);
  digitalWrite(display_f,LOW);
  digitalWrite(display_g,LOW);
}






/*******************************\
|								                |
|	ARDUINO LOGIN				          |
|								                |
/*******************************/
void setup()
{
  Serial.begin(9600);
  display_init();
  speaker_init();
  
  // LDR
  pinMode(A5, INPUT);
  
  // Leds
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  // Buttons
  pinMode(5, INPUT);
  pinMode(4, INPUT);
}

void loop()
{
  // Check if the power is one or off
  if(power_state) {  
    
    
    // POWER LED
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    // END POWER LED
    
    
    // BUTTONS FOR DISPLAY COUNTER
    if(digitalRead(5) == 1) {
      display_increase();
      delay(500);
    }
    if(digitalRead(4) == 1) {
      display_decrease();
      delay(500);
    }
    // END BUTTONS
    
    turnOff();
  	display_show(display_count);
    
    playMusic();
  } else {
    // POWER LED
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    // END POWER LED
  }
  
  
  // LDR FOR POWER STATE
  int light = analogRead(A5);
  if(light < 300) {
    power_state = false;
    turnOff();
  }
  else {
    power_state = true;
  }
  // END LDR
}
