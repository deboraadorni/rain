int pin_d = 7; // Digital pin connected to D0
int pin_a = A5; // Analog pin connected to A0
int val_d = 0; // Stores digital value
int val_a = 0; // Stores analog value

void setup()
{
  pinMode(pin_d, INPUT);
  pinMode(pin_a, INPUT);
  /**
     Sets the data rate in bits per second (baud) for serial data transmission.
     For communicating with the computer, use one of these rates: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200.
     You can, however, specify other rates - for example, to communicate over pins 0 and 1 with a component that requires a particular baud rate.
  */
  Serial.begin(9600);
}

void loop()
{
  val_d = digitalRead(pin_d);
  val_a = analogRead(pin_a);

  Serial.print("Digital value: ");
  Serial.println(val_d);
  Serial.print("Analog value : ");
  Serial.println(val_a);

  // Digital output
  if (val_d != null) {
    if (val_d == 1)
    {
      Serial.println("Raining! =D");
    }
    else
    {
      Serial.println("Not raining... =(");
    }
  }

  if (val_a != null) {
    // Analog output
    if (val_a > 700)
    {
      Serial.println("RUN TO THE HILLS!!!");
    }
    else if (val_a > 500 && val_a < 700)
    {
      Serial.println("Wow! We have a storm here!");
    }
    else if (val_a > 300 && val_a < 500)
    {
      Serial.println("Yay! RAIN!");
    }
    else if (val_a > 100 && val_a < 300)
    {
      Serial.println("Kind normal...");
    }
    else if (val_a < 100)
    {
      Serial.println("Are we in Atacama desert?");
    }
  }
  delay(2000);
}

