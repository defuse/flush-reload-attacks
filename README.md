Side Channels In Non-Crypto Software
=====================================

This repository tracks the progress of a 502.04 project about applying the
`FLUSH+RELOAD` side channel to non-cryptographic software. The main goal is to
apply the side channel to a broad class of common programs (text editors, web
browsers, web servers, etc.) and see what security impact the information leaks
have. Secondary goals are to determine how the attack can be applied to
scripting languages (i.e. JavaScript in the browser) and to find out if programs
can defend against this attack in an automated way (i.e. compiler
modifications).

This public repository will contain all of the source code, data, and other work
related to the project (copyright permitting).

Note that although the `FLUSH+RELOAD` attack is very powerful, and will likely
be the core of this research, the project will not be limited to *just* that
attack.

Most of the work will be done by Taylor Hornby, supervised by John Aycock.

Project Status
--------------

Getting started.

Directories
-----------

- `flush-reload`: The `FLUSH+RELOAD` source code provided by the original paper's
  author Yuval Yarom.
- `experiments`: Experiments.

Credit
------

The code in the `flush-reload` was provided by Yuval Yarom, the author of
[FLUSH+RELOAD: a High Resolution, Low Noise, L3 Cache Side-Channel
Attack](https://eprint.iacr.org/2013/448.pdf).
