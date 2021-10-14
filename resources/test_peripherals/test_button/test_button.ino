const int pinButton = 0; // D3
int i = 0;

void setup() {
    Serial.begin(115200);
    pinMode(pinButton, INPUT_PULLUP); // Using internal pull up resistor
    
}
void loop(){
    if(digitalRead(pinButton) == LOW){
        Serial.println("Pushed");
        i++;        
        Serial.println(i);
        delay(1000);
    } else{
        Serial.println("Not Pushed");
        i = 0;
    }
}