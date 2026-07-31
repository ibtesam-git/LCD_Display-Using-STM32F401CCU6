/* ==== Add this line inside USER CODE BEGIN PV ==== */
#define SLAVE_ADDRESS_LCD 0x4E   // 0x27 shifted left by 1 - HAL needs it this way

/* ==== Add everything below inside USER CODE BEGIN 0 ==== */

void lcd_send_cmd(char cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C;  // EN=1, backlight on
    data_t[1] = data_u | 0x08;  // EN=0, backlight on
    data_t[2] = data_l | 0x0C;
    data_t[3] = data_l | 0x08;
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, 100);
}

void lcd_send_data(char data)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D;  // EN=1, RS=1 (this bit means "this is a letter, not a command")
    data_t[1] = data_u | 0x09;
    data_t[2] = data_l | 0x0D;
    data_t[3] = data_l | 0x09;
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, 100);
}

void lcd_init(void)
{
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);  // switch to 4-bit mode
    HAL_Delay(10);

    lcd_send_cmd(0x28);  // 4-bit mode, 2 line, 5x8 font
    HAL_Delay(1);
    lcd_send_cmd(0x08);  // display off
    HAL_Delay(1);
    lcd_send_cmd(0x01);  // clear display
    HAL_Delay(2);
    lcd_send_cmd(0x06);  // cursor moves right after each letter
    HAL_Delay(1);
    lcd_send_cmd(0x0C);  // display on, cursor off
    HAL_Delay(1);
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0: col |= 0x80; break;
        case 1: col |= 0xC0; break;
        case 2: col |= 0x94; break;
        case 3: col |= 0xD4; break;
    }
    lcd_send_cmd(col);
}

void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++);
}
