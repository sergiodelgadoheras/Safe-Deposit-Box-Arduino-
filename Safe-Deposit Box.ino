#include <Servo.h> 
#include <Keypad.h>
#include <EEPROM.h>


Servo servomotor;//servo seguro
Servo servomotor1;// servo Puerta

char* password = {"1234" } ;// definicion clave 
int position = 0;//posicion inicial en 0

const byte rows = 4; //filas
const byte cols = 3 ; //columnas
char keys[rows][cols] = {

  {'1', '2', '3'},//fila 1
  {'4', '5', '6'},//fila 2
  {'7', '8', '9'},//fila 3
  {'*', '0', '#'} //fila 4
};

byte rowPins[rows] = {2, 3, 4, 5}; // Definicion pines filas
byte colPins[cols] = {6, 7, 8}; //Definicion pines columnas
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);//Reconocimiento libreria

int greenPin = 9; // Definicion de pines
int greenPin1 = 10;
int greenPin2 = 11; 
int greenPin3 = 0; 
int redPin = 1;
//0 1 servos, de 2 a 8 teclado, 9 a 13 leds.
void setup()
{
  servomotor.attach(12); //abrir puerta
  servomotor1.attach(13); //abrir seguro
  pinMode(redPin, OUTPUT); //denotar salida
  pinMode(greenPin, OUTPUT); 
  pinMode(greenPin1, OUTPUT);
  pinMode(greenPin2, OUTPUT); 
  pinMode(greenPin3, OUTPUT); 
  
  desbloqueo(true); // desbloqueo puerta
}

void loop()
{
//Valor de ingreso de la clave
  char key = keypad.getKey();
  int a=0;
  do
  {
    if (key == '*' )//dar posicion a 0 e ingresar la contraseña 
    {
      position = 0; //Posicion 0
    }                                                                                 
    if (key == password [position]) //incremento de 1 en 1 para la posicion 
    {
      position ++;//Incremento
     
    if (position == 1)
    {
     digitalWrite(greenpin, HIGH );            
    }
    if (position == 2)
      {
       digitalWrite(greenpin1, HIGH );            
    }if (position == 3)
    {
     digitalWrite(greenpin2, HIGH );            
    }if (position == 4)
    {
     digitalWrite(greenpin3, HIGH );            
    }
  }
  
  if (position == 4)
  {
   desbloqueo(true);
        if (key == '*' )
     {
       desbloqueo(false);
       position = 0; 
     }               
  }
  else {
    desbloqueo(false);
    a++
  }
  delay(100);
  }while(a!=3)

}
void desbloqueo (int cerradura)                                         
{
  
  if (cerradura) {                      
    digitalWrite(greenpin, HIGH ); 
    digitalWrite(greenpin1, HIGH); 
    digitalWrite(greenpin2, HIGH); 
    digitalWrite(greenpin3, HIGH);  
    digitalWrite(redPin, LOW);
   
    servomotor1.write(180);
     delay(1000);
    servomotor.write(180);
    delay(100); 
       
  }
  else {     
    digitalWrite(redPin, HIGH);    
    digitalWrite(greenPin1, LOW);
    digitalWrite(greenPin2, LOW);
    digitalWrite(greenPin3, LOW);
    digitalWrite(greenPin4, LOW);
       
    servomotor.write(0);
    delay(1000); 
    servomotor1.write(0);
    delay(100);
  }
}
