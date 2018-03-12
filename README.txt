Aditi:
Wrote the heuristic function, optimized score calculation to find best move
using mobility and weighted scores for edge and corner cases.

Richard:
Implemented the recursive minimax function, using both a simple score
calculating algorithm and Aditi's more robust algorithm. 

Improvements:
Heuristic function adds point values to the score instead of
multiplying, as multiplying could make a corner move appear worse
if the net score was negative for that move. 

In addition, it also considers mobility of a given move -
the potential moves a given move creates, the better it is. 
