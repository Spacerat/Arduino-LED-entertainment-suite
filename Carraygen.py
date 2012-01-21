#!/usr/bin/python

import sys
import binascii

end = False

while (not end):
	s = sys.stdin.readline()
	if len(s) == 0:
		end = True
	else:
		name = s[:-1]
		if len(name) > 0:
			# New pattern!
			sys.stdout.write("const uint8_t _%s[8] = {\n" % name)
			for x in range(8):
				binstr = sys.stdin.readline()[:-1]
				sys.stdout.write("\t0x%s" % binascii.hexlify(chr(int(binstr, 2))))
				if x < 7:
					sys.stdout.write(",")
				else:
					sys.stdout.write(" ")
				sys.stdout.write(" //%s \n" % binstr)
			sys.stdout.write("};\n\n")
