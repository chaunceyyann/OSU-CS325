#!/usr/bin/env python
#**********************************************************
 #Name: Molly Arwood
 #Term: Winter 2017
 #Class: CS_344 Operating Systems
 #mypython.py
#**********************************************************

import sys, getopt

def main(argv):

	inputfile = ''
	line1 = []

	#check argument usage
	if len(sys.argv) != 2:
		print 'Usage: {} instance_file\n'.format(sys.argv[0])
		exit(2)

	#get filename and read in file
	inputfile = sys.argv[1]
	ifs = open('{0}'.format(inputfile), "r")
	for line in ifs:
		line1.append(line.split())
#		print '{0}'.format(line.split())
	

	#create mst from input coordinates




	#write to output file
	outputfile = inputfile + '.tour'
	ofs = open('{0}'.format(outputfile), "w+")


	#close files
	ifs.close()
	ofs.close()

if __name__ == "__main__":
	main(sys.argv[1:])
