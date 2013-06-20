int val=0; // To store the value from the LDR
int laserPin=12;
int redLed=8;
int flash=10;
int greenLed=13;
int ldrPin=0;
bool aligned=false;
bool lastAligned=false;
bool beamBroken=false;

void setup() {
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(flash,OUTPUT);
}

void loop()
{
  // Laser/LDR alignment
  val=analogRead(ldrPin);
  if(val > 200)
  {
    digitalWrite(greenLed,HIGH);
    aligned=true;
  }
  else
  {
    digitalWrite(greenLed,LOW);
    aligned=false;
  }
  // Broken beam?
  if(lastAligned!=aligned && aligned==false)
  {
    // Alignment has changed or beam broken
    beamBroken=true;
  }
  else
  {
    beamBroken=false;
  }

  if(beamBroken)
  {
    digitalWrite(laserPin,LOW);
    // We probably need to put a delay here, to allow
    // the laser to turn off before the flash triggers
    digitalWrite(redLed,HIGH);
    digitalWrite(flash,HIGH);
    delay(10);
    digitalWrite(flash,LOW);
    delay(1000);
    digitalWrite(laserPin,HIGH);
    digitalWrite(redLed,LOW);
    delay(200); // Wait some time to allow the LDR
                // to stabilize after laser off/on
                // to avoid false positives.
  }
  digitalWrite(laserPin,HIGH);
  lastAligned=aligned;
}
