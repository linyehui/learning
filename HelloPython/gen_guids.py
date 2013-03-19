__author__ = 'edenlin'

import uuid

def gen_guids():
    fileHandle = open('guids.txt', 'w')

    for i in range(100):
        fileHandle.write(str(uuid.uuid1()) + '\n')

    fileHandle.close()
if __name__ == "__main__":
    gen_guids()