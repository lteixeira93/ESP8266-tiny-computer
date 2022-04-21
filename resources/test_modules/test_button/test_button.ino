#define PIN_BUTTON 0
int i = 0;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BUTTON, INPUT_PULLUP); // Using internal pull up resistor
    
}
void loop(){
    if(digitalRead(PIN_BUTTON) == LOW){
        Serial.println("Pushed");
        i++;        
        Serial.println(i);
        delay(1000);
    } else{
        Serial.println("Not Pushed");
        i = 0;
        delay(1000);
    }
}