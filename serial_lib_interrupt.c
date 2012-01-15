#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>

#define TBUFSIZE	1024

/* This array is used as a circular buffer.. */
volatile unsigned char tbuf[TBUFSIZE];
/* 
..the following two indexes keep track of where to
write data (t_in) and where to read from (t_out)
*/
volatile unsigned char t_in;
volatile unsigned char t_out;
volatile unsigned char serial_enabled = 0;

/* 
This function returns the amount of data 
in the circular buffer, i.e. the distance between
write and read indexes, note it's more tricky when 
the buffer "wraps"
*/
char tbuflen(void) 
{
    if (t_in > t_out){
        return t_in - t_out;
    }
    else
    {
        return TBUFSIZE - t_out + t_in;
    }
}

void serial_init()
{
    /* reset the indexes of the circular buffer */
    t_in = 0;
    t_out = 0;
    serial_enabled = 1;
    /* Set the baud rate */
    const unsigned int baud = 9600;
    const unsigned int bittimer = F_CPU / baud / 8 - 1;
    UBRR0H = (unsigned char) (bittimer >> 8);
    UBRR0L = (unsigned char) bittimer;
	
	// 8N1
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);	
    
	// receive and transmit enabled
	UCSR0B |= (1<<TXEN0)|(1<<RXEN0);

	// Global interrupt enable
	sei();
	
	return;
}


/* 
This function is called when the serial port data register
becomes empty i.e. when the next char can be transmitted. 

This function does not have the usual function structure 
(<return type> <function name>(<arguments>)) because it is 
defined through a macro. The compiler will replace 
"ISR(USART_UDRE_vect)" with something like
void USART_UDRE_vect(void)
*/
ISR(USART_UDRE_vect) 
{
    /* if there is data in the buffer.. */
	if(tbuflen() != 0) {
	    /* send the next char */
		UDR0 = tbuf[t_out];
		/* advance the index, wrap if necessary */
		t_out = (t_out + 1) % TBUFSIZE;
 	}
	else 
	{
	    /* 
	    nothing left to write, so
	    we disable (turn off) the interrupt
	    (otherwise this function would be 
	    called again and again..)
	    */
		UCSR0B &= ~(1<<UDRIE0);
	}
	return;
}

/*
Using the interrupt serial_putchar does not send data directly,
it writes the data to be sent in the buffer and triggers the 
interrupt, so that ISR(USART_UDRE_vect) is called and the data 
is sent from there
*/
int serial_putchar(const char c) 
{
	/* 
	If the transmit buffer is full, wait.
	This should happen rarely, and the buffer size can be
	adjusted to make sure this is rare.
	*/
	while((TBUFSIZE - tbuflen()) <= 1);
	
	/* Add data to the transmit buffer */
	tbuf[t_in] = c;
	t_in = (t_in + 1) % TBUFSIZE;
	
	/* Enable UDR empty interrupt */
	UCSR0B |= (1<<UDRIE0);
    
    /* manually trigger the interrupt to start the process */
	UCSR0A |= (1<<UDRE0);
	
	return 0;
}

void serial_puts(const char * string)
{
    int i=0;
    
    while (string[i] != '\0') 
    {
        serial_putchar(string[i++]);
    }
    return;
}

int serial_printf(const char *fmt, ...)
{
    if (!serial_enabled) return 0;
    char string[256];
    va_list ap;
    int r;
    va_start (ap, fmt);
    r = vsprintf (string, fmt, ap);
    va_end (ap);
    serial_puts(string);
    return r;
}



