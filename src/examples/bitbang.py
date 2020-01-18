#!/usr/bin/env python

from mpsse import *
from time import sleep

# Open mpsse in bitbang mode
io = MPSSE(BITBANG);

# Set pin 0 high/low and read back pin 0's state 10 times
for i in range(0, 10):

	io.set_pin_high(0)
	print "Pin 0 is:", io.pin_state(0)
	sleep(1)

	io.set_pin_low(0)
	print "Pin 0 is:", io.pin_state(0)
	sleep(1)

io.Close()
