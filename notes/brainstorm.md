Brainstorming
=============

Offense
-------

- Might as well look for crypto side channels too, will probably end up finding
  them by accident.

- Get FLUSH+RELOAD to work on AMD processors.

- Attack a PDF renderer. Seems like a good case where FLUSH+RELOAD could hook
  some of the rendering functions and learn what the PDF looks like (font
  loading, etc).

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
    - Shells (bash, zsh, etc.)
    - Standard system utilities (ls, cat, dd, etc.)

- Scripting languages?
    - Python / Ruby run on the command line.
    - JavaScript in the browser (different browsers).
    - JVM?

- Get FLUSH+RELOAD working on Windows.

- Virtual machines
    - Probe the virtual machine software itself, might reveal a lot of
      information about what another user's VM is doing.
    - In the case of Bochs, which implements all instructions with C++ code, you
      can probably see every instruction the VM executes.
    - In the case of VirtualBox / VMware, anything that's still implemented in
      software (Try disabling VT-X and AMD-V).

- Evaluate the *actual* limitations of FLUSH+RELOAD.
    - What is the actual granularity, e.g. cache lines?
    - Where exactly does the noise come from, etc.

- Password strength checkers.
    - zxcvbn

- Bitcoin? Other cryptocurrencies?
    - Especially mining, e.g. find out when someone in another AWS instance has
      won a block?

- Qubes OS?

- Databases! (Indexes, extract *data*, etc.)
    - http://patshaughnessy.net/2014/10/13/following-a-select-statement-through-postgres-internals

- Note that we don't actually have to get detailed information about
  keys-pressed when observing typed text. Just the timings might be enough.

Defense
-------

- Use the side channel as a defense mechanism itself. For example, use it to
  detect ROP. Make a side-channel profile of a process, then look for deviations
  in that profile.

- Disable code sharing between processes.
    - How do you do it?
    - What's the performance impact?

- Change the compiler to make programs (or parts of them) immune.

Random Cool Stuff
-----------------

- Build a "SideChat" obscure messaging system that lets one user communicate
  with another (pass messages back and forth) through the FLUSH+RELOAD side
  channel. Use a lot of error correction so that it's reliable.
