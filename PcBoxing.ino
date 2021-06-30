#define SENSOR 2 // define pint 2 for sensor
#define ACTION 9 // define pin 9 as for ACTION

double calcDamage(double ReactValue)
{
    //TODO: case <=0.10 callComboMethod!!!
    if(ReactValue <= 0.15)
    {
      return 5;
    }
    else if(ReactValue <= 0.25)
    {
      return 3.5;
    }
    else if(ReactValue <= 0.55)
    {
      return 2;
    }
    else if(ReactValue <= 0.80)
    {
      return 2;
    }
    else if(ReactValue <= 1)
    {
      return 1;
    }
    else if(ReactValue == 20)
    {
      return 0;
    }
    else if(ReactValue == 25)
    {
      return 0;
    }
    else
    {return 0.7;}
  
}


void randomWait()
{
  int randomInt= random(0,1000); 
  while(randomInt<530||randomInt>600)
  {
   randomInt= random(0,1000);
   delay(200);
  } 
}

double ReactionTimer()
{
  double ReactValue=0;
  while(digitalRead(SENSOR)==1)
  {
    ReactValue+=0.01; delay(20);
    if(ReactValue > 2)
    {
      Serial.println("\nNo reaction detected ... forwarding.........");
      return 25;
      break;
    }
  }
  return ReactValue;
}

bool blocked()
{
  double reaction = ReactionTimer();
  if(reaction < 0.15)
  {
    return true;
  }else{return false;}
}

void greetings()
{
  Serial.println("Hello and welcome to PC Boxing!");
  
  Serial.println("Scroll your hand infront of the sensor to start playing...\n");
}

void initialPunchTutorial()
{
  Serial.println("When the emoji appears swing!!!\nThe faster the reaction, the bigger the damage!"); delay(5000);

  Serial.println("Starting in....");
  for(int i=3;i>0;i--)
  {
    Serial.print(i);
    delay(1000);
  }
}


class Player
{
  public:
  double Health =100;
  int combo =0;
  bool BonusPunch = false;
  
  bool isAlive()
  {
    if(Health>0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  double Punch()
{
  double reaction = ReactionTimer();

  if(reaction <=0.15)
  {
    combo++;
    if(combo==2)
    {
      Serial.println("\nNice! do it once more for a bonus punch!");
    }
    if(combo ==3)
    {
      BonusPunch=true; combo=0;
    }
    
  }else{combo=0;} 
  
  return reaction;
}

  bool BonusResult()
  {
    if(BonusPunch==false)
    {
      return false;
    }
    else
    {
      BonusPunch =  false;
      return true;
    }
  }

void TakeDamage(double takeDamage)
  {
   Health-=takeDamage;
   Print(takeDamage);
  }

  void Print(double takenDamage)
  {
    Serial.print("\nTaken damage: ");Serial.print(takenDamage);
    Serial.print("\nYour health is: ");Serial.println(Health); 
  }
  
};

class PC
{
  public:
  double Health =100;

  void Draw()
  {Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); Serial.print("(ง'̀-'́)ง"); }
  bool isAlive()
  {
    if(Health>0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  double Punch()
  {
  randomWait();
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");Serial.print("(ノ0益0)ノ彡┻━┻"); ; Serial.print("                              Block him now!!");
    if(blocked())
    {
      Serial.println("\nBlocked!!!");
      return 20;
    }
    else
    {
      int randInt = random(0,4);
      if(randInt = 0)
      {
        return 0.15;
      }
      else if (randInt = 1)
      {
        return 0.25;
      }
      else if (randInt = 2)
      {
        return 0.55;
      }
      else if (randInt = 3)
      {
        return 0.80;
      }
      else if (randInt = 4)
      {
        return 1;
      }
    }
  }

  void TakeDamage(double takeDamage)
  {
   Health-=takeDamage;
   Print(takeDamage);
  }

  void Print(double takenDamage)
  {
    Serial.print("\nGiven damage: ");Serial.print(takenDamage);
    Serial.print("\nHealth: ");Serial.println(Health); 
  }
};


void setup() 
{
  Serial.begin(9600);
  greetings();
  while(digitalRead(SENSOR)==1){}
  initialPunchTutorial();

  Player* player = new Player();
  PC* pc = new PC();
  while(player->isAlive()&&pc->isAlive())
  {
     randomWait();
     pc->Draw();
     pc->TakeDamage(calcDamage(player->Punch()));
     if(player->BonusResult()==true)
     {
      Serial.println("\nCombooo!!! Swing again!"); delay(1000);
      pc->Draw();
      pc->TakeDamage(calcDamage(player->Punch()));
     }
     delay(1000);
     player->TakeDamage(calcDamage(pc->Punch()));delay(1000);
  }




  if(player->isAlive())
  {Serial.println("Congrats you wont the fight!!!");}
  else
  {
    Serial.println("KO, better luck next time!");
  }

  Serial.println("Press the RESET button to play again!");
}

void loop(){}
