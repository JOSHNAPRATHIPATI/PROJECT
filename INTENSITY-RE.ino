#define LDR_PIN A0
#define THRESHOLD 800
#define PERIOD 200

bool previous_state = true;
bool current_state = true;

void setup() {
  pinMode(LDR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  current_state = get_ldr();

  if (!current_state && previous_state) {
    char moisture_char = get_byte();  // Receive moisture level
    int moisture_value = map(moisture_char, 0, 255, 0, 1023);  // Map char to moisture value
    Serial.print("Moisture level: ");
    Serial.print(moisture_value);
    Serial.println(" (0-1023)");

    char received_byte = get_byte();
    Serial.print("Received byte: ");
    Serial.println(received_byte);
  }

  previous_state = current_state;
}

bool get_ldr() {
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD;
}

char get_byte() {
  char ret = 0;
  delay(1.5 * PERIOD);
  for (int i = 0; i < 8; i++) {
    ret |= (get_ldr() << i);
    delay(PERIOD);
  }
  return ret;
}
