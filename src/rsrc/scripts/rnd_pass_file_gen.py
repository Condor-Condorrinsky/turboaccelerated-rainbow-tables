#!/usr/bin/python

import string
import random
import sys

GEN_PASS = 'pass'
GEN_PIN = 'pin'


def rnd_small_letter() -> str:
    return random.choice(string.ascii_lowercase)


def rnd_digit() -> str:
    return random.choice(string.digits)


def build_word(word_len: int) -> str:
    word = ''
    for i in range(word_len):
        word += rnd_small_letter()
    return word


def build_pin(pin_len: int) -> str:
    pin = ''
    for i in range(pin_len):
        pin += rnd_digit()
    return pin


def gen_file(word_len: int, entries: int, mode: str) -> None:
    if mode == GEN_PASS:
        with open(f'random_{entries}_passes_len_{word_len}.txt', 'wt') as f:
            for i in range(entries):
                entry = build_word(word_len) + '\n'
                f.write(entry)
                print(f'Generated password nr {i}')
    elif mode == GEN_PIN:
        with open(f'random_{entries}_pins_len_{word_len}.txt', 'wt') as f:
            for i in range(entries):
                entry = build_pin(word_len) + '\n'
                f.write(entry)
                print(f'Generated PIN nr {i}')
    else:
        print(f"Unrecognized option {mode}, exiting!")


def main():
    mode = sys.argv[1]
    word_len = int(sys.argv[2])
    entries = int(sys.argv[3])
    gen_file(word_len, entries, mode)


if __name__ == '__main__':
    main()
