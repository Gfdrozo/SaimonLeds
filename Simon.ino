// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Simon.ino
    Created:	19/09/2020 9:17:16 p. m.
    Author:     DESKTOP-5L42D1L\gfdia
*/
//lista dinamica
struct Minodo
{
	int info;
	Minodo* enlace1;
	Minodo* enlace2;


	Minodo()
	{
		info = 0;
		enlace1 = NULL;
		enlace2 = NULL;
	}
	Minodo(int Pinfo)
	{
		info = Pinfo;
		enlace1 = NULL;
		enlace2 = NULL;
	}
	Minodo(int Pinfo, Minodo* Penlace1, Minodo* Penlace2)
	{
		info = Pinfo;
		enlace1 = Penlace1;
		enlace2 = Penlace2;
	}
};
//estados del juego
enum Game
{
	si,
	no,

};

/////////////////////////////////////////////////////
/////VARIABLES
////////////////////////////////////////////////////
//arduino
int leds[5] = { A0,A1,A2,A3,A4 };
int btnLeds[6] = { 2,3,4,5,6,7 };

int estado;
Game start;

//arrays
Minodo* Simon, *Player;

int opc, cont, ale, user, valor;
bool game, chance;
float timer;


using namespace std;

/////////////////////////////////////////////////////
/////prototipos
////////////////////////////////////////////////////
void Reinicio();
int aleatorio();
Minodo* insertar(Minodo*, int);
int mostrar(Minodo*, int);
bool comparar(Minodo*, Minodo*, int x);
void demo();
void Play();
float temporizador();
void inicioLeds();
/////////////////////////////////////////////////////
/////funciones
////////////////////////////////////////////////////
void demo()
{
	while (digitalRead(btnLeds[5]) == 1)
	{

		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[0], HIGH);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		delay(1500);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[0], LOW);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[1], HIGH);
		if (digitalRead(btnLeds[5]) == 0){break;}
		delay(1500);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[1], LOW);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[2], HIGH);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		delay(1500);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[2], LOW);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[3], HIGH);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		delay(1500);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[3], LOW);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[4], HIGH);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		delay(1500);
		if (digitalRead(btnLeds[5]) == 0) { break; }
		digitalWrite(leds[4], LOW);
		if (digitalRead(btnLeds[5]) == 0) { break; }
	}
}
void Play()
{
	Reinicio();
	int bandera = 0;
	do
	{

		//Agregando aleatoriamente un valor a Simon y mostrarlo
		Simon = insertar(Simon, aleatorio());
		cont++;
		Player = NULL;

		//mostrando leds
		for (int i = 1; i <= cont; i++)
		{

			valor = mostrar(Simon, i);
			digitalWrite(leds[valor], HIGH);
			delay(1500);
			digitalWrite(leds[valor], LOW);
			delay(1500);
		}

		//obteniendo lo que ingresa el jugado
		float tiemp = 0;
		bool des = false;
		int clics = 0;
		int cant = 1;
		//capturar boton
		while (clics < cont)
		{
			while (tiemp < 5)
			{
				if (digitalRead(btnLeds[0]) == 0)
				{
					Player = insertar(Player, 0);
					des = true;
					clics += 1;
					tiemp = 0;
					digitalWrite(leds[0], HIGH);
					delay(500);
					digitalWrite(leds[0], LOW);
					delay(500);
					break;
				}
				else if (digitalRead(btnLeds[1]) == 0)
				{
					Player = insertar(Player, 1);
					des = true;
					clics += 1;
					tiemp = 0;
					digitalWrite(leds[1], HIGH);
					delay(500);
					digitalWrite(leds[1], LOW);
					delay(500);
					break;
				}
				else if (digitalRead(btnLeds[2]) == 0)
				{
					Player = insertar(Player, 2);
					des = true;
					clics += 1;
					tiemp = 0;
					digitalWrite(leds[2], HIGH);
					delay(500);
					digitalWrite(leds[2], LOW);
					delay(500);
					break;
				}
				else if (digitalRead(btnLeds[3]) == 0)
				{
					Player = insertar(Player, 3);
					des = true;
					clics += 1;
					tiemp = 0;
					digitalWrite(leds[3], HIGH);
					delay(500);
					digitalWrite(leds[3], LOW);
					delay(500);
					break;
				}
				else if (digitalRead(btnLeds[4]) == 0)
				{
					Player = insertar(Player, 4);
					des = true;
					clics += 1;
					tiemp = 0;
					digitalWrite(leds[4], HIGH);
					delay(500);
					digitalWrite(leds[4], LOW);
					delay(500);
					break;
				}
				Serial.println(tiemp);
				tiemp += temporizador();
			}
			if (des == true)
			{
				if (comparar(Simon, Player, clics) == false)
				{
					inicioLeds();
					start = no;
					des = false;
					clics = cont + 1;
					bandera = 1;
					break;
				}
				else
				{
					if (clics == cont)
					{
						cant = 1;
					}
					else
					{
						cant++;
					}

				}
			}
			else
			{
				inicioLeds();
				start = no;
				bandera = 1;
				break;
			}
		}
	} while (bandera == 0);
}

void inicioLeds()
{
	digitalWrite(leds[0], HIGH);
	digitalWrite(leds[1], HIGH);
	digitalWrite(leds[2], HIGH);
	digitalWrite(leds[3], HIGH);
	digitalWrite(leds[4], HIGH);
	delay(2000);
	digitalWrite(leds[0], LOW);
	digitalWrite(leds[1], LOW);
	digitalWrite(leds[2], LOW);
	digitalWrite(leds[3], LOW);
	digitalWrite(leds[4], LOW);
	delay(1500);

}
float temporizador()
{
	float aux = 0.1;
	delay(100);
	return aux;
}

void Reinicio()
{
	cont = 0;
	Simon = NULL;
	Player = NULL;
	game = true;
	chance = true;
	start = si;
}
int aleatorio()
{
	int aux;
	aux = random(5);
	return aux;
}
Minodo* insertar(Minodo *arr, int x)
{
	Minodo* Q = new Minodo(x);
	if (arr == NULL)//no hay nodos
	{
		arr = Q;
	}
	else // varios nodos
	{
		Minodo* P = NULL;//Crea sin memoria
		P = arr;//asigna
		while (P->enlace1 != NULL)//recorre los nodos
		{
			P = P->enlace1;
		}
		P->enlace1 = Q;

	}
	return arr;



}
int mostrar(Minodo* arr, int x)
{
	Minodo* P = arr;
	if (P == NULL)
	{
		return P->info;
	}
	else
	{
		int i = 1;
		if (x == 1)
		{
			return P->info;
		}
		else
		{
			for (i; i < x; i++)
			{
				P = P->enlace1;
			}
		}
		return P->info;
	}
}
bool comparar(Minodo* arr1, Minodo* arr2, int x)
{
	Minodo* P = arr1;
	Minodo* Q = arr2;
	if (P == NULL)
	{
		if (P->info != Q->info)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		int i = 1;
		if (x == 1)
		{
			if (P->info != Q->info)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			for (i; i < x; i++)
			{
				P = P->enlace1;
				Q = Q->enlace1;
			}
		}
		if (P->info != Q->info)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	start = no;

	//leds
	pinMode(leds[0], OUTPUT);
	pinMode(leds[1], OUTPUT);
	pinMode(leds[2], OUTPUT);
	pinMode(leds[3], OUTPUT);
	pinMode(leds[4], OUTPUT);
	

	//pulsadores
	pinMode(btnLeds[0], INPUT);
	pinMode(btnLeds[1], INPUT);
	pinMode(btnLeds[2], INPUT);
	pinMode(btnLeds[3], INPUT);
	pinMode(btnLeds[4], INPUT);
	pinMode(btnLeds[5], INPUT);
}

// Add the main program code into the continuous loop() function
void loop()
{
	
	while (digitalRead(btnLeds[5]) == 1 && start == no)
	{
		demo();
	}
	if (digitalRead(btnLeds[5]) == 0)
	{
		start = si;
		inicioLeds();
		Play();
	}
	
	
	
}
