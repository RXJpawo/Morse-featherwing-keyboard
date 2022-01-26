// Enable debug by calling this from keyboard file
void debug(char c)
{
  Serial.print('(');
  Serial.print(int (c));
  Serial.println(')');
  if (int(c) >= 31)  // Printable characters
  {
    Serial.println(c);
  }
  else // Non printable characters
  {
    switch(int (c))
    {
      case 0:  Serial.println ("<NUL>"); break;
      case 1:  Serial.println ("<SOH>"); break;
      case 2:  Serial.println ("<STX>"); break;
      case 3:  Serial.println ("<ETX>"); break;
      case 4:  Serial.println ("<EOT>"); break;
      case 5:  Serial.println ("<ENQ>"); break;
      case 6:  Serial.println ("<ACK>"); break;
      case 7:  Serial.println ("<BEL>"); break;
      case 8:  Serial.println ("<BS>");  break;
      case 9:  Serial.println ("<HT>");  break;
      case 10: Serial.println ("<LF>");  break;
      case 11: Serial.println ("<VT>");  break;
      case 12: Serial.println ("<FF>");  break;
      case 13: Serial.println ("<CR>");  break;
      case 14: Serial.println ("<SO>");  break;
      case 15: Serial.println ("<SI>");  break;
      case 16: Serial.println ("<DLE>"); break;
      case 17: Serial.println ("<DC1>"); break;
      case 18: Serial.println ("<DC2>"); break;
      case 19: Serial.println ("<DC3>"); break;
      case 20: Serial.println ("<DC4>"); break;
      case 21: Serial.println ("<NAK>"); break;
      case 22: Serial.println ("<SYN>"); break;
      case 23: Serial.println ("<ETB>"); break;
      case 24: Serial.println ("<CAN>"); break;
      case 25: Serial.println ("<EM>");  break;
      case 26: Serial.println ("<SUB>"); break;
      case 27: Serial.println ("<ESC>"); break;
      case 28: Serial.println ("<FS>");  break;
      case 29: Serial.println ("<GS>");  break;
      case 30: Serial.println ("<RS>");  break;
      case 31: Serial.println ("<US>");  break;
    }
  }
}
