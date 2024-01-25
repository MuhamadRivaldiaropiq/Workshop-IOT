int M,sensor_analog
const int sensor_pin =34;
void setup() {
  serial.begin(115200);
  delay(2000);
  serial.print("workshop Monitoring tanaman SMKN 7 BALEENDAH");
}

void loop() {
  sensor_analog = analogRead(sensor_pin);
  M = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  if (isnan(M)) {
    serial.println("sensor tidak terbaca!");
    return;
  }
  serial.print("========Monitoring tanaman=========\n");
  serial.print("kelembapan air tanah: ");
  serial.print(M); /*print kelembapan air*/
  serial.println(" %");
  delay(2000);
}
