void status_line()
{
  // Save position for last call in function
  int16_t my_x = tft.getCursorX();
  int16_t my_y = tft.getCursorY();
  
  tft.setTextColor(WHITE, BLACK); // Text overwrite mode (background black)
  tft.setCursor(0, 0); // Place cursor top left
  tft.print("CW Speed ");
  tft.print(cw_spd);
  tft.print(" WPM  "); // Extra spaces to adjust for WPM number length
  tft.setTextColor(WHITE); // No text backgound
  tft.drawLine(0, status_border, scr_width, status_border, WHITE);

  // Restore position
  tft.setCursor(my_x, my_y);
}

void soft_menu()
{
  // Save position for last call in function
  int16_t my_x = tft.getCursorX();
  int16_t my_y = tft.getCursorY();
  
  tft.setCursor(0, scr_height - HEIGHT); // Place cursor at bottom line
  tft.print("CQ   RST   S-  S+ NAME  73");
  tft.drawLine(0, menu_border, scr_width, menu_border, WHITE);

  // Restore position
  tft.setCursor(my_x, my_y);
}

void redraw_screen ()
{
  // shift array one step, row-based FIFO 
  memmove(scr_buf, &scr_buf[1], (sizeof(scr_buf) - CHARS - 1));
  scr_buf[ROWS-1][0] = '\0';
  
  // Blank screen
  tft.fillScreen(BLACK);

  // Write the whole array back to the screen
  tft.setCursor(0, HEAD);
  for (int l = 0; l < ROWS; l++)
  {
    for (int c = 0; c < CHARS + 1 ; c++)
    {
      if (scr_buf[l][c] == '\0')
      {
        tft.setCursor(0, (HEIGHT + 2) * (l + 1) + HEAD);
        break;
      }
      else
      {
        tft.print(scr_buf[l][c]);
      }
    }
  }

  // Adjust rows to 2:nd last row
  row = ROWS - 1;
  tft.setCursor(0, (HEIGHT + 2) * row + HEAD);

  // Redraw header and footer
  status_line();
  soft_menu();
}

void draw_char(char key)
{
  // Use variables and increase row and char last in function
  bool add_chr = false;
  bool add_row = false;

  // Put character both on screen and in buffer array
  tft.print(char(key));
  scr_buf[row][chr] = char(key);
  add_chr = true;

  // If key is '=' (linefeed), then add linefeed for readability
  // Requires some handling of chr and row also
  if (key == '=')
  {
    tft.print('\n');
    chr++;
    scr_buf[row][chr] = '\0';
    add_row = true;
  }

  // We have reached the end of the line
  if (chr >= CHARS - 1)
  {
    scr_buf[row][chr] = '\n';
    add_row = true;
    chr = 0;
  }

  // Read the booleans and act accordingly
  if (add_chr) chr++;

  if (add_row)
  {
    chr = 0;
    row++;
    tft.setCursor(0, (row * (HEIGHT + 2)) + HEAD);
  }

  // Ooops we are running out of screen here
  if (row > ROWS - 1)
  {
    redraw_screen();
  }
}
