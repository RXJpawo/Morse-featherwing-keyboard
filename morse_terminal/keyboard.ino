// Read key, only register "release"
char read_key()
{
  int keyc = keyboard.keyCount();
  if (keyc == 0)
  {
    return 0;
  }

  BBQ10Keyboard::KeyEvent key = keyboard.keyEvent();
  if (key.state == BBQ10Keyboard::StateIdle)
  {
    return 0;
  }
  else if (key.state == BBQ10Keyboard::StatePress)
  {
    return 0;
  }
  else if (key.state == BBQ10Keyboard::StateLongPress)
  {
    return 0;
  }
  else if (key.state == BBQ10Keyboard::StateRelease)
  {
    //debug(key.key); // Uncomment to see keys in serial monitor
    return key.key;
  }
  else
  {
    return -1;
  }
}
