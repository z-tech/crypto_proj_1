# crypto_proj_1

Here we crack (a special) poly-alphabetic substitution cipher given ciphertext and some plaintext dictionaries. The cipher is special in that it may insert random characters when ciphering and it may select indices of shift values from the key on a non-sequential schedule.

When making guesses for the plaintext, we're more or less making guesses for four configuration parameters:

1) length of key `t` (guaranteed to be 1-24)
2) shift values at each index of the key `k0...kt-1` (all values in 0-26 inclusive)
3) rule(s) about selecting an index from the key, meaning, the scheduler behavior
4) rule(s) about inserting random characters, also scheduler behavior

It's worth mentioning that a basic approach would tabulate all conceivable rules for 3 & 4 and test each combination with all possible key lengths and key values. This is inefficient, but given infinite time, will result in success (provided all possible rules for 3 & 4 are guessed). Unsurprisingly, we cannot bet on guessing all possible rules for 3 & 4, and additionally we have finite time to execute our crack.

To improve the basic approach above we have a number of statistical approaches to start with:

A) `index of coincidence` analysis can identify key lengths that result in valid looking English

B) for each key index, `frequency analysis` can identify shift values that produce plaintext with letter frequency that matches our dictionaries

Together, these techniques can give us a long-ish list of initial key guesses. From there we switch gears to fitness analysis:

C) `levenshtein distance` can identify the fitness (quality) of plaintext guesses

Essentially, we can loop through a handful of the long-ish list of initial key guesses and determine a few that look promising by choosing ones with the smallest levenshtein distance from any dictionary value. Then we switch gears again to local search optimization:

D) `hill climbing` can improve the key guesses we have through trial and error

Basically, for a handful of our promising looking key guesses, we iteratively make a change to the key and compute the fitness. If the fitness of the new key is improved, we repeat the process, otherwise we go back to the unmodified key and repeat the process with a different modification. Something neat about our solution is that we need not result to a purely stochastic process of choosing random modifications, because we already computed a ranked list of probable shift values at each index of promising keys. We can reuse these lists to only hill climb with highly ranked values.

It's important to note that this will not always result in a perfectly reconstructed plaintext. In particular, there's seemingly little to do about random chars being inserted into the ciphertext. Given L=500, we just have to expect 50 or so random char values added and our fitness to be negatively impacted as a consequence.

When we think about it a little more, we don't need to perfectly reconstruct a plaintext. We need only to cross some threshold of fitness where there is reasonable confidence that some configuration using a similar candidate key will result in a particular plaintext from the dictionary. We have many options for the value of this threshold and we're gonna set it conservatively at fitness <= 250.

https://eprint.iacr.org/2020/302.pdf

https://www.geeksforgeeks.org/introduction-hill-climbing-artificial-intelligence/
