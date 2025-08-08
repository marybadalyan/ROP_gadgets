# ROP Demo

This project demonstrates a classic **Return-Oriented Programming (ROP)** exploit on a simple vulnerable C program. It shows how a buffer overflow vulnerability can be exploited to hijack program control flow and execute arbitrary functions (like spawning a shell) by chaining gadgets.

---

## Overview

* A vulnerable C program (`main.cpp`) contains a **stack buffer overflow** in a function that uses `scanf()` (unsafe input).
* The binary is compiled **without stack protection** and **without PIE** to make exploitation easier.
* An exploit script (`exploit.py`) crafts a **ROP chain** that:

  * Overflows the buffer
  * Overwrites the return address with gadgets
  * Sets up the stack to call `system("/bin/sh")`
* Running the exploit spawns an interactive shell without injecting any shellcode.

---

## Files

| File         | Description                               |
| ------------ | ----------------------------------------- |
| `main.cpp`     | Vulnerable C program with buffer overflow |
| `exploit.py` | Python script using `pwntools` to exploit |

---


## Compilation using CMake

Build the vulnerable binary with:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

```bash
cmake --build build --config Release
```
---

## Running the Exploit

Run the exploit script:

```bash
python3 exploit.py
```

If successful, you will get an interactive shell prompt:

```bash
$ whoami
$ ls
```

---

## How It Works

1. The vulnerable program reads input into a fixed-size buffer without bounds checking.
2. Excess input overwrites the saved return address on the stack.
3. The exploit crafts a payload that:

   * Overflows the buffer
   * Sets the return address to a **`pop rdi; ret`** gadget (to set the first argument)
   * Places the address of `"/bin/sh"` string
   * Calls the `system()` function with the argument `"/bin/sh"`
4. This causes the program to execute `system("/bin/sh")` and spawn a shell.

---

## Notes

* This project is for **educational purposes only**.
* Do **not** use these techniques on unauthorized systems.
* Modern systems use protections (ASLR, stack canaries, NX, PIE) that prevent this simple exploit.
* Learning ROP helps understand how low-level exploits work and how mitigations defend against them.

---

## Troubleshooting

* Ensure ASLR is disabled for consistent addresses.
* Verify addresses of gadgets and libc symbols may change between systems.
* Use debugging tools like `gdb` or `pwntools` to inspect memory and confirm gadget locations.

---