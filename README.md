# Vex-Packet-Analyzer (Vexor)

A zero-dependency packet analyzer and Mini-IDS core, written in C from scratch.

## What it does
Parses PCAP files at the binary level without relying on any networking libraries — just direct memory and file stream handling.

- **Binary parsing:** reads the PCAP global header and iterates through packet headers
- **Memory management:** extracts packet data into a custom linked list for traversal
- **Security layer:** the parsing engine doubles as the core for a simple Intrusion Detection System (Mini-IDS)