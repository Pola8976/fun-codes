#!/usr/bin/python3

from termcolor import colored
import sys

INVALID_GUESS = 0
LEN_WORDLE = 5  # default
NUM_GUESSES = 6
GREEN = 2
YELLOW = 1
GREY = 0

box = chr(129033)
unguessed = box * LEN_WORDLE


def clr_line():
    sys.stdout.write("\033[F")
    sys.stdout.write("\033[K")


def pretty_print(guess, guesses_left):
    color = {
        GREEN: "green",
        YELLOW: "yellow",
        GREY: "grey",
    }
    guess = guess.upper()
    sys.stdout.write("\033[s")
    sys.stdout.write("\033[{}A".format(guesses_left))
    sys.stdout.write("\033[K")
    for i in range(LEN_WORDLE):
        print(colored(guess[i], color[result[i]]), end="")
    sys.stdout.write("\0338")


def score(guess, answer):
    if not isinstance(guess, str) or len(guess) != LEN_WORDLE or not guess.isalpha():
        return None, INVALID_GUESS

    result = [GREY] * LEN_WORDLE
    used_up = [False] * LEN_WORDLE
    guess = guess.upper()
    answer = answer.upper()

    for i in range(LEN_WORDLE):
        if guess[i] == answer[i]:
            result[i] = GREEN
            used_up[i] = True

    for i in range(LEN_WORDLE):  # loop through guess
        if result[i]:
            continue
        for j in range(LEN_WORDLE):  # loop through answer
            if used_up[j] == False and guess[i] == answer[j]:
                result[i] = YELLOW
                used_up[j] = True
                break

    return result, None


if __name__ == "__main__":
    answer = input("Enter answer: ")
    if not isinstance(answer, str) or not answer.isalpha():
        sys.exit("Invalid answer")
    LEN_WORDLE = len(answer)

    sys.stdout.write("\033[s")
    sys.stdout.write("\033[1A")
    sys.stdout.write("\033[K")
    print("wordlISH", end="")
    sys.stdout.write("\0338")
    print("\n".join([unguessed] * NUM_GUESSES))

    flag_err = False
    flag_won = False
    guesses_left = NUM_GUESSES
    while guesses_left:
        guess = input("Enter guess: ")
        clr_line()

        if flag_err == True:
            clr_line()
            flag_err = False

        result, err = score(guess, answer)

        if err != None:
            if err == INVALID_GUESS:
                print(colored("Invalid guess!", "red"))
                flag_err = True
            continue

        pretty_print(guess, guesses_left)
        guesses_left -= 1

        if sum(result) == 10:
            flag_won = True
            break

    if not flag_won:
        sys.stdout.write("\033[s")
        sys.stdout.write("\033[{}A".format(NUM_GUESSES + 1))
        sys.stdout.write("\033[K")
        print(colored(answer.upper(), "blue"), "<-- the answer")
        sys.stdout.write("\0338")
