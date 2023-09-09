#!/usr/bin/python

import string
import random
import sys


def rnd_small_letter() -> str:
    return random.choice(string.ascii_lowercase)


def build_word(word_len: int) -> str:
    word = ''
    for i in range(word_len):
        word += rnd_small_letter()
    return word


def gen_file(word_len: int, entries: int) -> None:
    with open(f'random_{entries}_passes_len_{word_len}.txt', 'wt') as f:
        for i in range(entries):
            entry = build_word(word_len) + '\n'
            f.write(entry)
            print(f'Generated entry nr {i}\n')


def main():
    word_len = int(sys.argv[1])
    entries = int(sys.argv[2])
    gen_file(word_len, entries)


if __name__ == '__main__':
    main()
