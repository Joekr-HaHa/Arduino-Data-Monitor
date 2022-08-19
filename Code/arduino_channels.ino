#include <Wire.h>
 #include <Adafruit_RGBLCDShield.h>
 #include <utility/Adafruit_MCP23017.h>
 #include <EEPROM.h>

 Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
 #define UP_CHAR 0
 #define DOWN_CHAR 1
byte name0x0[] = { B00100, B01110, B11111, B00100, B00100, B00100, B00100, B00100 };
byte name0x1[] = { B00100, B00100, B00100, B00100, B00100, B11111, B01110, B00100 };
int scrollPos=0;
int scrollPos1=0;

 struct Channel_dict{
  char channel;
  String text="DEFAULT";
  int value=0;
  int maximum=255;
  int minimum=0;
 };

 struct Avg_return{
  byte avgArray[40];
 };

/*EEPROM PROOF OF CONCEPT
  struct Channel_dict channel;
Channel_dict channels[26]={};*/
 //make a function to look up alphabet's index
 //then can do channels_maxmin(alpha_index('A'),56);, etc.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
lcd.begin(16, 2);
 lcd.setBacklight(5);
 lcd.clear();
 lcd.createChar(UP_CHAR,name0x0);
  lcd.createChar(DOWN_CHAR,name0x1);
  /*EEPROM PROOF OF CONCEPT
    char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

for(int i=0;i<=26;i++){
  channels[i].channel=alpha[i];
  channels[i].value=eeprom_read_value(i);
  if(eeprom_read_text(i).substring(1,2)!=NULL){
    Serial.println(eeprom_read_text(i));
  channels[i].text=eeprom_read_text(i);}
  else{
    channels[i].text="DEFAULT";
  }
  channels[i].maximum=eeprom_read_max(i);
  channels[i].minimum=eeprom_read_min(i);
}*/
  //eeprom_read(0);
   //for resetting eeprom
   
   for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}
 void update_display(String str) {
 lcd.clear();
 lcd.print(str);
 }
 void update_display_two_line(String str,String str1){
  lcd.clear();
  lcd.print(str);
  lcd.setCursor(0,1);
  lcd.print(str1);
 }
#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else // __ARM__
extern char *__brkval;
#endif // __arm__
int freeMemory() {
char top;
#ifdef __arm__
return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
return &top - __brkval;
#else // __arm__
return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}


/*char read_eeprom_channel(int addr){
  addr=addr*151;
  if(EEPROM.read
}*/
/*EEPROM PROOF OF CONCEPT
void eeprom_read(int addr){
  addr*=62;
  char charArray[15];
   Serial.println(char(EEPROM.read(addr)));
   byte highByte=EEPROM.read(addr+=1);
  byte lowByte=EEPROM.read(addr+=1);
  int value=convert_byte_to_int(highByte,lowByte);
  Serial.println(value);
   for(int i=0;i<15;i++){
    charArray[i]=EEPROM.read(addr+=1);
   }
   //Serial.println(char(charArray[0]));
   Serial.println(String(charArray));
   Serial.println(addr);
   highByte=EEPROM.read(addr+=1);
   lowByte=EEPROM.read(addr+=1);
   value=convert_byte_to_int(highByte,lowByte);
   Serial.println(value);
   highByte=EEPROM.read(addr+=1);
   lowByte=EEPROM.read(addr+=1);
   value=convert_byte_to_int(highByte,lowByte);
   Serial.println(value);
   Serial.print("addr count: ");
   Serial.println(addr);
   for(int i=0;i<=64;i++){
    if(EEPROM.read(addr+1)!=0){
    highByte=EEPROM.read(addr+=1);
    lowByte=EEPROM.read(addr+=1);
    value=convert_byte_to_int(highByte,lowByte);
    Serial.println(value);}
    else{
      addr+=2;
    }
   }
  
}

int eeprom_read_value(int addr){
  addr*=62;
  char charArray[15];
   byte highByte=EEPROM.read(addr+=1);
  byte lowByte=EEPROM.read(addr+=1);
  int value=convert_byte_to_int(highByte,lowByte);
  return value;
  
}

String eeprom_read_text(int addr){
  addr*=62;
  char charArray[15];
  addr+=2;
  for(int i=0;i<15;i++){
    charArray[i]=EEPROM.read(addr+=1);
   }
   //Serial.println(char(charArray[0]));
   return String(charArray);
  
}

int eeprom_read_max(int addr){
  addr*=62;
  addr+=17;
   int highByte=EEPROM.read(addr+=1);
   int lowByte=EEPROM.read(addr+=1);
   int value=convert_byte_to_int(highByte,lowByte);
   return value;
  
}

int eeprom_read_min(int addr){
  addr*=62;
  addr+=19;
   int highByte=EEPROM.read(addr+=1);
   int lowByte=EEPROM.read(addr+=1);
   int value=convert_byte_to_int(highByte,lowByte);
   return value;
  
}*/
Avg_return read_eeprom_avg_bytes(int addr){//TODO the issue is here, writing is fine
  addr=addr*62;
  addr+=22;//22
  Avg_return a;
  //byte avgArray[40];
  for(int i=0;i<40;i++){
    //if(i%2!=0){
      //Serial.print("Location: ");
      //Serial.println(addr+i);
      //byte highByte=EEPROM.read(addr+i);
      //byte lowByte=EEPROM.read(addr+i+1);
      //a.avgArray[i]=highByte;
      a.avgArray[i]=EEPROM.read(addr+i);
      //Serial.print("High byte: ");
      //Serial.println(highByte);
      //Serial.print("Low byte: ");
      //Serial.println(lowByte);
      /*Serial.println("IN RETURN AVERAGE BYTES");
      Serial.println(a.avgArray[i]);
      Serial.println("-----------------------");*/
  //}
  }
  return a;
}



byte return_high_byte(int num){
  //Serial.print("num: ");
  //Serial.println(num);
   //byte highByte = ((num >> 8) & 0xFF);
   byte highByte=highByte(num);
   //Serial.print("calc: ");
   //Serial.println(highByte);
   return highByte;
}


byte return_low_byte(int num){
//byte lowByte = ((num >> 0) & 0xFF);
byte lowByte=lowByte(num);
return lowByte;}


int convert_byte_to_int(byte highByte,byte lowByte){
  byte newHighByte=((highByte<<8)&0xFF);
  byte newLowByte=((lowByte<<0)&0xFF);
  //Serial.print("high: ");
  //Serial.println(newHighByte);
  //Serial.print("high + low: ");
  //Serial.println(newHighByte+newLowByte);
  return (newHighByte+newLowByte);
}

int return_first_empty(Avg_return a){
  int numArray[64];
  for(int i=0;i<40;i++){
    if(i%2==0){
    byte highByte=a.avgArray[i];
    byte lowByte=a.avgArray[i+1];
    int num=convert_byte_to_int(highByte,lowByte);
    /*Serial.println(i);
    Serial.println("CONVERTED NUM");
    Serial.println(highByte);
    Serial.println(lowByte);
    Serial.println(num);
    Serial.println("-------------");*/
    numArray[i/2]=num;
    }
  }
  for(int i=0;i<64;i++){
    if(numArray[i]<1){//==0
      return i;
    }
  }
  return 0;
}

void write_my_eeprom_single(Channel_dict channels[],int i){
  int j=i;
  j=j*62;
  j-=1;
  char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  //for(int i=0;i<=26;i++){
    //Serial.println((sizeof(channels)/sizeof(Channel_dict)));
    char channel=channels[i].channel;
    /*if(channel==NULL){
      channel=alpha[i];
      //continue;
    }*/
    int value=channels[i].value;
    String text=channels[i].text;
    int max=channels[i].maximum;
    int min=channels[i].minimum;
    EEPROM.update(j+=1,channel);
    String valString=String(value);
    EEPROM.update(j+=1,return_high_byte(value));
    EEPROM.update(j+=1,return_low_byte(value));
    /*if(length_of(text)<15){
      EEPROM.update(j+=1,length_of(text));
    }
    else{
    EEPROM.update(j+=1,char(1));
    EEPROM.update(j+=1,char(5));}
    */
    for(int k=0;k<15;k++){
      EEPROM.update(j+=1,char(text[k]));
    }
    EEPROM.update(j+=1,return_high_byte(max));
    EEPROM.update(j+=1,return_low_byte(max));
    EEPROM.update(j+=1,return_high_byte(min));
    EEPROM.update(j+=1,return_low_byte(min));
    //Serial.print("addr count write: ");
    //Serial.println(j);
    //byte pastNums[40];
    Avg_return pastNums;
    pastNums=read_eeprom_avg_bytes(i);
    /*Serial.println("PAST NUMS");
    for(int k=0;k<40;k++){
      Serial.println("OUTPUT OF READ AVG");
      Serial.println(pastNums.avgArray[k]);
      Serial.println("-------------------");
    }
    Serial.println("----------------");*/
    int pos=return_first_empty(pastNums);
    pos*=2;
    /*Serial.print("POSITION: ");
    Serial.println(pos);
    Serial.println(value);*/
    //if(pastNums.avgArray[pos]<1&&pastNums.avgArray[pos+1]<1){
    pastNums.avgArray[pos]=return_high_byte(value);
    pastNums.avgArray[pos+1]=return_low_byte(value);//}
    /*for(int k=0;k<40;k++){
      Serial.println("CHANGES MADE");
      Serial.println(pastNums.avgArray[k]);
      Serial.println("-------------------");
    }*/
    /*for(int k=0;k<40;k++){
      //if(k%2!=0){
        //Serial.println(k);
      //has 0, 32, then want it after
      if((pastNums.avgArray[k]<1)&&(pastNums.avgArray[k+1]<1)){
        /*Serial.println("Writing value");
        Serial.println(value);
        Serial.println(return_high_byte(value));
        Serial.println(return_low_byte(value));
        byte highByte=pastNums.avgArray[k];
        byte lowByte=pastNums.avgArray[k+1];
        int num=convert_byte_to_int(highByte,lowByte);
        Serial.print("num: ");
        Serial.println(num);
        Serial.println(highByte);
        Serial.println(lowByte);*/
         /*pastNums.avgArray[k]=return_high_byte(value);
         pastNums.avgArray[k+1]=return_low_byte(value);
        break;
      }
      }*/
    //}
    
    for(int k=0;k<40;k++){
      //Serial.print("k: ");
      //Serial.println(pastNums.avgArray[k]);
      EEPROM.update(j+=1,pastNums.avgArray[k]);
      //Serial.print("location: ");
      //Serial.println(j);
    }
    //Serial.print("j: ");
    //Serial.println(j);
    //write to empty spaces at end of eeprom the averages.
//    Serial.println("writes :"+String(writes));
    /*
    String maxString=String(max);
    for(int k=0;k<2;k++){
      EEPROM.update(j+=1,(char)maxString[k]);
    }
    String minString=String(min);
    for(int k=0;k<2;k++){
      EEPROM.update(j+=1,(char)minString[k]);
    }*/
 // }
  
}




int count_right_rule(Channel_dict channels[]){
  int j=0;
  for(int i=0;i<=26;i++){
    if(channels[i].value>channels[i].maximum){
      j+=1;
    }
  }
  return j;
}
Channel_dict * make_array_right_rule(Channel_dict channels[],int count,int pointer){
  Channel_dict newChannels[count];
  //malloc(newChannels);
  int j=0;
  for(int i=0;i<=26;i++){
    if(channels[i].value>channels[i].maximum){
      newChannels[j]=channels[i];
      j+=1;
    }
  }
  //return newChannels;
  if(count!=0){
  lcd_channels_len(newChannels,count,pointer);}
  else{
    return;
  }
}

int count_left_rule(Channel_dict channels[]){
  int j=0;
  for(int i=0;i<=26;i++){
    if(channels[i].value<channels[i].minimum){
      j+=1;
    }
  }
  return j;
}
Channel_dict * make_array_left_rule(Channel_dict channels[],int count,int pointer){
  Channel_dict newChannels[count];
  //malloc(newChannels);
  int j=0;
  for(int i=0;i<=26;i++){
    if(channels[i].value<channels[i].minimum){
      newChannels[j]=channels[i];
      j+=1;
    }
  }
  //return newChannels;
  if(count!=0){
  lcd_channels_len(newChannels,count,pointer);}
  else{
    return;
  }
}
/*void scroll(String displayText1,int row){//change to account for two simultaneously on screen
  if (displayText1.length()>6){
  for(int x=0;x<displayText1.length();x++){
    lcd.setCursor(10,row);
    //return partial string between x and the end of the string and change every half second
    lcd.print("                    ");
    lcd.setCursor(10,row);
    lcd.print(partial_string(displayText1,x,displayText1.length()));
  }}
}*/

void scroll(String displayText1,int row){//change to account for two simultaneously on screen
  /*if(scrollPos>displayText1.length()){
    scrollPos=0;
  }*/
  if (displayText1.length()>6){
    lcd.setCursor(10,row);
    //return partial string between x and the end of the string and change every half second
    lcd.print("                    ");
    lcd.setCursor(10,row);
    if(row==0){
    //lcd.print(partial_string(displayText1,scrollPos,displayText1.length()-1));
    lcd.print(displayText1.substring(scrollPos));
    scrollPos+=1;}
    else{
      //lcd.print(partial_string(displayText1,scrollPos-1,displayText1.length()-1))
      lcd.print(displayText1.substring(scrollPos1));
      scrollPos1+=1;
    }
  }
  else{
  lcd.setCursor(10,row);
  lcd.print(displayText1);}
}

void endScroll(String displayText, int row){
  lcd.setCursor(10,row);
  lcd.print(displayText);
}



int return_avg(int addr){
  addr=addr*62;
  addr+=22;//23
  int total=0;
  int count=0;
  //Serial.println("VALUES");
  //byte avgArray[64];
  for(int i=0;i<40;i+=2){
      //Serial.print("Location: ");
      //Serial.println(addr+i);
      byte highByte=EEPROM.read(addr+i);
      byte lowByte=EEPROM.read(addr+i+1);
      int value=convert_byte_to_int(highByte,lowByte);
      //Serial.println(value);
      //Serial.println("LOC: ");
      //Serial.println(addr+i);
      if(value!=0){
      total+=value;
      count+=1;
    }
  }
  //Serial.println("---------------");
  /*int avg=(total/count);
  Serial.print("This is: ");
  Serial.println(total);
  Serial.println(count);
  Serial.println((total/count));
  Serial.println(avg);*/

  //tried other fixes but just concluded dividing by 0 does weird stuff
  if(count!=0){
    //Serial.println(total);
    //Serial.println(count);
  return total/count;}
  else{
    return 0;
  }
}

void lcd_channels_len(Channel_dict channels[],int len,int pointer){
  //Serial.println("BROOOOOOOOO");
  //Serial.print(channels[0].value);
  //Serial.println(len);
  len-=1;
  //Serial.print(channels[1].value);
  /*for(int i=0;i<len;i++){
    Serial.print(channels[i].channel);
    Serial.print(channels[i].value);
    Serial.println(channels[i].text);
  }*/
  bool downPoint=false;
  bool upPoint=false;
  //Serial.println(pointer+1);
  //Serial.println(len);
  if(pointer+1!=(len)&&pointer+1<len){
    downPoint=true;
  };
  if(pointer!=0){
    upPoint=true;
  }
  lcd.clear();
  lcd.setCursor(0,0);//0,0
  if(upPoint==true){
    //lcd.createChar(0,name0x0);
    //lcd.setCursor(0,0);
    //Serial.println("in up char");
    lcd.print(char(UP_CHAR));
  }
  else{
    lcd.print(" ");
  }
  lcd.print(channels[pointer].channel);
  //lcd.print(" ");
  lcd.print(channels[pointer].value);
  lcd.print(" ");
  //lcd.print("AVG ");
  lcd.print(return_avg(pointer));
  String displayText0=(channels[pointer].text);
  scroll(displayText0,0);
  displayText0.trim();
  //if(len>0){
  lcd.print(displayText0);
  lcd.setCursor(0,1);
  if(downPoint==true){
    //lcd.createChar(1,name0x1);
    //lcd.setCursor(0,1)
    lcd.print(char(DOWN_CHAR));
  }
  else{
    lcd.print(" ");
  }
  if(len!=0){
    Serial.println("it's over anakin, I have the high ground");
  lcd.print(channels[pointer+1].channel);
  //lcd.print(" ");
  lcd.print(channels[pointer+1].value);
  lcd.print(" ");
  //lcd.print("AVG ");
  lcd.print(return_avg(pointer+1));
  //0,11; then loop through string
  String displayText1=(channels[pointer+1].text);
  scroll(displayText1,1);
  displayText1.trim();
  lcd.setCursor(10,1);
  lcd.print(displayText1);}}
  //free(channels);
  
//}
  

/*
void lcd_channels_with_null(Channel_dict channels[], int pointer){
  //copy lcd channels but any time a null field is encountered, skip it
  bool downPoint=false;
  bool upPoint=false;
  int cursorPos=0;
  char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  for(int i=0;i<=26;i++){
    if(channels[i].maximum>cv){
      if(cursorPos==0){
        cursorPos=1;
      }
      else{
        cursorPos=0;
      }
      lcd.setCursor(0,cursorPos);
      channels[i].channel=alpha[i];
       lcd.print(channels[pointer].channel);
        //lcd.print(" ");
        lcd.print(channels[pointer].value);
        lcd.print(" ");
        String displayText0=(channels[pointer].text);
        displayText0.trim();
        lcd.print(displayText0);
    }
  }
  
  return
}
*/
void lcd_channels(Channel_dict channels[],int pointer){
  bool downPoint=false;
  char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  bool upPoint=false;
  //change this part to not change channel element and instead just print the letter
  /*if(channels[pointer].channel==NULL){
    channels[pointer].channel=alpha[pointer];
  }
  if(channels[pointer+1].channel==NULL){
    channels[pointer+1].channel=alpha[pointer+1];
  }*/
  if(pointer+1!=25){
    downPoint=true;
  };
  if(pointer!=0){
    upPoint=true;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  if(upPoint==true){
    //lcd.createChar(0,name0x0);
    //lcd.setCursor(0,0);
    //Serial.println("in up char");
    lcd.print(char(UP_CHAR));
  }
  else{
    lcd.print(" ");
  }
  //lcd.print(channels[pointer].channel);
  lcd.print(alpha[pointer]);
  //lcd.print(" ");
  //lcd.print(channels[pointer].value);
  right_align(channels,channels[pointer].value);
  lcd.print(" ");
  //lcd.print("AVG ");
  lcd.print(return_avg(pointer));
  String displayText0=(channels[pointer].text);
  displayText0.trim();
  scroll(displayText0,0);
  //lcd.print(displayText0);
  lcd.setCursor(0,1);
  if(downPoint==true){
    //lcd.createChar(1,name0x1);
    //lcd.setCursor(0,1)
    lcd.print(char(DOWN_CHAR));
  }
  else{
    lcd.print(" ");
  }
  //lcd.print(channels[pointer+1].channel);
  lcd.print(alpha[pointer+1]);
  //lcd.print(" ");
  //lcd.print(channels[pointer+1].value);
  right_align(channels,channels[pointer+1].value);
  lcd.print(" ");
  //lcd.print("AVG ");
  lcd.print(return_avg(pointer+1));
  String displayText1=(channels[pointer+1].text);
  scroll(displayText1,1);
  displayText1.trim();
  //lcd.print(displayText1);
  //lcd.print("UR MOM");
  
}

void right_align(Channel_dict channels[],int val){
  Serial.println(val);
  if(val<10){
    lcd.print("  ");
    lcd.print(val);
  }
  else if(val<100 && val>=10){
    lcd.print(" ");
    lcd.print(val);
  }
  else if(val<1000 && val>=100){
    lcd.print(val);
  }
  else{
    lcd.print("ERR");
  }
}
int convert_to_int(String str,int lb, int ub){
  int x;
  int j=0;
  int num1=0;
  int arrLen=ub-lb;
  int intArray[arrLen];
  for(int i=lb;i<ub;i++){
    x=(char)str[i]-(char)48;
    //x=stoi(str[i]);
    intArray[j]=x;
    j+=1;
  }
  for(int k=0;k<arrLen;k++){
    num1+=(intArray[k]*((int)(pow(10,(arrLen-k-1)))));
  }
  return num1;
}

int return_alpha(Channel_dict channels[],char desired){
  char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  for(int i=0;i<=26;i++){
    if((char)alpha[i]==(char)desired){
      channels[i].channel=desired;
      //Serial.println(channels[i].channel);
      return i;
    }
  }
  //Serial.println("Dumbass");
  //Serial.println(desired);
  return 0;
}

void min_max_light(Channel_dict channels[],int pos){
  int val=channels[pos].value;
  bool over_min=false;
  bool over_max=false;
  if(val>=0&&val<=255){
      if(val>channels[pos].maximum){
        over_max=true;
      }
      if(val<channels[pos].maximum){
        over_max=false;
      }
      if(val<channels[pos].minimum){
        over_min=true;
      }
      if(val>channels[pos].minimum){
        over_min=false;
      }
      //Serial.println("Over Max"+(String)over_max);
      //Serial.println("Over Min"+(String)over_min);
      if(over_min&&!over_max){
        lcd.setBacklight(2);
      }
      else if(over_max&&!over_min){
        lcd.setBacklight(1);
      }
      if(!over_max &&!over_min){
        lcd.setBacklight(7);
      }
      else if(over_min && over_max){
      lcd.setBacklight(3);
    }
}
}

void set_alpha(Channel_dict channels[],int pos){
  char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  channels[pos].channel=alpha[pos];
}
struct Channel_dict channel;
Channel_dict channels[26]={};
/*char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
for(int i=0;i<=26;i++){
   channels[i].channel=alpha[i];}*/

enum state_e {SYNCHRONISATION, WAITING_PRESS,MAIN,WAITING_RELEASE};
int val=0;

//enum state_e state=SYNCHRONISATION;
void loop() {
  // put your main code here, to run repeatedly:
  //for(int i=0;i<=26;i++){
   //channels[i].channel=alpha[i];};
 static enum state_e state = SYNCHRONISATION;
 static int updown; // Store which button was pressed
 static long press_time; // Store the time the button was pressed
 static int last_b = 0; // Store for the last button press
 static int pointer = 0;
 static bool refine_right=false;
 static bool refine_left=false;
 //static int val=0;
 static bool over_min=false;
 static bool over_max=false;
 static long scroll_time;//stores time between scrolls
 static long scroll_time1;//stores time between scrolls
 switch(state){
case MAIN:
{
  //lcd.print("Waiting input");
    if(!Serial.available()){
    state=WAITING_PRESS;};
      Serial.print("Recieved input");
      //Serial.println(freeMemory());
      String x = Serial.readString();
      //Serial.println(x);
      //lcd.clear();
      //lcd.setCursor(0,1);
      //lcd.print((char)x[0]);
      int pos=return_alpha(channels,x[1]);
      if((char)x[0]=='C' or (char)x[0]=='V' or (char)x[0]=='X' or (char)x[0]=='N'){
        set_alpha(channels,pos);
      }
      if((char)x[0]==(char)'C'){
        //follow by channel number and description
        //String textData=partial_string(x,2,x.length());
        String textData=x.substring(2,17);//15 characters long
        textData.trim();
        //lcd.clear();
        //lcd.setCursor(0,1);
        //lcd.print(textData);
        channels[pos].text=textData;
        pointer=pos;
        lcd_channels(channels,pointer);
        //lcd.setCursor(0,0);
        //lcd.print(channels[pos].text);
      }
     else if((char)x[0]==(char)'V'){
        //follow by channel number then a value between 0 and 255
      //int val=(int)partial_string(x,2,x.length());
      //int val= int atoi((const char * str)
      //int val=convert_to_int(x,2,x.length());
      //String textData=partial_string(x,2,x.length());
      String textData=x.substring(2);
      int val=textData.toInt();
      //lcd.clear();
      //lcd.setBacklight(2);
      //lcd.print(val);
      if(val>=0&&val<=255){
      if(val>channels[pos].maximum){
        over_max=true;
      }
      if(val<channels[pos].maximum){
        over_max=false;
      }
      if(val<channels[pos].minimum){
        over_min=true;
      }
      if(val>channels[pos].minimum){
        over_min=false;
      }
      //Serial.println("Over Max"+(String)over_max);
      //Serial.println("Over Min"+(String)over_min);
      if(over_min&&!over_max){
        lcd.setBacklight(2);
      }
      else if(over_max&&!over_min){
        lcd.setBacklight(1);
      }
      if(!over_max &&!over_min){
        lcd.setBacklight(7);
      }
      else if(over_min && over_max){
      lcd.setBacklight(3);
    }
      //delay(500);
      channels[pos].value=val;
      //Serial.println(val);
      //delay(500);
      write_my_eeprom_single(channels,pos);
      pointer=pos;
      lcd_channels(channels,pointer);
      //eeprom_read(0);
      /*for(int y=0;y<=64;y++){
        Serial.println(avgArray[y]);
      }*/}
      //lcd.clear();
      //lcd.print(channels[pos].value);
      
      }
      else if((char)x[0]=='X'){
        //maximum value for channel; channel number then value; 255 default
        //int check_max=convert_to_int(x,2,x.length());
        //int check_max=(partial_string(x,2,x.length()).toInt());
        int check_max=(x.substring(2)).toInt();
        if(check_max>=channels[pos].minimum&&check_max>=0&&check_max<=255){
          channels[pos].maximum=check_max;
          min_max_light(channels,pos);
        }
        else{
          Serial.print("Maximum cannot be smaller than minimum of:");
          Serial.println(channels[pos].minimum);
        }
      
      }
      else if((char)x[0]=='N'){
        //minimum value for channel; channel number then value; 0 default
        //int check_min=(partial_string(x,2,x.length()).toInt());
        int check_min=(x.substring(2)).toInt();
        //int check_min=convert_to_int(x,2,x.length());
       if(check_min<=channels[pos].maximum&&check_min>=0&&check_min<=255){
          channels[pos].minimum=check_min;
          min_max_light(channels,pos);
        }
        else{
          Serial.print("Minimum cannot be bigger than maximum of:");
          Serial.println(channels[pos].maximum);
        }
      }
      else if(x=="BUTTON"){
        state=WAITING_PRESS;
      }
      else if(x=="QUIT"){
        break;
      }
    
    //state=WAITING_PRESS;
    Serial.print("Awaiting Input\n");
    }
    break;

case SYNCHRONISATION:{
    if(!Serial.available()){
      delay(1000);
      Serial.print("Q");
      }
    String x=Serial.readString();
    if(x=="X"){
      Serial.println("\nUDCHARS, FREERAM, HCI, RECENT, NAMES, SCROLL");
      lcd.setBacklight(7);
      lcd_channels(channels,0);
      state=MAIN;
     }}
     break;

case WAITING_RELEASE:{
 if(millis() - press_time>=250){
  press_time=millis();
  if(updown==BUTTON_UP){
    /*if(pointer!=0){
    pointer-=1;}
    lcd_channels(channels,pointer);*/
    if(pointer!=0){
 pointer-=1;}
 if(refine_right==true){
  int len=count_right_rule(channels);
  make_array_right_rule(channels,len,pointer);
 }
 else if(refine_left==true){
  int len=count_left_rule(channels);
  make_array_left_rule(channels,len,pointer);
 }
 else{
 lcd_channels(channels,pointer);}
  }
  if(updown==BUTTON_DOWN){
    /*if(pointer+1!=25){
    pointer+=1;}
    lcd_channels(channels,pointer);*/
    if(refine_right){
  int len=count_right_rule(channels);
  if(pointer!=(len-1)){//pointer+1 instead of pointer
  pointer+=1;
 }
  make_array_right_rule(channels,len,pointer);
 }
 else if(refine_left){
  int len=count_left_rule(channels);
  if(pointer+1!=(len-1)){
  pointer+=1;
 }
  make_array_left_rule(channels,len,pointer);
 }
 else{
  if(pointer+1!=25){
  pointer+=1;
 }
 lcd_channels(channels,pointer);}
  }
  if(updown==BUTTON_SELECT){;
 // update_display_two_line("F129714",EEPROM.freeMemory());
 //update_display("F129714");
 lcd.setBacklight(5);
 update_display_two_line("F129714",String(freeMemory()));}
  //update_display("down");
 }else {
 int b = lcd.readButtons();
 // We are looking for buttons that are not pressed
 // now and were pressed last time.
 // The logic below is this. ~ means not.
 // so "NOT now AND last_time"
 int released = ~b & last_b;
 last_b = b; // Save
 // Mask off the bit we are interested in and if
 // it's been released then change state
 if (released & updown) {
  if(updown==BUTTON_SELECT){
  lcd_channels(channels,pointer);}
  //Serial.println("waiting press");
  lcd.setBacklight(7);
 state = MAIN;//WAITING_PRESS
 }
 }}
 break;
case WAITING_PRESS:{
  if(!(refine_left||refine_right)){//to factor in HCI displaying different channels
    Serial.println(refine_right);
  if(((millis()-scroll_time>=500)&&scrollPos!=0)||((millis()-scroll_time>=2000)&&scrollPos==0)){//or statement for scrollPos==0 gives a 2 second delay before scrolling again
    if(scrollPos==0){//so it doesn't flash/ re-output the text after the 2 sec delay
      scrollPos=1;
    }
  if(scrollPos<channels[pointer].text.length()){
    scroll_time=millis();
  scroll(channels[pointer].text,0);}
  else{
    endScroll(channels[pointer].text,0);
    scrollPos=0;
  }}
  if(((millis()-scroll_time1>=500)&&scrollPos1!=0)||((millis()-scroll_time1>=2000)&&scrollPos1==0)){//or statement for scrollPos==0 gives a 2 second delay before scrolling again
    if(scrollPos1==0){//so it doesn't flash/ re-output the text after the 2 sec delay
      scrollPos1=1;
    }
  if(scrollPos1<channels[pointer+1].text.length()){
    scroll_time1=millis();
  scroll(channels[pointer+1].text,1);}
  else{
    endScroll(channels[pointer+1].text,1);
    scrollPos1=0;
  }}}
  if(Serial.available()){
    state=MAIN;
  }
 int b = lcd.readButtons();
 // We are looking for buttons that were NOT pressed
 // and are pressed now.
 // Logic is "now AND NOT last_time"
 int pressed = b & ~last_b;
 last_b = b;
 // if either up OR down is pressed
 if (pressed & (BUTTON_UP | BUTTON_DOWN | BUTTON_SELECT |BUTTON_RIGHT|BUTTON_LEFT)) {
  scrollPos=0;
 // now just checking for up
 if (pressed & (BUTTON_UP)) {
  if(pointer!=0){
 pointer-=1;}
 if(refine_right==true){
  int len=count_right_rule(channels);
  make_array_right_rule(channels,len,pointer);
 }
 else if(refine_left==true){
  int len=count_left_rule(channels);
  make_array_left_rule(channels,len,pointer);
 }
 else{
 lcd_channels(channels,pointer);}
 }
 /*if(pressed&BUTTON_SELECT){
  //write_my_eeprom(channels);
  //read_my_eeprom(2);
  update_display("Student ID");
 }*/
 if(pressed&BUTTON_LEFT){
  //update_display("left");
  refine_left=!refine_left;
  //Serial.print("refine left");
  //Serial.println(refine_left);
  if(refine_left==true){
    pointer=0;
    int len=count_left_rule(channels);
    if(len==0){
      update_display("No Values");
      //delay(50);
      //refine_left=false;
    }
     make_array_left_rule(channels,len,pointer);
    //lcd_channels_len(newChannels,len,pointer);
  }
  else{
    lcd.clear();
    lcd_channels(channels,pointer);
  }
  }
 if(pressed&BUTTON_RIGHT){
  //update_display("right");
  refine_right=not refine_right;
  if(refine_right==true){
    pointer=0;
    int len=count_right_rule(channels);
    if(len==0){
      update_display("No Values");
      //delay(50);
      //refine_right=false;
    }
     make_array_right_rule(channels,len,pointer);
    //lcd_channels_len(newChannels,len,pointer);
  }
  else{
    lcd_channels(channels,pointer);
  }
  }
 if(pressed&BUTTON_DOWN) {
 if(refine_right){
  int len=count_right_rule(channels);
  if(pointer+1<(len-1)){
  pointer+=1;
 }
  make_array_right_rule(channels,len,pointer);
  //Serial.println("HELLLLOOOOO");
  //lcd_channels_len(newChannels,len,pointer);
 }
 else if(refine_left){
  int len=count_left_rule(channels);
  if(pointer+1<(len-1)){
  pointer+=1;
 }
  make_array_left_rule(channels,len,pointer);
  //Serial.println("HELLLLOOOOO");
  //lcd_channels_len(newChannels,len,pointer);
 }
 else{
  if(pointer+1!=25){
  pointer+=1;
 }
 lcd_channels(channels,pointer);}
 }
 updown = pressed;
 press_time = millis();
 state = WAITING_RELEASE;
 }}
 break;
}}
  
