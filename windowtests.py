import subprocess
from os import listdir, stat
from os.path import isfile, join

testfiles = [f for f in listdir('testfiles/') if isfile(join('testfiles/', f))]

cummulative = 0
cummulative_enc = 0
for testfile in testfiles:
    filesize = stat('testfiles/{}'.format(testfile)).st_size
    cummulative += filesize
    with open('testfiles/{}'.format(testfile), 'rb') as infile:
        outdata = subprocess.run(['./huffman', '-t', '3', '-c'], stdin=infile, stdout=subprocess.PIPE).stdout
        cummulative_enc += len(outdata)
        print("{} ( = {})- {} -> {}".format(testfile, filesize, len(outdata), len(outdata)/filesize))

print("{} -> {} ({}%)".format(cummulative, cummulative_enc, cummulative_enc/cummulative))
