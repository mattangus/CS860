# CS860 - Hankel Determinant Checker

This is a program to check if hankel determinants of a sequence are non zero up to some value for t.

The open problem is described below (taken from [here](https://cs.uwaterloo.ca/~shallit/Courses/860/problems.html) #6):

> [A somewhat old problem, discussed January 12 2017]. Given an infinite sequence s(n), we can form the Hankel matrix of order n beginning at position k as follows: the first row is 
> s(k) s(k+1) ... s(k+n-1) 
> the next row is formed by a sliding window of size n into s, so 
> s(k+1) s(k+2) ... s(k+n) 
> and so forth, until the last row 
> s(k+n-1) s(k+n) ... s(k+2n-2)
> The Hankel determinant is then the determinant of this matrix. These have been studied in great detail because if a sequence satisfies a linear recurrence with constant coefficients, then all sufficiently large Hankel determinants starting sufficiently far out are 0.
> 
> Conjecture: there exists an infinite sequence over a finite subset of Z - {0} with the property that all Hankel determinants (of all orders n ≥ 1 and starting points k ≥ 0) are nonzero.
> 
> What's known: it is not hard to prove that this is impossible for subsets of cardinality 2. However, it seems like it might be possible for some subsets of cardinality 3. One possible sequence is the fixed point, starting with 1, of the morphism 1 → 12113, 2 → 21131, 3 → 23132, which avoids 0 Hankel determinants for all k, n with k+n < 3300. (This computation was done using Dodgson condensation, which is more efficient than computing all Hankel determinants from scratch.) If this is so, then it would be best possible in terms of alphabet size. So try to prove this sequence has no 0 Hankel determinants! Or disprove it by continuing the calculation beyond what I did.
> 
> Another possibility: consider the fixed point, starting with 1, of the morphism 1 → 12, 2 → 23, 3 → 14, 4 → 32. This avoids 0 Hankel determinants for all k, n with k+n < 3300. Try to prove it has no 0 Hankel determinants!
> 
> One obvious strategy to try to prove this would be to show that the determinants are all nonzero mod m, for some integer m. But I also conjecture this is impossible for all m. For example, for m = 2,3,4,5 the longest sequences avoiding Hankel determinants mod m are as follows:
> 
> |n |length | example of longest of longest sequence|
> |---|-------|---------------------------------------|
> |2 |  2  	 |   11                                  |
> |3 |	4  	 |  1221                                 |
> |4 |	24   |	132132231231122331121332             |
> |5 |	22   |	1424133432424131321224               |

#Usage
```
cmake .
make
./cs860 --morphism morphFile --size 1000
```
