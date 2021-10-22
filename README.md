# C Password Generator
Cpassgen is a pure C minimalistic program that will shuffle your input data into something unreadable and irreversible.

# Feature
One of the key point of using this software is to modify a key of 16 unsigned char before compilation. That key will drasticly change the behaviour of the program. Key, or "code" can be found in ./inc/cpassgen.h. You can change it only before every compilation. There is no "rc" file and program won't even try to behave "randomly". The same input means the same output.
