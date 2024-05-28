void Budilok()
{
  switch(ntp.dayWeek()){
    case 1:if(BUD1==true){hBud=hBud1;mBud=mBud1;Pap=PaB1;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 2:if(BUD2==true){hBud=hBud2;mBud=mBud2;Pap=PaB2;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 3:if(BUD3==true){hBud=hBud3;mBud=mBud3;Pap=PaB3;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 4:if(BUD4==true){hBud=hBud4;mBud=mBud4;Pap=PaB4;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 5:if(BUD5==true){hBud=hBud5;mBud=mBud5;Pap=PaB5;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 6:if(BUD6==true){hBud=hBud6;mBud=mBud6;Pap=PaB6;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 7:if(BUD7==true){hBud=hBud7;mBud=mBud7;Pap=PaB7;BUD = true;
    }else{
     BUD = false; 
    }
    break;
  }
  if(hBud == ntp.hour() && mBud == ntp.minute() && ntp.second() == 00 && BUD == true){
      flagBudilnik = true;
      dfPlayer.volume(Y);
      dfPlayer.playFolder(14, Pap);
      Mod7();
      }else{
       flagBudilnik = false; 
      }
}
void Mod7()
{
  if(flagBudilnik == true){
    
   P.displayText(Buf7, just, sk, 1,PA_NO_EFFECT ,PA_NO_EFFECT);
      P.displayReset();
     }
}
