# CS 301 Final Project Log

**November 14, 2026 - Betero Tiikana**

I added the initial input file validation. I am also thinking of keeping `main()` simple and using helpers for the main logic.

Possible helper logics I found from the instructions:

- **“Count the frequencies of each character in the file.”** → one helper could handle reading the file and keeping track of how many times each byte appears.
- **“Construct a Huffman Tree of the frequencies.”** → one helper could take the frequency data and build the Huffman tree.
- **“Create unique prefix codes for each character by assigning 0's to left edges and 1's to right edges.”** → one helper could walk through the tree and create the code for each character.

For input validation, I used `cerr` instead of `cout` for error messages to practice standard C++ convention. [Microsoft's C++ documentation](https://learn.microsoft.com/en-us/cpp/standard-library/cpp-program-startup-and-termination?view=msvc-170) identifies `cerr` as the standard error output stream.
I also opened the input with `std::ios::binary` because the restored file must match the original byte for byte. Binary mode prevents text-mode translation from changing the file contents before compression.

---

**Date — Name**

Add the next log below this line.
