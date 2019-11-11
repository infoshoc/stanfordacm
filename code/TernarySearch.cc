while (r - l > EPS) {
   double m1 = l + (r - l) / 3,
      m2 = r - (r - l) / 3;
   if (f (m1) < f (m2))
      l = m1;
   else
      r = m2;
}
//Unimodal/Convex max(g,f), g+f
while(lo < hi) {
    int mid = (lo + hi) >> 1;
    if(f(mid) > f(mid+1))
        hi = mid;
    else
        lo = mid+1;
}
//strictly increasing/decreasing

