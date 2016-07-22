Getting Started Guide
=====================

This guide will get you going with the attack code in this repository. It
assumes you're running Debian 8 Jessie, so if you're running a different variant
of Linux, you'll have to be smart and adapt the guide to work for you.

If you have run into any problems following this guide, please [open an issue on
GitHub](https://github.com/defuse/flush-reload-attacks/issues).

Installing the Dependencies
---------------------------

To get the attack tools and experiment scripts to work, you'll need to install
all of this stuff first:

```
apt-get install build-essential libelf libelf-dev ruby
```

And the ruby gems:

```
gem install levenshtein-ffi
gem install parallel
gem install gnuplot
gem install colorize
gem install graphviz
```

For your reference, the versions of the dependencies we tested are:

```
$ ruby -v
ruby 2.1.5p273 (2014-11-13) [x86_64-linux-gnu]
```

```
$ gem list

*** LOCAL GEMS ***

...
levenshtein-ffi (1.1.0)
parallel (1.6.1)
...
```

Attacking the Links Web Browser
-------------------------------

Automatically Re-discovering the Links Probes
---------------------------------------------

