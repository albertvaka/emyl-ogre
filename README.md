Emyl Makes You Listen
=====================

About Emyl
----------

Emyl (acronym for Emyl Makes You Listen) is a C++ sound library that abstracts the usage of OpenAL and libOgg.

It provides the classes `emyl::sound` and `emyl::stream` (for longer audio files, like music) with methods like `Load(filename)` or `Play()` that transparently use OpenAL without having to worry about managing buffers and sources.

This library is meant to be included in your project code and be statically linked. You will need to install OpenAL and libvorbis + libogg before compiling Emyl.

You can read the complete readme of the original Emyl project here: https://github.com/budsan/emyl/blob/master/readme.md

About this fork
---------------

This fork mainly adds two functionalities to Emyl:

 * Loading files not only from disk but also from Ogre resurces, to integrate seamlessly with Ogre-based games.
 
 * Multithreading capabilities using Boost, to fill the buffers transparently in the background.
