#!/usr/bin/env python

import sys
import random

def usage():
	print '''usage: %s output_filename no_of_integers random_seed ''' %(sys.argv[0])

MAXINT=sys.maxint

if __name__ == "__main__":    
	if len(sys.argv) != 4:
		usage()
		sys.exit(1)
	
	outfile = open(sys.argv[1], 'w')
	num_int = int(sys.argv[2])
	seed = int(sys.argv[3])
	
	random.seed(seed)
	
	outfile.write("%d" %num_int)
	for i in xrange(num_int):
		outfile.write("\n")
		outfile.write("%d" %random.randint(0, MAXINT))
	outfile.close()

	sys.stderr.write("done.\n")
