#define COUNT_ANALOG_PINS 6
#define COUNT_DIGITAL_PINS 14
#define COUNT_PINS 20
#define SERIAL_PORT_SPEED 115200
#define SHIFT_DIGITAL_PINS 2

void send_plotter_data() {
  String s = "";
  for (short i = 0; i < COUNT_ANALOG_PINS; ++i) {
    if (!bitRead(PIND, i + 2)) {
      if (s != "") {
        s += ' ';
      }
      s += 'A';
      s += i;
      s += ':';
      s += analogRead(i);
    }
  }
  if (s != "") {
    Serial.println(s);
    Serial.flush();
  }
}

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);
  for (short i = 2; i < COUNT_PINS; ++i) {
    if (i < COUNT_DIGITAL_PINS) {
      pinMode(i, INPUT_PULLUP);
    } else {
      pinMode(i, INPUT);
    }
  }
  ADCSRA |= (1 << ADPS2);
  ADCSRA &= ~ ((1 << ADPS1) | (1 << ADPS0));
}

void loop() {
  while (1) {;
    send_plotter_data();
  }
}
