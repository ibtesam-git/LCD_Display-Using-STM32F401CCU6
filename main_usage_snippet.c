/* ==== Add this inside USER CODE BEGIN 2, inside main() ==== */

lcd_init();
lcd_put_cur(1, 0);
lcd_send_string("Internee's Task");
lcd_put_cur(2, 0);
lcd_send_string("succeeded");
