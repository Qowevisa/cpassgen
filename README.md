# C Password Generator
Cpassgen is a pure C minimalistic program that will shuffle your input data into something unreadable and irreversible.

# Features
 - One of the key point of using this software is to modify a key of 16 unsigned char before compilation. That key will drasticly change the behaviour of the program. Key, or "code" can be found in ./inc/cpassgen.h. You can change it only before every compilation. There is no "rc" file and program won't even try to behave "randomly". The same input means the same output.
 - You can edit the default length of every password that will be generated by changing "#define DEFAULT\_LENGTH 32" line in ./inc/cpassgen.h file. If you change it to, for example, 16, you can easily get back the password that was generated by adding -32 before them.
 - You can generate a password with different length. For example, by using -1000 before any string will generate hash that will be 1000 characters in length. It is fast so you don't need to worry about it.
 - Everytime I change the version of the algorithm I will increment the first number in version so you can easily get back source and restore needed binary file.

# Builing
Just call make
```
make
```
