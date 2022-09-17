// La función setup corre una vez, al prenderse el Arduino
// o bien al reiniciar mediante el botón reset
  int cont = 0;
  int cant = 1;
  //anodo comun 
  const int digitos [10][7] = {
   /*0*/ {0,0,0,0,0,0,1},
    /*1*/ {1,0,0,1,1,1,1},
    /*2*/ {0,0,1,0,0,1,0},
    /*3*/ {0,0,0,0,1,1,0},
    /*4*/ {1,0,0,1,1,0,0},
    /*5*/ {0,1,0,0,1,0,0},
    /*6*/ {0,1,0,0,0,0,0},
    /*7*/ {0,0,0,1,1,1,1},
    /*8*/ {0,0,0,0,0,0,0},
    /*9*/ {0,0,0,0,1,0,0}

    };
const int OFF = HIGH;
const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;

const int N = 7;
const int SEGMENTOS[N] = {A,B,C,D,E,F,G};

  
void setup()
{
    // Inicializa el pin digital 6 como pin de salida
    //pinMode(16, OUTPUT);
   Serial.begin(9600);
   //inicializamos pines digitales conectados a los segmentos del display.
  for (int i=0; i<N; i++){
    pinMode(SEGMENTOS[i], OUTPUT);
    digitalWrite(SEGMENTOS[i], OFF);//apagar
    }
    
}


void loop()
{

  int sensorValue = digitalRead(D0);    
  Serial.print(sensorValue);  

  if(sensorValue == 0){
    for(int i=0; i<10; i++){
      print(i);
      delay(1000);// esperar 1000 milisegundos
      }
   }
  
  
}


void print(int d){
  for (int i=0; i<N; i++){
    digitalWrite(SEGMENTOS[i], digitos[d][i]);
  }
}


// La función loop corre una y otra vez sin parar
  
  /*

   if(sensorValue == 0){
    cont += 1;
    digitalWrite(D1, HIGH);
    delay(60);
    Serial.print("Vuelta nro: ");  
    Serial.print(cont);
    Serial.println();
    }
    if(millis() >= (60000 * cant) ){
      cant += 1;
      Serial.print("RPM: ");  
      Serial.print(cont);
      Serial.println();
      cont = 0;
      }
    digitalWrite(D1, LOW);
  */
