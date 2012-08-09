#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    
    DDRB &= ~(1<<PB0);
    DDRA |= (1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3);
    PORTB = (1<<PB0); //pullup
    
    while(1) {    
        //WAIT FOR BUTTON PRESS
        uint8_t f = 0;
        uint8_t z = 0;
        while(PINB & (1<<PB0)) {
            if(!++f) {
                ++z;
                if(z%3)
                    PORTA = (1<<PA1);
                else if((z+1)%3)
                    PORTA = (1<<PA2);
                else if((z+2)%3)
                    PORTA = (1<<PA3);
                _delay_ms(23);
                PORTA = 0;
            }
            _delay_ms(23);
        }
        
        //WAIT FOR BUTTON RELEASE (liegt verkehrt am tisch -> ...)
        while(!(PINB & (1<<PB0))) _delay_ms(23);
        
        //WARNING WARNING WARNING WARNING
        for(f=0;f<4;f++) {
            PORTA = (1<<PA1);
            _delay_ms(100);
            
            PORTA = (1<<PA2);
            _delay_ms(100);
            
            PORTA = (1<<PA3);
            _delay_ms(100);
            
            PORTA = 0;
            _delay_ms(100);
        }
        
        //HOT HOT HOT!!!!
        PORTA = (1<<PA0);
        
        //ON THE FLY...
        for(uint8_t i=0;i<42;i++) {
            PORTA |= (1<<PA1)|(1<<PA2)|(1<<PA3);
            _delay_ms(42);
            PORTA &= ~((1<<PA1)|(1<<PA2)|(1<<PA3));
            _delay_ms(42);
            
            if(!(PINB & (1<<PB0))) {
                for(i=0;i<5;i++) {
                PORTA |= (1<<PA1)|(1<<PA2)|(1<<PA3);
                    _delay_ms(23);
                    PORTA &= ~((1<<PA1)|(1<<PA2)|(1<<PA3));
                    _delay_ms(23);
                }
                i=0;
            }
        }
        
        //ENTWARNUNG
        PORTA = 0;
    }
}
