void NR()
{
  if(MNR == true){
  if(ntp.hour()== hNon && ntp.minute() == mNon && ntp.second() >= sNon){flagNR = true;yar = 0;flagGV = false; P.setIntensity(yar);}
  if(ntp.hour()== hNoff && ntp.minute() == mNoff && ntp.second() >= sNoff){flagNR = false;yar = oldyar;flagGV = true;P.setIntensity(yar);}
  if ((hNon < hNoff) && (ntp.hour() > min(hNon, hNoff) && ntp.hour() < max(hNon, hNoff-1))){flagNR = true;yar = 0;flagGV = false;P.setIntensity(yar);}
  if ((hNon > hNoff) && (ntp.hour() > max(hNon, hNoff) || ntp.hour() < min(hNon, hNoff-1))){flagNR = true;yar = 0;flagGV = false;P.setIntensity(yar);}
  if((hNon < hNoff) && (ntp.hour() < min(hNon, hNoff) || ntp.hour() > max(hNon, hNoff+1))){flagNR = false;yar = oldyar;flagGV = true;P.setIntensity(yar);}
  if((hNon > hNoff) && (ntp.hour() > min(hNon, hNoff) && ntp.hour() < max(hNon, hNoff+1))){flagNR = false;yar = oldyar;flagGV = true;P.setIntensity(yar);}
    }
}
