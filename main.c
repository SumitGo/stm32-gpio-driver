// Task: Blink Pin9 (user led green)

#define PERIPH_BASE_ADD 0x40000000u

#define GPIO_PORTC_ADD 0x40011000u

#define RCC_BASE_ADD 0x40021000u

#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE_ADD + 0x18)) // vlalue at the Address of RCC_APB2ENR, clock enable register for pin9(set bit 4)

#define CNF_H_R_OFFSET 0x04u

#define IOPC_MODE_R (*(volatile unsigned int *)(GPIO_PORTC_ADD + CNF_H_R_OFFSET)) // value at the address of GPIO_CRH register

#define PIN9_BSRR_ADD (*(volatile unsigned int *)(GPIO_PORTC_ADD + 0x10u)) // value at the address of GPIO_BSRR register

int main(void)
{
    // this line enables clock access to pin 9, using RCC_APB2ENR
    RCC_APB2ENR = RCC_APB2ENR | 1u << 4; // writing bit 4 value to 1

    // this line sets pin 9 for output mode
    //  set bit 4 and 5 to 1, in the  GPIO CRH register
    IOPC_MODE_R |= 1u << 4;
    IOPC_MODE_R |= 1u << 5;

    while (1)
    {
        // set bit 9 of bsrr register
        PIN9_BSRR_ADD |= 1u << 9; // turn the led on(green)

        // this loop keeps the led off for 10 counts of i
        for (int i = 0; i < 10; i++)
        {
            PIN9_BSRR_ADD &= ~(1u << 9); // turns the led off
        }
    }

    return 0;
}