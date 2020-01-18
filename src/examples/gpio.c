#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mpsse.h"

int main(void)
{
	struct mpsse_context *io = NULL;
	int i = 0, retval = EXIT_FAILURE;

	io = mpsse_init(GPIO, 0, 0);
	
	if(io && io->open)
	{
		for(i=0; i<10; i++)
		{
			set_pin_high(io, GPIOL0);
			printf("GPIOL0 State: %d\n", pin_state(io, GPIOL0, -1));
			sleep(1);
			
			set_pin_low(io, GPIOL0);
			printf("GPIOL0 State: %d\n", pin_state(io, GPIOL0, -1));
			sleep(1);
		}
	
		retval = EXIT_SUCCESS;
	}
	else
	{
		printf("Failed to open MPSSE: %s\n", error_string(io));
	}
		
	release(io);

	return retval;
}
