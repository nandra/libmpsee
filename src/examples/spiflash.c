#include <stdio.h>
#include <stdlib.h>

#include "mpsse.h"

#define SIZE	0x10			// Size of SPI flash device: 1MB
#define RCMD	"\x03\x00\x00\x00"	// Standard SPI flash read command (0x03) followed by starting address (0x000000)
#define FOUT	"flash.bin"		// Output file

int main(void)
{
	FILE *fp = NULL;
	char *data = NULL, *data1 = NULL;
	int retval = EXIT_FAILURE;
	struct mpsse_context *flash = NULL;
	
	if((flash = mpsse_init(SPI0, TWELVE_MHZ, MSB)) != NULL && flash->open)
	{
		printf("%s initialized at %dHz (SPI mode 0)\n", get_description(flash), get_clock(flash));
		
		start(flash);
		write_data(flash, RCMD, sizeof(RCMD) - 1);
		data = read_data(flash, SIZE);
		data1 = read_data(flash, SIZE);
		stop(flash);
		
		if(data)
		{
			fp = fopen(FOUT, "wb");
			if(fp)
			{
				fwrite(data, 1, SIZE, fp);
				fwrite(data1, 1, SIZE, fp);
				fclose(fp);
				
				printf("Dumped %d bytes to %s\n", SIZE, FOUT);
				retval = EXIT_SUCCESS;
			}

			free(data);
		}
	}
	else
	{
		printf("Failed to initialize MPSSE: %s\n", error_string(flash));
	}

	release(flash);

	return retval;
}
