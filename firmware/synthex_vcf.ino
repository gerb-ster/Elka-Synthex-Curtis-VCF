#define LP 0
#define BP1 1
#define BP2 2
#define HP 3

#define MODE_COUNT 4

#define BTN_PORT 0

#define LP_PORT 1
#define BP1_PORT 2
#define BP2_PORT 4
#define HP_PORT 3

int button_state;
int last_button_state = LOW;

unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 50;

int current_mode = 0;

int enable_mode(int mode)
{
  // set all to low
  digitalWrite(LP_PORT, LOW);
  digitalWrite(BP1_PORT, LOW);
  digitalWrite(BP2_PORT, LOW);
  digitalWrite(HP_PORT, LOW);

  // set selected mode
  switch(mode)
  {
    case LP:
      digitalWrite(LP_PORT, HIGH);
    break;

    case BP1:
      digitalWrite(BP1_PORT, HIGH);
    break;

    case BP2:
      digitalWrite(BP2_PORT, HIGH);
    break;

    case HP:
      digitalWrite(HP_PORT, HIGH);
    break;
  }
}

void setup() 
{
  // button port
  pinMode(BTN_PORT, INPUT);

  // output port
  pinMode(LP_PORT, OUTPUT);
  pinMode(BP1_PORT, OUTPUT);
  pinMode(BP2_PORT, OUTPUT);
  pinMode(HP_PORT, OUTPUT);

  // start
  enable_mode(current_mode);
}

void loop() 
{
  int reading = digitalRead(BTN_PORT);

  if (reading != last_button_state)
  {
    last_debounce_time = millis();
  }
  
  if ((millis() - last_debounce_time) > debounce_delay) 
  {
    if (reading != button_state)
    {
      button_state = reading;

      if (button_state == HIGH) 
      {
        current_mode++;

        if(current_mode == MODE_COUNT)
        {
          current_mode = 0;
        }
        
        enable_mode(current_mode);
      }
    }
  }

  last_button_state = reading;
}
