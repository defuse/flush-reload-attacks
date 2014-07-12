Brainstorming
=============

Offense
-------

- Might as well look for crypto side channels too, will probably end up finding
  them by accident.

- Get FLUSH+RELOAD to work on AMD processors.

- What is *theoretically* possible, assuming the attacker gets perfect knowledge
  of all branches?
    - Automate the process of finding out what an attacker could learn.
    - This is more important for evaluating defenses.

- Attack programs of different kinds:
    - Compression (tar, gzip, bzip, 7z, zip, etc.)
    - SSH (the crypto parts as well as non-crypto parts).
        - Server
        - Client
    - Web server, mail server, DNS server, FTP server
    - Web browsers and their extensions (look at Cryptocat).


- Scripting languages?
    - Python / Ruby run on the command line.
    - JavaScript in the browser (different browsers).
    - JVM?

- Virtual machines
    - Probe the virtual machine software itself, might reveal a lot of
      information about what another user's VM is doing.
    - In the case of Bochs, which implements all instructions with C++ code, you
      can probably see every instruction the VM executes.
    - In the case of VirtualBox / VMware, anything that's still implemented in
      software (Try disabling VT-X and AMD-V).

Defense
-------

- Disable code sharing between processes.
    - How do you do it?
    - What's the performance impact?

- Change the compiler to make programs (or parts of them) immune.
