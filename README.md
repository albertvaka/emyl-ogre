Emyl Makes You Listen
=====================

Library description
-------------------

Emyl (acronym for Emyl Makes You Listen) is a C++ sound library that abstracts the usage of OpenAL and libOgg.

It provides the classes `emyl::sound` and `emyl::stream` (for longer audio files, like music) with methods like `Load(filename)` or `Play()` that transparently use OpenAL without having to worry about managing buffers and sources.

This library is meant to be included directly in your project code and be statically linked.


This fork
---------

This fork mainly adds two functionalities to Emyl:

 * Loading files not only from disk but also from Ogre resurces, to integrate seamlessly with Ogre-based games.
 
 * Multithreading capabilities using Boost, to fill the buffers transparently in the background.