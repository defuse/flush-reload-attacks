Getting Started Guide
=====================

This guide will get you going with the attack code in this repository. It
assumes you're running Debian 8 Jessie, so if you're running a different variant
of Linux, you'll have to be smart and adapt the guide to work for you.

If you have run into any problems following this guide, please [open an issue on
GitHub](https://github.com/defuse/flush-reload-attacks/issues).

For best results, follow this guide on dedicated hardware. It might not work
very well in a virtual machine; I know that it doesn't work on the cheaper
Amazon EC2 instances because of the way they allocate CPU time.

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
$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/4.9/lto-wrapper
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Debian 4.9.2-10' --with-bugurl=file:///usr/share/doc/gcc-4.9/README.Bugs --enable-languages=c,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-4.9 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.9 --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-4.9-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-4.9-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-4.9-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --with-arch-32=i586 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 4.9.2 (Debian 4.9.2-10)
```

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

### 1. Build Links from Source

We need a copy of the Links binary with symbols. The one in the debian
repositories doesn't include symbols, so we have to build it from source. Follow
these steps to do that.

(If you're using Debian 8 Jessie, you might be able to skip this step and the
next one by using the binary that's included at
`experiments/links/binaries/links-debian` and the probe addresses in the file
`experiments/links/binaries/links-debian.probes`).

**1.1. Download Links Source Code**

**1.2. Copy the Links Binary**

### 2. Find the Probe Addresses

**2.1. Run the Probe Address Finding Tool**

**2.2. Save the Probe Addresses to a File**

### 3. Run the Experiment

To check if the attacks will work on your system, run the automated experiment.

**3.1. Set the Experiment Parameters**

Go into `experiments/links` and edit the `LinksExperiment.rb` file. This file
defines all of the parameters for an experiment run.

Find the `RUN_BINARY` line and change the path to the Links binary you built in
Step 1 above. If you've been following along exactly, this will be
`binaries/links-demo`.

Find the `PROBES_PATH` line and change the path to the probe addresses file that
you created in Step 2.2 above. If you've been following along exactly, this will
be `binaries/links-demo.probes`.

**3.2. Run the Experiment**

To run the experiment, just run (from within `experiments/links`):

```
$ ./experiment.sh
```

The experiment starts with a training phase. You'll see it taking samples of all
the URLs. After that phase finishes, it will start testing the success rate of
the attack by having a victim visit each of the pages and trying to identify
which page it was. At the end, you'll see the overall success rate of the
attack.

**3.3. Try Different Experiment Parameters**

By default, the experiment runs using just the top 10 Wikipedia pages, taking
5 training samples of each page, and has the victim visit each page 10 times.
This is good for quickly testing if the attack works on your system. If you'd
like to run a longer and more complete experiment, then change `URL_LIST_FILE`,
`SAMPLE_COUNT`, and `VICTIM_RUNS` accordingly.

### 4. Step-by-Step Attack

If the experiment worked for you, then you can try running an attack against
yourself. This will show you what it's like to use the attack tools to actually
spy on somebody.

**4.1. Start the Spy Tool**

**4.2. Pretend to be the Victim**

Automatically Rediscovering the Links Probes
--------------------------------------------

I've already found good probe locations for distinguishing between web pages
visited in Links. But, as a demonstration, you can see how these probes can be
automatically discovered with a bit of human help.

**TODO**
