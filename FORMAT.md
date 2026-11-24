# FORMAT.md: team agreement for the .zip301 format

> Rule: if the official ZIP301 page says something different from this file, the ZIP301 page wins. Fix this file to match it.

## 1. Shared function (A gives this to B)

```cpp
// huffman.h
#pragma once
#include <string>
#include <vector>

// Index with (unsigned char). codes[c] is the bit string for byte c,
// e.g. "0110". An empty string means c never appears in the text.
std::vector<std::string> buildCodes(const std::string& text);
```

- Treat every character as an **unsigned char (0 to 255)**, so UTF-8 or odd characters still work.
- Only B calls `buildCodes`. C does NOT need `huffman.h`, because C rebuilds the codes by reading the file header.

## 2. Overall file layout

```
<code line>\n
<code line>\n
...
*****\n
<bit count as decimal text>\n
<raw bytes of the encoded bits>
```

## 3. Code lines

Each line is: `<token> <code>`

- One space between the token and the code.
- The code is text `0`s and `1`s.
- The token is how we write the character. A token never contains a raw space or newline, so the decompressor can split each line at the first space.

| Character | Token |
|---|---|
| Normal printable char (`!` to `~`), except backslash | the char itself, e.g. `a 0110` |
| Space | `\s` |
| Newline (byte 10) | `\n` |
| Carriage return (byte 13) | `\r` |
| Tab (byte 9) | `\t` |
| Backslash `\` | `\\` |
| Any other byte (below 32 or above 126) | `\xHH`, two hex digits, e.g. `\x0B` |

Order of lines does not matter, because C reads them all into a map.

## 4. After the codes

1. Write the line `*****`.
2. Write the total number of bits as a plain decimal number, then `\n`.
3. Write the encoded bits as raw bytes.
   - Pack bits from the **most significant bit first**. The first bit of the text goes into bit 7 of the first byte.
   - If the last byte is not full, pad with `0`s.

Why the bit count matters: the padding zeros look just like real data. The bit count tells C where to stop reading, so C doesn't invent extra characters at the end.

## 5. Edge cases

| Case | What B writes | What C does |
|---|---|---|
| Empty file | no code lines, then `*****`, `0`, and no data bytes | creates an empty output file |
| One unique character (e.g. `aaaa`) | give that char the code `0`; bit count = number of chars | each `0` bit decodes to that char |

## 6. Rules for everyone

- Open **every** file in binary mode: `std::ios::binary`. Otherwise Windows changes `\r\n` and the byte-for-byte match breaks.
- Read the whole input file as bytes. Do not use `>>`, because it skips whitespace.
- C reading tip: read the header with `getline` until the `*****` line, then read the bit count line, then switch to raw byte reading. Do not use `getline` on the binary part.
- Input `name.txt` -> compressed `name.zip301` -> restored `name2.txt`.

## 7. Testing

C writes a script that compresses then decompresses a file and compares the original and restored files. Test at least: an empty file, `aaaa`, a file with newlines and tabs, and `gulliver.txt`.
