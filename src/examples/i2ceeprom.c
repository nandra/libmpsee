/* 
 * Example code to read the contents of an I2C EEPROM chip.
 */

#include <stdio.h>
#include <stdlib.h>

#include "mpsse.h"

#define SIZE	0x8000		// Size of EEPROM chip (32KB)
#define WCMD	"\xA0\x00\x00"	// write start address command
#define RCMD	"\xA1"		// Read command
#define FOUT	"eeprom.bin"	// Output file

int main(void)
{
	FILE *fp = NULL;
	char *data = NULL;
	int retval = EXIT_FAILURE;
	struct mpsse_context *eeprom = NULL;

	if((eeprom = mpsse_init(I2C, FOUR_HUNDRED_KHZ, MSB)) != NULL && eeprom->open)
	{
		printf("%s initialized at %dHz (I2C)\n", get_description(eeprom), get_clock(eeprom));
	
		/* write the EEPROM start address */	
		start(eeprom);
		write_data(eeprom, WCMD, sizeof(WCMD) - 1);

		if(get_ack(eeprom) == ACK)
		{
			/* Send the EEPROM read command */
			start(eeprom);
			write_data(eeprom, RCMD, sizeof(RCMD) - 1);

			if(get_ack(eeprom) == ACK)
			{
				/* Read in SIZE bytes from the EEPROM chip */
				data = read_data(eeprom, SIZE);
				if(data)
				{
					fp = fopen(FOUT, "wb");
					if(fp)
					{
						fwrite(data, 1, SIZE, fp);
						fclose(fp);

						printf("Dumped %d bytes to %s\n", SIZE, FOUT);
						retval = EXIT_SUCCESS;
					}

					free(data);
				}
	
				/* Tell libmpsse to send NACKs after reading data */
				set_nacks(eeprom);

				/* Read in one dummy byte, with a NACK */
				read_data(eeprom, 1);
			}
		}

		stop(eeprom);
	}
	else
	{
		printf("Failed to initialize MPSSE: %s\n", error_string(eeprom));
	}

	release(eeprom);

	return retval;
}
