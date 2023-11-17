INPUT_FILEPATH = 'in.txt'
OUTPUT_FILEPATH = 'flag'
KEY_FILEPATH = 'key.txt'

def binarize(text):
    enc = b''
    for c in text:
        val = 0
        shifts = [64, 4, 2, 16, 1, 8, 32]
        for shift in shifts:
            val = val * 2 + (ord(c) // shift & 1)
        enc += val.to_bytes()
    return enc
        
def combine_key(text, key):
    enc = ''
    for i, c in enumerate(text):
        enc += chr((ord(c) + ord(key[i % len(key)])) % 127)
    return enc

with open(KEY_FILEPATH, 'r') as key_file:
    key = key_file.read()
    assert key.isascii()
    assert len(key) == 11
    
with open(INPUT_FILEPATH, 'r') as input_file:
    text = input_file.read()
    assert text.isascii()

with open(OUTPUT_FILEPATH, 'wb') as output_file:
    output_file.write(binarize(combine_key(text, key)))
