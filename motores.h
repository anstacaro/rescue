#define pwma 4
#define ai1 16
#define ai2 17

#define pwmb 19
#define bi1 5
#define bi2 18

const int frecuencia = 5000;
const int resolucion = 8;

void motorsetup(){
  ledcSetup(1, frecuencia, resolucion);
  ledcAttachPin(pwma, 1);
  ledcSetup(0, frecuencia, resolucion);
  ledcAttachPin(pwmb, 0);
  pinMode(ai1, OUTPUT);
  pinMode(ai2, OUTPUT);
  pinMode(bi1, OUTPUT);
  pinMode(bi2, OUTPUT);
  }
void motor(int velder, int velizq){
  if(velder < 0){
    digitalWrite(ai1, LOW);
    digitalWrite(ai2, HIGH);
    }else if(velder > 0){
    digitalWrite(ai1, HIGH);
    digitalWrite(ai2, LOW);      
      }else{
    digitalWrite(ai1, LOW);
    digitalWrite(ai2, LOW);             
        }
  if(velizq < 0){
    digitalWrite(bi1, HIGH);
    digitalWrite(bi2, LOW);
    }else if(velizq > 0){
    digitalWrite(bi1, LOW);
    digitalWrite(bi2, HIGH);      
      }else{
    digitalWrite(bi1, LOW);
    digitalWrite(bi2, LOW);             
        }
  ledcWrite(0,abs(velder));
  ledcWrite(1,abs(velizq));
  }