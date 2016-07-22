Side-Channel Attacks on Everyday Applications
================================================================================

This repository contains the source code and experiment data accompanying Taylor
Hornby's talk at Black Hat 2016 titled "Side-Channel Attacks on Everyday
Applications."

- `cpsc502`: Assignments for my undergraduate research project at the University
  of Calgary.
- `experiments`: Experiment implementations and all saved experiment run data.
- `flush-reload`: Attack tools, including:
    - `original-from-authors`: The original authors' implementaiton of
      Flush+Reload.
    - `myversion`: My rewrite of the Flush+Reload attack tool. The Ruby attack
      tools and automated probe finding tools are in `myversion/ruby`.
    - `cachebench`: A tool for timing the difference between cached and
      non-cached memory accesses.
    - `rdtsc-consistency`: A tool to check if the RDTSC timestamp behaves
      monotonically.
- `paper`: The LaTeX source code to the accompanying paper.
- `source`: Source files, e.g. the PDF files for the libpoppler input
  distinguishing attack.

Contributing
------------

Pull requests to this repository are welcome, although I have very limited time
to review and merge them. Feel free to fork this project if I'm taking too long!

Acknowledgements
----------------

The code directly inside the `flush-reload` folder was provided by Yuval Yarom,
one of the authors of [FLUSH+RELOAD: a High Resolution, Low Noise, L3 Cache
Side-Channel Attack](https://eprint.iacr.org/2013/448.pdf). The code inside
`flush-reload/myversion` is a complete re-write, based on the original code.

I would like to thank Prof. John Aycock at the University of Calgary for serving
as my advisor when I was working on this project for my undergrad thesis. Our
discussions helped lead me to the results included here. He also contributed
edits and improvements to an earlier version of the paper.
