

// initialize the library with the numbers of the interface pins

#include <Servo.h>

Servo myservo;
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();
SoftwareSerial mySerial(2, 3);// tx, rx


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int pos = 0;

 void doorOpen()
{
  
  
  if(finger.fingerID==8 || finger.fingerID==1 ||finger.fingerID==2 ||finger.fingerID==3 ||finger.fingerID==4 ||finger.fingerID==5 ||finger.fingerID==6 ||finger.fingerID==7 )
  {
  Serial.println("Welcome MR.xxxxxxxx");//i enroled ID no 1 as Nidhi'sfingerprint, so used this line to display corresponding name
  
 
  digitalWrite(8,HIGH);
  myservo.write(60);
  delay(2000);
 
  }  
  
  
}


void doorClose()
{
  digitalWrite(8,LOW);
  myservo.write(pos);
   
}





void setup()  
{
 
  Serial.begin(38400);
  Serial.println("fingertest");
 finger.begin(57600);
 myservo.attach(9);
  pinMode(8,OUTPUT);//Pin connectet to relay
  
  if (finger.verifyPassword())
  {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for fingerprint...");
  
  }

  
  
  void loop()                     // run over and over again
{
      
  if(getFingerprintIDez()>=0)
  {
        doorOpen();
        delay(1000);
        doorClose();
  }
  
    
}
uint8_t getFingerprintID()
{
  uint8_t p = finger.getImage();
  switch (p)
  {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
        default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) 
  {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
