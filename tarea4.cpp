
#include <LiquidCrystal.h> 
 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 

#define COLS 16 
#define ROWS 2 
 

const int PinTrig = 7;
const int PinEcho = 6;
 

const float VelSon = 34000.0;
 

const int numLecturas = 100;
 

const float distancia100 = 2.15;
const float distanciaVacio = 11.41;
 
float lecturas[numLecturas]; 
int lecturaActual = 0; 
float total = 0; 
float media = 0; 
bool primeraMedia = false; 
 
void setup()
{
 
  Serial.begin(9600);
 
  pinMode(PinTrig, OUTPUT);
 
  pinMode(PinEcho, INPUT);
 
 
  for (int i = 0; i < numLecturas; i++)
  {
    lecturas[i] = 0;
  }
 
 
  lcd.begin(COLS, ROWS);
}
void loop()
{
 
  total = total - lecturas[lecturaActual];
 
  iniciarTrigger();
 
  
  unsigned long tiempo = pulseIn(PinEcho, HIGH);
 
  float distancia = tiempo * 0.000001 * VelSon / 2.0;
 
  lecturas[lecturaActual] = distancia;
 
 
  total = total + lecturas[lecturaActual];
 
  
  lecturaActual = lecturaActual + 1;
 

  if (lecturaActual >= numLecturas)
  {
    primeraMedia = true;
    lecturaActual = 0;
  }
 
  
  media = total / numLecturas;
 
 
  if (primeraMedia)
  {
    float distanciaLleno = distanciaVacio - media;
    float cantidadLiquido = distanciaLleno * 100 / distancia100;
    int porcentaje = (int) (distanciaLleno * 100 / distanciaVacio);
 
    
    lcd.clear();
  
    lcd.setCursor(0, 0);
    lcd.print(String(cantidadLiquido) + " ml");
 
   
    lcd.setCursor(0, 1);
    lcd.print(String(porcentaje) + " %");
 
    Serial.print(media);
    Serial.println(" cm");
 
    Serial.print(cantidadLiquido);
    Serial.println(" ml");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Calculando: " + String(lecturaActual));
  }
 
  delay(500);
}
 

void iniciarTrigger()
{
 
  digitalWrite(PinTrig, LOW);
  delayMicroseconds(2);
 
  
  digitalWrite(PinTrig, HIGH);
  delayMicroseconds(10);
 
 
  digitalWrite(PinTrig, LOW);
}
