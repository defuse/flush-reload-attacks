Side-Channel Attacks on Everyday Applications
=============================================

Abstract
-----------------------------

In 2013, Yuval Yarom and Katrina Falkner discovered the FLUSH+RELOAD L3 cache
side-channel. So far it has broken numerous implementations of cryptography
including, notably, the AES and ECDSA in OpenSSL and the RSA GnuPG. Given
FLUSH+RELOAD's astounding success at breaking cryptography, we're lead to wonder
if it can be applied more broadly, to leak useful information out of regular
applications like text editors and web browsers whose main functions are not
cryptography.

In this talk, I'll briefly describe how the FLUSH+RELOAD attack works, and how
it can be used to build input distinguishing attacks. In particular, I'll
demonstrate how when the user Alice browses around the top 100 Wikipedia pages,
the user Bob can spy on which of those pages she's visiting.

This isn't an earth-shattering attack, but as the code I'm releasing shows, it
can be implemented reliably. My goal is to convince the community that side
channels, FLUSH+RELOAD in particular, are useful for more than just breaking
cryptography. The code I'm releasing is a starting point for developing better
attacks. If you have access to a vulnerable CPU running a suitable OS, you
should be able to reproduce the attack within minutes after watching the talk
and downloading the code.

Presentation Outline
-----------------------------

1. (3 minutes) Review of the Flush+Reload side-channel at a high level.
   Flush+Reload is an L3 cache side-channel that lets you place 'probes' on
   cache lines in the code segment of shared binaries, which get 'triggered' any
   time any process on the system loads that line into cache (i.e. the code was
   executed). In effect, you can spy on which code other processes are
   executing.

2. (3 minutes) Technical details of Flush+Reload. It works by flushing those
   lines out of the cache, waiting a little bit, and then checking if they've
   been loaded back into the cache (by timing a read). There'll be a cool
   histogram showing the timing difference between cached and uncached reads.

3. (3 minutes) Flush+Reload has so far been used (really successfully!) to break
   cryptography, but what about non-crypto applications? It's broken (1) The AES
   in OpenSSL, (2) The RSA in GnuPG, (3) The ECDSA in OpenSSL, and lots more.
   It's clearly good at breaking cryptography, but I'll draw attention to the
   fact that cryptography is a sort of low-hanging fruit for side-channel
   attacks. There's a small number of secret bits (the key) and leaking those
   bits is always fatal to security, so it makes sense to invest effort in
   developing attacks that leak those bits. They're the obvious targets. I'll
   hypothesize a bit about what kinds of information Flush+Reload can extract
   from every day apps that don't use cryptography as part of their main
   function, like text editors, web browsers, PDF viewers, chat clients, etc.
   This is to get the audience interested in the possibilities and thinking up
   ideas of their own.

4. (8 minutes) A starting point is input-distinguishing attacks. To distinguish
   between a set of N different inputs to a program you need to learn  bits
   about the input so it should be easy. I implemented an attack against the
   Links command-line web browser, it lets me tell which of the top-100
   Wikipedia pages another user is viewing. The attack will be explained as
   follows. First, we place Flush+Reload probes on HTML parsing code
   (parse_html, html_stack_dup, html_h, and html_span functions), an example of
   what one of these probe hit sequences looks like for one pageview, the
   attacker trains the system by recording 10 samples of each page (either on
   the target system or on their own system which is similar), the attacker
   spies on the victim as they visit one of the pages, then the attacker
   recovers which page was visited (and how that works is explained).

5. (5 minutes) Demo the Links attack: In one terminal logged in as the user
   alice, I'm visiting various top-100 Wikipedia pages in the Links browser. In
   another terminal logged in as the user bob, there's a spy program running.
   Then I start a recovery program on bob's terminal, and a few minutes later
   (filling time by talking about the code/implementation and what it's doing
   right now), we see a list of the URLs Alice visited.

6. (3 minutes) Try this at home! Point the audience to where the code is (on
   GitHub) and how to get started and where contact me for hacking help. Promote
   the idea that there's lots of room for improvement and it would be awesome to
   see new attacks being developed.

Attendee Takeaways
-----------------------------

1. That side-channel attacks aren't only threats to cryptography.
   Non-cryptography parts of regular applications leak information that might be
   valuable on its own or as part of a larger attack.

2. You'll see an example of a general pattern for using the Flush+Reload
   side-channel to distinguish which of a set of known inputs was given to
   a program.

3. The Flush+Reload side-channel attack is very reliable, and the code I'll be
   releasing is the start of a framework for developing attack tools based on
   it. Everyone is welcome to start hacking on it and start constructing better
   attacks.

What's New?
-----------------------------

The novel contributions are:

1. The specific information leak I demo in the talk: an attacker can tell which
   of a set of known web pages was opened in the Links browser.

2. There are two more attacks implemented in the code I'll be releasing. The
   first lets you determine whether the Truecrypt volume that just got mounted
   was a hidden container. The second lets you distinguish which of 127 known
   PDF files just got processed by libpoppler.

3. Release quality code (C) implementing the Flush+Reload attack, and
   a framework (Ruby) that makes it quick and easy to implement
   input-distinguishing attacks and the Truecrypt attack.

4. (Not covered in the talk) Code that implements a technique for
   semi-automatically discovering where to place Flush+Reload probes in order
   for an input-distinguishing attack to work.

There is related work which is similar in that it applies Flush+Reload in
a non-cryptography setting. The paper is called "Cross-Tenant Side-Channel
Attacks in PaaS Clouds" by Yinqian Zhang and Ari Juels. In it, they have three
case studies, one of which is determining how many items are in a user's
shopping cart. The other two case studies involve cryptography. They take a more
formal approach to modeling the attack (using NFAs), whereas I took a more
ad-hoc approach. I make up for this by releasing reliable code anyone should be
able to use to reproduce my experiments.

There is a lot of existing work in using side-channels to attack cryptography,
far too much to mention here. If the reviewers would like a more detailed
bibliography please let me know and it will be provided.


Why Black Hat?
-----------------------------

Originally, I wanted to submit this work to an academic journal. However, Black
Hat's emphasis on releasing code alongside the presentation makes it a more
suitable venue. The audience will be expecting to get code to play with, so by
releasing at Black Hat there's a greater chance that the community will start
developing better attacks. In comparison, if I submit to an academic journal,
the code gets relegated to an appendix in the paper.

The same is true of other security conference venues (like bsides, etc.), so why
Black Hat? Even though the actual attacks I'm presenting aren't incredibly
interesting on their own, they are a starting point for the community to build
on. The people who are best suited to doing that are in the audience at Black
Hat.

Have you presented any version of this talk before?
-----------------------------

If yes, what changes/updates will be made to this presentation? I've only
presented this privately to a research group at the University of Calgary, as
a requirement to get academic credit for the project. In that version of the
presentation, I had to give a lot of background on how CPU cache works, how
side-channels abuse cache timings, etc. At Black Hat I can assume the audience
is already familiar with that so I can focus more on the technical details of my
new attacks.

Message for Review Board Only
-----------------------------

This is joint work with John Aycock and James Sullivan, both from the University
of Calgary. They will be credited on the talk slides and in any written
material.

I put "Cryptography" as the second track since side-channel research is
typically targeted to break cryptography, so my target audience will be paying
attention to that track.

I plan on also submitting an academic paper to USENIX WOOT '16, an academic
conference which is friendly to content also published at Black Hat. In their
CFP proposal they say:

"Note: Work presented at industry conferences, such as Black Hat, is not
considered to have been "previously published" for the purposes of WOOT '16. We
strongly encourage the submission of such work to WOOT '16, particularly work
that is well suited to a more formal and complete treatment in a published,
peer-reviewed setting. In your submission, please do note any previous
presentations of the work."

The Black Hat talk will be more on the practical side, emphasizing that the code
is available, working, and it's ready to be hacked on. The USENIX paper will be
a more formal summary of the work I've done, presenting the results to the
academic community where most of this kind of side-channel research is taking
place. I'll write a separate white paper to accompany the Black Hat talk which
explains the attacks in a way that's more suitable to the Black Hat audience. It
will focus more on low-level details of the attacks and using the code. This way
I get the best of both worlds: the academics working on side channels can think
about the results, and the Black Hat hackers get the code.

If the review board would like access to the code, or to a preprint of the paper
I plan on submitting to USENIX, just ask!
