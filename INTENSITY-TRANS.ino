#define LED_PIN 9
#define MOISTURE_SENSOR_PIN A0
#define PERIOD 200

const char *string = "This project focuses on improving precision agriculture";
int string_length;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  Serial.begin(9600);
  string_length = strlen(string);  // Correctly initialize the global string_length
}

void loop() {
  int moisture_value = analogRead(MOISTURE_SENSOR_PIN);
  char moisture_char = map(moisture_value, 0, 1023, 0, 255);  // Map moisture value to char
  send_byte(moisture_char);  // Send moisture level

  for (int i = 0; i < string_length; i++) {
    send_byte(string[i]);
  }
  delay(100);
}

void send_byte(char my_byte) {
  digitalWrite(LED_PIN, LOW);
  delay(PERIOD);

  uint8_t bin;

  for (int i = 0; i < 8; i++) {
    int led_state = bitRead(my_byte, i);
    digitalWrite(LED_PIN, led_state != 0);
    delay(PERIOD);
  }

  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
}
