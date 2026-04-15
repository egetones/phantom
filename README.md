<div align="center">

# Phantom

![C](https://img.shields.io/badge/Language-C-blue?style=flat&logo=c)
![License](https://img.shields.io/badge/License-MIT-green)
![Technique](https://img.shields.io/badge/Technique-Rootkit_Hooking-red)

<p>
  <strong>A User-land Rootkit PoC using LD_PRELOAD to hide processes from system tools.</strong>
</p>

[Report Bug](https://github.com/egetones/phantom/issues) · [Request Feature](https://github.com/egetones/phantom/issues)

</div>

---

## Description

**Phantom** is a cybersecurity proof-of-concept tool demonstrating how **Function Hooking** works on Linux systems.

By utilizing the `LD_PRELOAD` environment variable, Phantom intercepts calls to the `readdir()` system function. This allows it to filter out specific process names from tools like `top`, `ps`, and `ls`, effectively making a running process "invisible" to the user, even though it continues to execute in the background.

### Key Concepts

  **Function Hooking:** Overriding standard C library functions with custom logic.
  **Shared Libraries:** Compiling code into `.so` (Shared Object) files for injection.
  **Defense Evasion:** Understanding how malware hides artifacts from forensic analysis.

---

## Usage

### 1. Compile
```bash
make
```
*This will generate the `phantom.so` library file.*

### 2. The "Magic" Trick

**Step A: Create a Target Process**
Open a terminal and run a command that lasts a long time (e.g., ping):
```bash
ping google.com
```
*Let this run in the background or a separate terminal.*

**Step B: Verify Visibility (Normal)**
In a new terminal, check if you can see the process:
```bash
ps aux | grep ping
```
*You will see the process listed.*

**Step C: Activate Phantom (Hide it)**
Now, run the same command but inject Phantom:
```bash
LD_PRELOAD=./phantom.so ps aux | grep ping
```
*Result: The output will be empty (or only show the grep color), even though ping is still running!*

You can also use it with `top`:
```bash
LD_PRELOAD=./phantom.so top
```

---

## ⚠️ Disclaimer

**This tool is for educational purposes only.** It is designed to help security professionals and students understand rootkit techniques and defense evasion. Hiding processes on a system you do not own is illegal and unethical.

---

## License

Distributed under the MIT License. See `LICENSE` for more information.
