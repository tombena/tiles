# tiles
A set of floor tiles contains tiles of size 2 and 3.
These floor tiles are always laid out in strips, for instance 3223 is a strip of length 10.

When two strips are adjacent, no two tiles can share an inner edge. For instance, strips 3223 and 3322 both start with a 3 so they cannot be neighbors. But strips 3223 and 22222 of length 10 can be neighbors because they don't share inner edges.

The goal is to find the total number of floor designs which have 11 strips of length 30
