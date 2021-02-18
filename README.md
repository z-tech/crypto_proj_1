# crypto_proj_1

Here we crack (a special) poly-alphabetic substitution cipher given ciphertext and some plaintext dictionaries. The cipher cracked is special in that it may insert random characters when ciphering and it may select indices of shift values from the key on a non-sequential schedule.

When making guesses for the plaintext, we're more or less making guesses for four configuration parameters:

1) length of key `t` (guaranteed to be 1-24)
2) shift values at each index of the key `k0...kt-1` (all values in 0-26 inclusive)
3) rule(s) about selecting an index from the key, meaning, the scheduler behavior
4) rule(s) about inserting random characters, also scheduler behavior

It's worth noting that in a basic approach might tabulate all conceivable rules for 3 & 4 and test each combination with all key lengths and key values. This is inefficient, but given infinite time, will result in success (provided all possible rules for 3 & 4 are guessed). Unsurprisingly, we cannot bet on guessing all possible rules for 3 & 4, and additionally we have finite time to execute our crack.

To improve the basic approach just described we have a number of statistical approaches to start with:
A) `index of coincidence` analysis can identify probable key lengths
B) for each key index, `frequency analysis` can identify probable shift values
C) if ciphertext is longer than dictionary plaintext, random chars were added

Together, these techniques can give us a long-ish list of initial key guesses. From there we switch gears to fitness analysis:

D) quality of plaintext guesses is estimated through computing `levenshtein distance`

Essentially, we can loop through the long-ish list of initial key guesses and determine a few that look promising by choosing the ones that result in plaintext guesses that are the most similar to entries in the dictionary. Then we switch gears again to stochastic analysis:

E) key guesses can be improved by trial and error through `hill-climbing`

Basically, for a handful of our promising looking key guesses, we can iteratively make a change to the key and compute the fitness. If the fitness of the new key is improved, then we repeat the process, otherwise we go back to the unmodified key and repeat the process with a different modification.

We could perform this process until we perfectly compute some key that results in a valid plaintext, but all we really need is to cross some threshold where there is reasonable confidence that some key similar to the candidate key will result in the correct deciphering of the ciphertext to a plaintext in the dictionary.

https://eprint.iacr.org/2020/302.pdf

https://www.geeksforgeeks.org/introduction-hill-climbing-artificial-intelligence/
