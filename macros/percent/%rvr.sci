//<h>=%rvr(h1,h2)
// %rvr(h1,h2) calcule (I+h1*h2)\h1. h1 et h2 matrices de fractions
//  rationnelles
//!
[m1,n1]=size(h1(2))
[m2,n2]=size(h2(2))
if abs(n1-m2)+abs(m1-n2)<>0 then error('inconsistent dimensions'),end
h=(eye(m1,m1)+h1*h2)\h1
//end


