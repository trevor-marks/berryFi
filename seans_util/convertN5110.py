#!/usr/bin/python

"""Converts images for use on a Nokia 5110 Graphic LCD"""

__author__ = "Sean DeArras"
__copyright__ = "Copyright 2014"
__license__ = "GPL"
__version__ = "1.0"
__date__ = "2014/6/4"

import sys
from optparse import OptionParser
import Image
import PIL.ImageOps

parser = OptionParser()
parser.add_option("-i", "--input", dest="input_file",
                  help="Image file to convert", metavar="FILE")
parser.add_option("-o", "--output", dest="output_file",
                  help="File to save to", metavar="FILE")
parser.add_option("-r", "--resize", action="store_true", dest="resize",
                  help="Auto resize image to screen size maintaining ratio", default=False)
parser.add_option("-x", "--invert-color", action="store_true", dest="invert_color",
                  help="Invert image", default=False)
parser.add_option("-v", "--verbose", action="store_true", dest="verbose",
                  help="Output to console", default=False)
parser.add_option("-d", "--display", action="store_true", dest="display",
                  help="Display image", default=False)

(options, args) = parser.parse_args()

if options.input_file == None:
	print ("You need to specify the input file with \'-i\'! Use '-h' for help.")
	sys.exit(1)

inName = options.input_file[0:options.input_file.find('.')]

img = Image.open(options.input_file)
w,h = img.size
if options.resize:
	if (w*48)/h <=84:
		img = img.resize((int((w*48)/h),48), Image.ANTIALIAS)
	elif (h*84)/w <=48:
		img = img.resize((84,int((h*84)/w)), Image.ANTIALIAS)
img = img.convert('L')
if not options.invert_color:
	img = PIL.ImageOps.invert(img)
img = img.convert('1')
w,h = img.size

if h%8:
	hNew = (h|7) + 1
else:
	hNew = h

imgNew = Image.new('1', (w,hNew), "black")
imgNew.paste(img, (0,0,w,h))

if options.display:
	imgInv = imgNew.convert('L')
	imgInv = PIL.ImageOps.invert(imgInv)
	imgInv = imgInv.convert('1')
	imgInv.show()

pxl = imgNew.load()
out = []

for y in range(0,hNew,8):
	for x in range(0,w):
		out.append(hex((((0,1)[pxl[x,y+7]>0])<<7)+(((0,1)[pxl[x,y+6]>0])<<6)+(((0,1)[pxl[x,y+5]>0])<<5)+(((0,1)[pxl[x,y+4]>0])<<4)+(((0,1)[pxl[x,y+3]>0])<<3)+(((0,1)[pxl[x,y+2]>0])<<2)+(((0,1)[pxl[x,y+1]>0])<<1)+((0,1)[pxl[x,y]>0])))

main_string = "//Original Size: " + str(w) + ", " + str(h)
main_string += "\n//Actual Size: " + str(w) + ", " + str(hNew)
main_string += "\nconst static unsigned char " + inName + "[] = {\n  "
main_string += ',\n  '.join(out)
main_string += "\n};"

if options.verbose:
	print (main_string)

if options.output_file != None:
	out_file = open(options.output_file, "w")
	out_file.write(main_string)
	out_file.close()

