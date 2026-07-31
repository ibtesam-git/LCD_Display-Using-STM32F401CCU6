# STM32 I2C LCD Display

Displays text on a 16x2 (or 20x4) I2C character LCD using an STM32F401CCU6 microcontroller, driven directly through STM32 HAL (no Arduino library used).

## Hardware Used

- STM32F401CCU6 (Blackpill board)
- I2C 16x2 LCD display (PCF8574 backpack)
- ST-Link programmer

## Pinout / Wiring

| LCD Pin | STM32 Pin |
|---------|-----------|
| GND     | GND       |
| VCC     | 5V        |
| SDA     | PB7       |
| SCL     | PB6       |

## STM32CubeMX Configuration

1. Select MCU: **STM32F401CCUx**
2. System Core → SYS → Debug: **Serial Wire**
3. Connectivity → I2C1 → Mode: **I2C**
4. I2C1 → GPIO Settings → PB6 and PB7: **Pull-up**
5. I2C1 → Speed Mode: **Standard Mode**, Speed: **100000 Hz**
6. Generate Code (Toolchain: STM32CubeIDE)

## Files

- `lcd_i2c.c` — all LCD driver functions (init, send command, send data, cursor positioning, string printing)
- `main_usage_snippet.c` — example of what to add inside `main()` after code generation

## How to Use

1. Set up the project in STM32CubeMX using the configuration above.
2. Copy the contents of `lcd_i2c.c` into the `USER CODE BEGIN 0` section of `main.c` (function definitions), and the `#define` line into `USER CODE BEGIN PV`.
3. Copy the contents of `main_usage_snippet.c` into `USER CODE BEGIN 2` inside `main()`.
4. Build and flash using ST-Link.

## Notes

- LCD default I2C address used: `0x27` (written as `0x4E` in code, since HAL expects the address already shifted left by 1).
- If your specific module doesn't respond, try address `0x3F` instead.
- Contrast is controlled by the small potentiometer on the back of the LCD backpack — adjust if the screen looks blank.
