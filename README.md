**Vex-Packet-Analyzer**

> A custom, zero-dependency network packet analyzer and Mini-IDS core built entirely in C from scratch.

**Overview** This project aims to develop a custom network packet analyzer for reading PCAP files and analyzing their content at the binary level. Rather than relying on external networking libraries, it directly interacts with memory and file streams to parse data.

**Core Mechanics:**

- **Binary Parsing:** Reads and decodes the PCAP Global Header and iterates through individual Packet Headers.
- **Memory Management:** Dynamically extracts packet-associated data and organizes the results within a custom Linked List structure for efficient processing and traversal.
- **Security Application:** Serves as the foundational engine for a simple Intrusion Detection System (Mini-IDS), bridging the gap between low-level systems programming and practical cybersecurity.
