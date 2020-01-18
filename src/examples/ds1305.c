#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mpsse.h"

int main(void)
{
	struct mpsse_context *ds1305 = NULL;
	int sec = 0, min = 0, retval = EXIT_FAILURE;
	char *control = NULL, *seconds = NULL, *minutes = NULL;
	
	if((ds1305 = mpsse_init(SPI3, ONE_HUNDRED_KHZ, MSB)) != NULL && ds1305->open)
	{
		set_cs_idle(ds1305, 0);

		printf("%s initialized at %dHz (SPI mode 3)\n", get_description(ds1305), get_clock(ds1305));
		
		start(ds1305);
		write_data(ds1305, "\x0F", 1);
		control = read_data(ds1305, 1);
		stop(ds1305);
		
		control[0] &= ~0x80;
		
		start(ds1305);
		write_data(ds1305, "\x8F", 1);
		write_data(ds1305, control, 1);
		stop(ds1305);

		free(control);

		while(1)
		{
			sleep(1);

			start(ds1305);
			write_data(ds1305, "\x00", 1);
			seconds = read_data(ds1305, 1);
			stop(ds1305);

			sec = (((seconds[0] >> 4) * 10) + (seconds[0] & 0x0F));

			start(ds1305);
			write_data(ds1305, "\x01", 1);
			minutes = read_data(ds1305, 1);
			stop(ds1305);

			min = (((minutes[0] >> 4) * 10) + (minutes[0] & 0x0F));

			printf("%.2d:%.2d\n", min, sec);

			free(minutes);
			free(seconds);
		}	
	}
	else
	{
		printf("Failed to initialize MPSSE: %s\n", error_string(ds1305));
	}

	release(ds1305);

	return retval;
}
