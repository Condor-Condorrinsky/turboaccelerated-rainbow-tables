#!/usr/bin/python

import string
import random
import sys

WORD_MIN_LEN = 4
FILE_ENTRIES = 10_000_000


def rnd_small_letter() -> str:
    return random.choice(string.ascii_lowercase)


def build_word(max_len: int) -> str:
    word = ''
    length = random.randint(WORD_MIN_LEN, max_len)
    for i in range(length):
        word += rnd_small_letter()
    return word


def gen_file(max_word_len: int) -> None:
    with open('random_passes_10_000_000.txt', 'wt') as f:
        for i in range(FILE_ENTRIES):
            entry = build_word(max_word_len) + '\n'
            f.write(entry)
            print(f'Generated entry nr {i}\n')


def main():
    word_max_len = int(sys.argv[1])
    gen_file(word_max_len)


if __name__ == '__main__':
    main()
