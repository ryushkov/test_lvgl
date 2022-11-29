#include <Arduino_GFX_Library.h>
#include <TAMC_GT911.h>



#define CS_PIN  38
#define GFX_BL DF_GFX_BL
#define TFT_BL 2
#define TOUCH_SDA  19
#define TOUCH_SCL  20
#define TOUCH_INT 18
#define TOUCH_RST 38
#define TOUCH_WIDTH  480
#define TOUCH_HEIGHT 272
TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *gfx = create_default_Arduino_GFX();
#else


Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);

 Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
   bus,
   800 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 8 /* hsync_back_porch */,
   480 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 8 /* vsync_back_porch */,
   1 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);

#endif 


void setup(void)
{
    gfx->begin();
    tp.begin();
    tp.setRotation(ROTATION_INVERTED);
    delay(1000);
    gfx->fillScreen(BLACK);
    delay(1000);
    gfx->fillRoundRect(40,30,200,160,6,YELLOW);
    gfx->fillRoundRect(290,30,200,160,6,YELLOW);
    gfx->fillRoundRect(540,30,200,160,6,YELLOW);
    gfx->fillRoundRect(40,220,200,160,6,YELLOW);
    gfx->fillRoundRect(290,220,200,160,6,YELLOW);
    gfx->fillRoundRect(540,220,200,160,6,YELLOW);
#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
#endif
    delay(1000); 
}


void loop()
{
	tp.read();
	if (tp.isTouched){
		for (int i=0; i<tp.touches; i++){
            int x = (tp.points[i].x);
            int y = (tp.points[i].y);
			if (x>26 && x<140 && y>26 && y<105){gfx->fillRoundRect(40,30,200,160,6,GREEN);}
			if (x>184 && x<289 && y>26 && y<105){gfx->fillRoundRect(290,30,200,160,6,GREEN);}
			if (x>328 && x<439 && y>26 && y<105){gfx->fillRoundRect(540,30,200,160,6,GREEN);}
			if (x>24 && x<145 && y>130 && y<210){gfx->fillRoundRect(40,220,200,160,6,GREEN);}
			if (x>179 && x<294 && y>130 && y<210){gfx->fillRoundRect(290,220,200,160,6,GREEN);}
			if (x>332 && x<444 && y>130 && y<210){gfx->fillRoundRect(540,220,200,160,6,GREEN);}
			gfx->setTextSize(2);
			gfx->setCursor(0, 0);
			gfx->print("  x: ");gfx->print(x);
			gfx->print("  y: ");gfx->print(y);
			delay(3000);
			gfx->fillRect(0,0,200,20,BLACK);
		}
	}
}
