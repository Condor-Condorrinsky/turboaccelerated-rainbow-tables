#!/usr/bin/python

import string
import random
import sys

GEN_PIN = 'pin'
GEN_ALPHA = 'alpha'
GEN_ASCII = 'ascii'

ALPHANUM = string.digits + string.ascii_uppercase + string.ascii_lowercase
# Without space and |
ASCII_PRINTABLE = '!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{}~'


def rnd_digit() -> str:
    return random.choice(string.digits)


def rnd_alphanumeric() -> str:
    return random.choice(ALPHANUM)


def rnd_ascii() -> str:
    return random.choice(ASCII_PRINTABLE)


def build_word(word_len: int, mode: str) -> str:
    word = ''
    if mode == GEN_PIN:
        for i in range(word_len):
            word += rnd_digit()
    elif mode == GEN_ALPHA:
        for i in range(word_len):
            word += rnd_alphanumeric()
    elif mode == GEN_ASCII:
        for i in range(word_len):
            word += rnd_ascii()
    return word


def gen_file(word_len: int, entries: int, mode: str) -> None:
    if mode == GEN_PIN:
        with open(f'random_{entries}_pins_len_{word_len}.txt', 'wt') as f:
            for i in range(entries):
                entry = build_word(word_len, mode) + '\n'
                f.write(entry)
                print(f'Generated PIN nr {i}')
    elif mode == GEN_ALPHA:
        with open(f'random_{entries}_alphanum_passes_len_{word_len}.txt', 'wt') as f:
            for i in range(entries):
                entry = build_word(word_len, mode) + '\n'
                f.write(entry)
                print(f'Generated alphanumeric password nr {i}')
    elif mode == GEN_ASCII:
        with open(f'random_{entries}_ascii_passes_len_{word_len}.txt', 'wt') as f:
            for i in range(entries):
                entry = build_word(word_len, mode) + '\n'
                f.write(entry)
                print(f'Generated ascii password nr {i}')
    else:
        print(f"Unrecognized option {mode}, exiting!")


def main():
    mode = sys.argv[1]
    word_len = int(sys.argv[2])
    entries = int(sys.argv[3])
    gen_file(word_len, entries, mode)


if __name__ == '__main__':
    main()
