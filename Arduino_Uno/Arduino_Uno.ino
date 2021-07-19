#define COUNT_ANALOG_PINS 6
#define COUNT_DIGITAL_PINS 14
#define COUNT_PINS 20
#define SERIAL_PORT_SPEED 115200
#define SHIFT_DIGITAL_PINS 2

word analog_mask;

void update_analog_mask() {
  word new_analog_mask = 0;
  word b = 1;
  for (short i = 0; i < COUNT_ANALOG_PINS; ++i) {
    if (digitalRead(SHIFT_DIGITAL_PINS + i) == LOW) {
      new_analog_mask |= b;
    }
    b <<= 1;
  }
  if (analog_mask != new_analog_mask) {
    analog_mask = new_analog_mask;
  }
}

void send_plotter_data() {
  word b = 1;
  String s = "";
  for (short i = 0; i < COUNT_ANALOG_PINS; ++i) {
    if (analog_mask & b) {
      if (s != "") {
        s += ' ';
      }
      s += 'A';
      s += i;
      s += ':';
      s += analogRead(i);
    }
    b <<= 1;
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
}

void loop() {
  while (1) {
    update_analog_mask();
    send_plotter_data();
  }
}
