# crypto_proj_1

In this exercise, we work toward cracking the poly-alphabetic substitution cipher given ciphertext and some plaintext dictionaries. Our cipher is special in that it may insert random characters when ciphering and it may select indices of shift values from the key on a non-linear schedule.

When making guesses for the plaintext, we're more or less making guesses for four configuration parameters:

1) length of key `t` (guaranteed to be 1-24)
2) shift values at each index of the key `k0...kt-1` (all values in 0-26 inclusive)
3) rule(s) about selecting an index from the key to shift at iteration i used by the scheduler
4) rule(s) about inserting random characters used by the scheduler

An inefficient approach might involve simply tabulating all conceivable rules for 3 & 4 and testing each combination with all key lengths and key values. Given infinite time, this will likely yield success. Unfortunately, we're given limited time to perform our crack.

We have a number of options to improve the quality of our guesses. We will categorize these options into (a) linguistic analysis and (b) fitness analysis (though there's somewhat of an overlap):

a1) `index of coincidence` can be used to identify what key lengths are comparatively more likely
a2) for each guess of a key length `frequency analysis` can surface what shift values are more likely
b1) for a given configuration and ciphertext, the `fitness` of the guessed plaintext can be defined as how "close" it resembles any of the members of the dictionary or English language in general. When guess n is "more fit" than guess n-1, we might infer that we've "done something right". This allows for a stochastic approach


https://eprint.iacr.org/2020/302.pdf

https://www.geeksforgeeks.org/introduction-hill-climbing-artificial-intelligence/
