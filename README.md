# The Community OS
## Vision:
We want to have a ton of random people come together and make their own individual contributions to a barebones operating system. Our goal is to have an OS that is fully custom built from scratch that can boot on an x86 machine. Any contributions or advice is greatly appreciated! 

## How to Contribute:
There are several ways you can contribute:
- Give us ideas for the name and logo [here](https://forms.gle/33wz1AsVEKife6pB8)
- Give us feedback [here](https://forms.gle/3aL4FJqvc8MZaJJv5)
- Fix a typo or add better wording
- Improve documentation
- Add a new feature
- Improve or optimize code
- Clean up code
- Format code and comments
- Tell others about the project

You can apply your contributions to the main project in two ways:
- https://codeshare.io/aybXqo
- Fork the repo, make a change, and submit a PR

If you contribute at all in any way to the project, please add your name to the list in the README or main.c file. I highly recommend using Github to make changes as codeshare is difficult to work on multiple files and is very disorganized at the moment. I would like to make codeshare more of a note and planning page as well as a place to gather names rather than a place where we are actually working on code to improve effeciency.

## TO-DO
- Create a command system
- Implement shell
- Implement shell navigation via arrow keys
- Remove Profanity

## Needed Jobs
- Dedicated tester: Must have a Linux machine or Linux VM running x86 to build the lastest version of the OS and distribute it on the website.

## Roadmap
- Dynamic Memory Management
- Shell
   - With a basic command system
- Storage management/Filesystem
- Internet Access
- Package Manager
- First Official Release

# How do I compile and run this project?

**NOTE: THESE INSTRUCTIONS ARE TARGETING LINUX BASED SYSTEMS, IF YOU DON'T USE LINUX THEN INSTALL LINUX ON A VIRTUAL MACHINE TO FOLLOW THESE**

### Step 1 - Install required build tools
I am using Ubuntu for this guide, the following command will install the required tools on any Ubuntu based distro

`sudo apt install build-essential binutils nasm clang qemu-system-x86`

This installs:
 - NASM (for assembling the bootloader)
 - LD (the GNU linker for linking the code into one image)
 - Clang (for compiling the C code)
 - GCC (backup compiler, same use as Clang)
 - Make (for automating all the commands needed)
 - QEMU (emulator, for testing the OS)

If you are not using an Ubuntu based distro then use any equivalent command for your distro's package manager, these tools should be easily available for all distros.

### Step 2 - Building the OS
This process will work on any Linux distro as long as you have the previously stated dependencies installed

There are 2 commands you can use for this:

`make all` - This produces an os.img file

`make run` - This produces an os.img file (like the make all command) but it also runs the img file in qemu so you can test it out.

# Other details

## Contact
elroylilly@gmail.com for any questions
If you want a pre-built Image email us

Also, you can join the community slack [here](https://join.slack.com/t/communtiyos/shared_invite/zt-3t3iltj77-5JTo~dkpCm44tZcyA0Or_w)
## Pictures

<img width="1920" height="1080" alt="theosbooted" src="https://github.com/user-attachments/assets/498e0981-27eb-4e7d-a306-26bc7ed75c6f" />

## Contributors: 
- **Ember2819** (Founder & Manager)
- Sifi11 (Founder)
- Crim (OG)
- CheeseFunnel23 (was cooking RIP)
- **bonk enjoyer/dorito girl** (Bootloader Creator) **ABSOLUTE LEGEND**
- KaleidoscopeOld5841 (Uses Arch BTW)
- billythemoon (main website creator)
- TheGirl790 (OG)
- kotofyt
- xtn59
- c-bass
- u/EastConsequence3792
- MorganPG1 (added build instructions to readme)
- Zorx555
