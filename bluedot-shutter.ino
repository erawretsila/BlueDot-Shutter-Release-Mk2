
#include <Arduino.h>
#include "BluetoothSerial.h"
#define SERIAL_BAUDRATE 115200
#define start '\n'
#define Focus_Pin 13
#define Shutter_Pin 12

BluetoothSerial ESP_BT;
uint8_t input;
uint8_t state;
char InitDisp[]={"4,#0000ffff,0,1,1,1,3\n"};
char FocusLocked[]={"5,#ffff00ff,0,1,1,0,0\n"};
char FocusUnlocked[]={"5,#0000ffff,0,1,1,0,0\n"};
char ShutterPressed[]={"5,#00ff00ff,0,1,1,0,1\n"};
char ShutterLocked[]={"5,#ff0000ff,0,1,1,0,1\n"};

char readchar;
char message[256]= "";
bool shutter = false;
bool focus = false;
bool lock = false;
int i;
void setup() {
  pinMode(Shutter_Pin,OUTPUT);
  pinMode(Focus_Pin,OUTPUT);
  digitalWrite(Focus_Pin,HIGH);
  digitalWrite(Shutter_Pin,HIGH);
  // Init serial port and clean garbage
  Serial.begin(SERIAL_BAUDRATE);
  ESP_BT.register_callback(callback);
  if (!ESP_BT.begin("ESP32-shutter release mk2")){;
    Serial.println("ready to pair");
  } else {
    Serial.println("Bluetooth Initialised");
    
  }
  state=start;
  while(not ESP_BT.available()){
    ;
    //wait for Bluedot
  }
}


void loop() {
//  int i=0;
  if(ESP_BT.available()){
    input=ESP_BT.read();
    message [i] = input;
    i++;
    if (i>255){
      Serial.println("Buffer overflow");
      i=0;
      message[0]=0;
      return;
    }
//    Serial.write(input);
    if (input=='\n'){    //message terminator
      message[i]=0;      
      Serial.print(message); //print full message
      Serial.println(message[4]);
      switch (message[4]){
        case '0': //focus button
          Focus(message[0]);
          break;
        case '1': // shutter button
          Fire(message[0]);
          break;
        case '2': // releasse button
          Release(message[0]);
      }
      message[0]=0;
      i=0;
      
      Serial.print("Focus :-");
      Serial.print(focus);
      Serial.print(" Shutter :- ");
      Serial.println(shutter);
      digitalWrite(Focus_Pin,focus);
      digitalWrite(Shutter_Pin,shutter);
      delay(250);
    }
  } 
}
void callback(esp_spp_cb_event_t event,esp_spp_cb_param_t *param){
  switch (event){
    case ESP_SPP_SRV_OPEN_EVT:
      Serial.println("App Acctive");
      ESP_BT.print(InitDisp);
      break;
    case ESP_SPP_CLOSE_EVT:
      Serial.println("Connection Lost");
      break;
    default:
    ;
//      Serial.print("Event ");
//      Serial.println(event,HEX);
          
  }
}

void Focus(char state) {
        Serial.print(focus);
        if (state=='1'){ //only react to press
        focus=!focus;
        Serial.println("-Focus Locked");
        if (focus){
          ESP_BT.print(FocusLocked);
        } else {
          ESP_BT.print(FocusUnlocked);
          
        }
        }

}

void Fire(char state){
        switch (state){  //b
          case '2': //lock to be defined
            lock=true;
            shutter=true; //incase initial fire message gets missed/ommited
            focus=false;
            ESP_BT.print(ShutterLocked);

           ESP_BT.print(FocusUnlocked);
            break; 
          case '1':
            shutter=true;
            focus=false;
            ESP_BT.print(ShutterPressed);
            ESP_BT.print(FocusUnlocked);
            Serial.println("Shutter Pressed");
//            delay(250);
            break;
            
          case '0': 
            Serial.println("Shutter Released");
            if (!lock){
              focus=false;
              shutter=false;
              ESP_BT.print(InitDisp);
 //             delay(250);
            }       
//        digitalWrite(Shutter_Pin,HIGH);
        }
}

void Release(char state){
        Serial.println("Release");
        focus=false;
        shutter=false;
        lock=false;
        ESP_BT.print(InitDisp);

}
