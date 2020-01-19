std::vector<std::pair<PT, PT>> GetAllAntiPodalPairs(std::vector<PT> p) {
  std::sort(p.begin(),
            p.end(),
            [](const PT &p1, const PT &p2) {
              return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
            });
  auto last = std::unique(p.begin(), p.end());
  p.erase(last, p.end());

  if (p.size() == 1) return {};
  if (p.size() == 2) return {std::make_pair(p[0], p[1])};

  //Obtain upper and lower parts of polygon
  vector<PT> U, L;
  ConvexHull(p, U, L);

  std::vector<std::pair<PT,PT>> res;
  //Now we have U and L, apply rotating calipers
  u64 i = 0, j = L.size() - 1;
  while (i < U.size() - 1 || j > 0) {
    res.emplace_back(U[i], L[j]);

    //if i or j made it all the way through advance other size
    if (i == U.size() - 1)
      --j;
    else if (j == 0)
      ++i;
    else if ((U[i + 1].y - U[i].y) * (L[j].x - L[j - 1].x)
        > (U[i + 1].x - U[i].x) * (L[j].y - L[j - 1].y))
      ++i;
    else
      --j;
  }
  return res;
}

