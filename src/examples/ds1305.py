#!/usr/bin/env python

from mpsse import *
from time import sleep

try:
	ds1305 = MPSSE(SPI1, ONE_HUNDRED_KHZ, MSB)

	# The DS1305's chip select pin idles low
	ds1305.set_cs_idle(0)

	print "%s initialized at %dHz (SPI mode 1)" % (ds1305.get_description(), ds1305.get_clock())

	# Get the current control register value
	ds1305.start()
	ds1305.write_data("\x0F")
	control = ord(ds1305.read_data(1))
	ds1305.stop()

	# Clear the EOSC bit (BIT7) to enable the DS1305's oscillator
	control &= ~0x80

	# write the new control value to the control register
	ds1305.start()
	ds1305.write_data("\x8F")
	ds1305.write_data(chr(control))
	ds1305.stop()

	# Loop to print the time elapsed every second
	while True:

		try:	
			sleep(1)

			# Read in the elapsed seconds
			ds1305.start()
			ds1305.write_data("\x00")
			seconds = ord(ds1305.read_data(1))
			ds1305.stop()

			# High 4 bits == tens of seconds, low 4 bits == seconds
			seconds = (((seconds >> 4) * 10) + (seconds & 0x0F))

			# Read in the elapsed minutes
			ds1305.start()
			ds1305.write_data("\x01")
			minutes = ord(ds1305.read_data(1))
			ds1305.stop()	

			# High 4 bits == tens of minutes, low 4 bits == minutes
			minutes = (((minutes >> 4) * 10) + (minutes & 0x0F))

			print "%.2d:%.2d" % (minutes, seconds)
		except KeyboardInterrupt:
			break
			
	ds1305.Close()
except Exception, e:
	print "Error reading from DS1305:", e
