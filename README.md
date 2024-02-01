# WordCount utility

WordCount utility - counts the number of lines, words, letters and bytes for a specified file and outputs this information to the output stream.

The program supports the following options:

**-l, --lines** output only the number of lines

**-c, --bytes** output file size in bytes

**-w, --words** output the number of words

**-m, --chars** output the number of letters.

The file name and options are passed through command line arguments in the following format:

_**./WordCont [OPTION] filename [filename,.....]**_

Output format (without options specified):
  lines words bytes filename
