# Nanopb_Serial
An example project that uses nanopb to pass messages on USB using Chibios.
The proto files used are in [proto](proto)folder and the headers and sources will be automatically generated using the cmake file provided in Nanopb. 

Inorder to differentiate messages, every message has enum infront of it that differentiates it from other messages. 

Uses bluepill to run the code.
