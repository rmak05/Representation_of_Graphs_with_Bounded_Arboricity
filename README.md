# Representation of Graphs with Bounded Arboricity

An implementation of the graph data structure described in `"Dynamic Representation of Sparse Graphs" by Gerth Stølting Brodal and Rolf Fagerberg (WADS 1999: 342-351)`.

## Overview

This repository provides an implementation of dynamic graphs, which supports the following operations:

| Operation  | Time Complexity                   |
|:-----------|:----------------------------------|
| Adjacency  | *O*(**c**) worst case             |
| Insertion  | *O*(**1**) amortized              |
| Deletion   | *O*(**c** + log**n**) amortized   |

Where,   
- **n** = number of vertices in the graph    
- **c** = bound on the arboricity of the graph    

## Sparse Graph Generator

This repository includes a utility to generate graphs with arboricity bounded by a given value.   
The steps of generation are as follows:

- Provide **n** (number of vertices) and **c** (arboricity bound) as input.

- **c** random spanning trees are generated on the vertex set V = {0, 1, ..., **n** - 1}.   
  There are multiple ways to generate a uniformly random spanning tree:
    - Generate a random [prüfer sequence](https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence) and construct its equivalent tree.
    - Start with all the vertices as **n** connected components. Repeatedly pick two random connected components and connect them, until only one connected component remains.

- The union of the edge sets of all the generated trees is taken as the edge set of the final graph which is the output.