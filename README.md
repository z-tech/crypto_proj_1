# crypto_proj_1

Here we crack (a special) poly-alphabetic substitution cipher given ciphertext and some plaintext dictionaries. The cipher cracked is special in that it may insert random characters when ciphering and it may select indices of shift values from the key on a non-sequential schedule.

When making guesses for the plaintext, we're more or less making guesses for four configuration parameters:

1) length of key `t` (guaranteed to be 1-24)
2) shift values at each index of the key `k0...kt-1` (all values in 0-26 inclusive)
3) rule(s) about selecting an index from the key, meaning, the scheduler behavior
4) rule(s) about inserting random characters, also scheduler behavior

It's worth mentioning that a basic approach would tabulate all conceivable rules for 3 & 4 and test each combination with all possible key lengths and key values. This is inefficient, but given infinite time, will result in success (provided all possible rules for 3 & 4 are guessed). Unsurprisingly, we cannot bet on guessing all possible rules for 3 & 4, and additionally we have finite time to execute our crack.

To improve the basic approach just described we have a number of statistical approaches to start with:

A) `index of coincidence` analysis can identify key lengths that result in valid looking English

B) for each key index, `frequency analysis` can identify shift values that produce plaintext with letter frequency that matches our dictionaries

Together, these techniques can give us a long-ish list of initial key guesses. From there we switch gears to fitness analysis:

C) quality of plaintext guesses is estimated through computing `levenshtein distance`

Essentially, we can loop through some number of the long-ish list of initial key guesses and determine a few that look promising by choosing the ones that result in plaintext guesses that are the most similar to entries in the dictionary. Then we switch gears again to stochastic analysis:

D) key guesses can be improved by trial and error through `hill-climbing`

Basically, for a handful of our promising looking key guesses, we can iteratively make a change to the key and compute the fitness. If the fitness of the new key is improved, then we repeat the process, otherwise we go back to the unmodified key and repeat the process with a different modification. What's more cool is we don't have to result to a purely stochastic process because we already computed an ordered list of probable shift values, so we can just try the most probable handful of these.

This will not always result in a perfectly reconstructed plaintext. In particular, there's probably not a lot we can do about random chars being inserted into the ciphertext. Given L=500 we just have to expect 50 or so random char values added and our fitness to be impacted respectively.

When we think about it a little more, we don't need to perfectly reconstruct a plaintext, all we really need is to cross some threshold where there is reasonable confidence that some key similar to the candidate key will result in the correct deciphering of the ciphertext to a plaintext in the dictionary. We have many options for the configuration of this threshold and we're gonna set it at fitness <= 250.

https://eprint.iacr.org/2020/302.pdf

https://www.geeksforgeeks.org/introduction-hill-climbing-artificial-intelligence/
