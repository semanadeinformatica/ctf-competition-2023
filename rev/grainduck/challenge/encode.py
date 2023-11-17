#!/usr/bin/env python3

from random import shuffle, seed

brainfuck = "><+-.[]"
grainduck = "🌾🌽🦢🦆😗🍞🥖"

with open("./chall.bf", "r") as f:
    code = f.read()

for k, v in zip(brainfuck, grainduck):
    code = code.replace(k, v)

with open("../prompt/ransom", "w") as f:
    f.write(code)
