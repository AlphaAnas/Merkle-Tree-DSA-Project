# Merkle-Tree-DSA-Project
Merkle Tree Implementation using C++ and Object Oriented Programming .
So, what's a Merkle Tree?  It's a hierarchical structure built using cryptographic hash functions. Each leaf node represents a block of data, like parts of a file. As you move up the tree, the hash values of child nodes combine to form the hash of their parent node. This way, even a tiny change in any part of the data results in a completely different root hash, making tampering evident.

In our project, we're leveraging C++ to make this powerful concept to ensure the integrity of files. It takes a file as input, and constructs a Merkle Tree based on its contents. Then, it generate a digital signature using the Merkle Tree structure. This signature serves as a unique identifier for your file, making it easy to verify its authenticity later.

