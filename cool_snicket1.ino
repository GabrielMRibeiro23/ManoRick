#include <Keypad.h>
#include <Servo.h>

Servo servo_Motor;

// Define a senha de desbloqueio
char* password = "1234B";
int position=0;

const byte ROWS = 4; // Número de linhas do teclado 4x4
const byte COLS = 4; // Número de colunas do teclado 4x4

// Define os caracteres do teclado 4x4
char keys [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Pinos das linhas do teclado 4x4
byte rowPins[ROWS] = {9,8,7,6};

// Pinos das colunas do teclado 4x4
byte colPins[COLS] = {5,4,3,2};

Keypad keypad = Keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int ledvermelho=12;
const int ledverde=11;

void setup(){
 pinMode (ledvermelho,OUTPUT);
 pinMode (ledverde, OUTPUT);
  
  servo_Motor.attach(13);
  setLocked(true);
  
}

void loop(){
  char key = keypad.getKey();
  
// Se as teclas "*" ou "#" for pressionada, limpa a senha
  if (key == '*'|| key == '#'){
    
  	position=0;
    setLocked(true);
  }
  
  if (key == password[position]){
    position++;
  }

//Quantidade de caractéres que serão usados na senha
  if(position == 5) {
   setLocked(false);  
  }
  delay(100);
  
}

void setLocked (int locked){

//Se a porta estiver fechada, o led vermelho será ligado e o verde desligado
  if (locked){
    digitalWrite (ledvermelho, HIGH);
    digitalWrite (ledverde, LOW);
    servo_Motor.write(0);
    
//Senão, o led vermelho será desligado e o verde ligado
  }else{
    digitalWrite (ledverde, HIGH);
    digitalWrite (ledvermelho, LOW);
    servo_Motor.write(82);
  }
}