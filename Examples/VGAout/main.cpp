#include "Pokitto.h"
#include "sct_11u6x.h"


/* Working principle:
SCT is set to flip HSync at 31.77 uS. The low state (hsync) lasts for 3.77 uS
SCT is set to pull Hsync low at 28 us. Reset occurs at 31.77 us, counters get zeroed.
A VSync_count interrupt gets called at the end of every scanline, VSync_count is incremented
When VSync_count reaches the drawing state (end of vsync back porch), main loop begins pushing out pixels via RGB lines
Main loop pushes X amount of pixels out, then stalls until VSync_count is incremented, signifying a HSync front porch
When 480 lines have been pushed out or VSync_state is changed away from the drawing state, no more pixels are pushed
and the main loop just rolls over */

/* In Pokitto PEX header, the EXT0 PWM pin is P1_19, and pinmode 2 is SCT0_OUT0 � SCTimer0/PWM output 0 */

#define CLR_VSYNC LPC_GPIO_PORT->CLR[0] = 1 << 11
#define SET_VSYNC LPC_GPIO_PORT->SET[0] = 1 << 11

#define CLR_R LPC_GPIO_PORT->CLR[0] = 1 << 12
#define SET_R LPC_GPIO_PORT->SET[0] = 1 << 12
#define CLR_G LPC_GPIO_PORT->CLR[0] = 1 << 13
#define SET_G LPC_GPIO_PORT->SET[0] = 1 << 13
#define CLR_B LPC_GPIO_PORT->CLR[0] = 1 << 14
#define SET_B LPC_GPIO_PORT->SET[0] = 1 << 14

mbed::DigitalOut VSync(EXT1);
mbed::DigitalOut R(EXT2);
mbed::DigitalOut G(EXT3);
mbed::DigitalOut B(EXT4);
mbed::PwmOut HSync(EXT0);

volatile int vsync_counter=0;
volatile int counteract=0;

enum VSYNC_STATES
{
  VSYNC_LOW_ENABLED = 1, // 0
  VSYNC_BACKPORCH_STARTS = 3, // 0.064ms
  VSYNC_BACKPORCH_ENDS_DRAWING_BEGINS = 34, // 1.084ms
  VSYNC_FRONTPORCH_STARTS = 514, // 16.334ms
  VSYNC_FRONTPORCH_ENDS = 528 // //
};


/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	/* This is only used to wakeup up the device from sleep */
}

/**
 * @brief	Handle interrupt from HSync reset (end of scanline)
 * @return	Nothing
 */
extern "C" {
void SCT0_1_IRQHandler(void)
{
    // halt and clear the counter
    LPC_SCT0->CTRL |= (1 << 2) | (1 << 3);
    LPC_SCT0->COUNT = 0;
    LPC_SCT0->CTRL &= ~(1 << 2);

    /* Clear the Interrupt */
	Chip_SCT_ClearEventFlag((LPC_SCT_T*)LPC_SCT0, (CHIP_SCT_EVENT)0x01);
    //LPC_SCT0->EVFLAG = 0x3;
//CLR_R;CLR_G;CLR_B;
    /* Vsync state changer */

    switch (vsync_counter) {
    case VSYNC_LOW_ENABLED:
        CLR_VSYNC;
        break;
    case VSYNC_BACKPORCH_STARTS:
        SET_VSYNC;
        break;
    case VSYNC_FRONTPORCH_ENDS:
        vsync_counter=0; //loop around

        break;
    }
    vsync_counter++;

    //LPC_SCT0->CTRL &= ~(1 << 2);

}}


void initHSync() {

    HSync.period(0.000032f); //30.80us
    HSync.pulsewidth(0.000028f); // 3.08us

    // halt and clear the counter
    LPC_SCT0->CTRL |= (1 << 2) | (1 << 3);

    NVIC_SetVector((IRQn_Type)13, (uint32_t)&SCT0_1_IRQHandler);
    NVIC_EnableIRQ((IRQn_Type)13);

    // Event 0 : MATCH and MATCHSEL=0
    LPC_SCT0->EV0_CTRL  = (1 << 12);
    //LPC_SCT0->EV0_STATE = 0x1;
    // Event 1 : MATCH and MATCHSEL=1
    LPC_SCT0->EV1_CTRL  = 0x1001; //(1 << 12) | (1 << 0);
    //LPC_SCT0->EV1_STATE = 0x2;

	/* Enable the interrupt */
	LPC_SCT0->EVEN = (1<<0); //bit 0 is 1. When flag register bit 0 is also 1, interrupt is requested

	/* Unhalt the counter to start */
	LPC_SCT0->CTRL &= ~(1 << 2); // bit 2, HALT When this bit is 1 counter does not run and no events can occur.


}

int main ()
{
volatile int vsync_old=0;
VSync = 1; counteract=5;
initHSync();
volatile int toggle=0;

	while (1)
	{

        if (vsync_counter == VSYNC_BACKPORCH_ENDS_DRAWING_BEGINS) {

                for (int i=0; i<480; i++) {
                        vsync_old = vsync_counter; /* store line we are on */
                        /* draw line here, this has to be faster than the HSync frequency */
                        //CLR_R;CLR_G;CLR_B;
                        for (int j=0; j < 16; j++) SET_R;
                        CLR_R;//CLR_G;CLR_B;
                        for (int j=0; j < 16; j++) SET_G;
                        //CLR_R;
                        CLR_G;//CLR_B;
                        for (int j=0; j < 16; j++) SET_B;
                        CLR_B;
                        /* set color off so that it is off during hsync*/
                        CLR_R;CLR_G;
                        /* wait for a new line trigger */
                        while (vsync_counter == vsync_old) {
                            toggle++;
                        };

                }
        }
	}
}
