First fit
=========
  # time ./mp 3 100
    0.01 real   0.00 user   0.01 sys
    0.01 real   0.00 user   0.01 sys
    0.03 real   0.00 user   0.03 sys
  # time ./mp 3 10000
    0.21 real   0.18 user   0.03 sys
    0.21 real   0.18 user   0.03 sys
    0.23 real   0.18 user   0.05 sys
  # time ./mp 3 100000
    2.13 real   2.08 user   0.05 sys
    2.16 real   2.10 user   0.05 sys
    2.11 real   2.06 user   0.05 sys

  # time ./mp 15 100
    0.08 real   0.00 user   0.05 sys
    0.08 real   0.01 user   0.08 sys
    0.08 real   0.00 user   0.05 sys
  # time ./mp 15 10000
    1.16 real   1.05 user   0.08 sys
    1.11 real   1.06 user   0.03 sys
    1.10 real   0.96 user   0.13 sys
  # time ./mp 15 100000
    14.26 real   14.04 user   0.31 sys
    14.78 real   14.45 user   0.31 sys
    15.03 real   14.60 user   0.33 sys

  # time ./mp 45 100
    0.16 real   0.01 user   0.13 sys
    0.16 real   0.01 user   0.15 sys
    0.16 real   0.00 user   0.10 sys
  # time ./mp 45 10000
    3.31 real   3.05 user   0.23 sys
    3.33 real   3.03 user   0.25 sys
    3.35 real   3.05 user   0.28 sys
  # time ./mp 45 100000
    38.71 real   37.55 user   1.10 sys
    44.58 real   43.45 user   1.00 sys
    44.75 real   43.68 user   0.95 sys

  # time ./mpm 3
    1.11 real   1.08 user   0.03 sys
    1.10 real   1.05 user   0.03 sys
    1.23 real   1.13 user   0.08 sys
  # time ./mpm 15
    5.61 real   5.46 user   0.15 sys
    5.65 real   5.48 user   0.13 sys
    5.58 real   5.38 user   0.13 sys
  # time ./mpm 45
    16.95 real   16.41 user   0.46 sys
    16.33 real   15.80 user   0.50 sys
    16.91 real   16.46 user   0.45 sys

Best fit
========
  # time ./mp 3 100
    0.03 real   0.00 user   0.00 sys
    0.03 real   0.00 user   0.03 sys
    0.03 real   0.00 user   0.01 sys
  # time ./mp 3 10000
    0.31 real   0.25 user   0.05 sys
    0.31 real   0.26 user   0.05 sys
    0.33 real   0.28 user   0.00 sys
  # time ./mp 3 100000
    3.03 real   2.95 user   0.06 sys
    2.95 real   2.86 user   0.03 sys
    3.05 real   2.96 user   0.08 sys

  # time ./mp 15 100
    0.08 real   0.00 user   0.06 sys
    0.10 real   0.00 user   0.08 sys
    0.08 real   0.01 user   0.06 sys
  # time ./mp 15 10000
    1.51 real   1.41 user   0.05 sys
    1.53 real   1.38 user   0.15 sys
    1.55 real   1.45 user   0.08 sys
  # time ./mp 15 100000
    14.78 real   14.41 user   0.33 sys
    14.85 real   14.46 user   0.30 sys
    14.83 real   14.45 user   0.36 sys
  
  # time ./mp 45 100
    0.21 real   0.01 user   0.05 sys
    0.23 real   0.03 user   0.10 sys
    0.23 real   0.00 user   0.08 sys
  # time ./mp 45 10000
    4.65 real   4.40 user   0.21 sys
    4.53 real   4.23 user   0.30 sys
    4.56 real   4.18 user   0.36 sys
  # time ./mp 45 100000
    47.06 real   45.95 user   1.01 sys
    45.33 real   44.31 user   0.96 sys
    44.40 real   43.15 user   1.18 sys

  # time ./mpm 3
    1.11 real   1.05 user   0.05 sys
    1.08 real   1.03 user   0.05 sys
    1.15 real   1.08 user   0.05 sys
  # time ./mpm 15
    5.46 real   5.30 user   0.16 sys
    5.60 real   5.30 user   0.25 sys
    5.43 real   5.25 user   0.15 sys
  # time ./mpm 45
    16.51 real   16.08 user   0.38 sys
    16.58 real   15.95 user   0.58 sys
    16.48 real   15.96 user   0.48 sys

Quick fit
=========
  # time ./mp 3 100
    0.03 real   0.00 user   0.03 sys
    0.03 real   0.00 user   0.01 sys
    0.03 real   0.00 user   0.01 sys
  # time ./mp 3 10000
    0.36 real   0.28 user   0.06 sys
    0.31 real   0.28 user   0.03 sys
    0.28 real   0.26 user   0.01 sys
  # time ./mp 3 100000
    3.00 real   2.90 user   0.08 sys
    2.98 real   2.90 user   0.05 sys
    3.03 real   2.95 user   0.06 sys

  # time ./mp 15 100
    0.08 real   0.00 user   0.05 sys
    0.08 real   0.00 user   0.03 sys
    0.08 real   0.00 user   0.05 sys
  # time ./mp 15 10000
    1.53 real   1.41 user   0.10 sys
    1.50 real   1.36 user   0.13 sys
    1.55 real   1.41 user   0.11 sys
  # time ./mp 15 100000
    14.83 real   14.51 user   0.28 sys
    15.08 real   14.75 user   0.28 sys
    15.08 real   14.65 user   0.36 sys
  
  # time ./mp 45 100
    0.21 real   0.00 user   0.20 sys
    0.21 real   0.00 user   0.16 sys
    0.21 real   0.00 user   0.16 sys
  # time ./mp 45 10000
    4.66 real   4.35 user   0.25 sys
    4.55 real   4.16 user   0.35 sys
    4.61 real   4.23 user   0.35 sys
  # time ./mp 45 100000
    44.66 real   43.48 user   1.16 sys
    44.80 real   43.70 user   1.01 sys
    45.18 real   44.16 user   0.90 sys
  
  # time ./mpm 3
    1.11 real   1.06 user   0.03 sys
    1.11 real   1.06 user   0.01 sys
    1.13 real   1.01 user   0.10 sys
  # time ./mpm 15
    5.63 real   5.48 user   0.11 sys
    5.51 real   5.28 user   0.23 sys
    5.53 real   5.38 user   0.15 sys
  # time ./mpm 45
    16.45 real   15.88 user   0.53 sys
    16.45 real   15.86 user   0.50 sys
    16.47 real   16.02 user   0.41 sys

Quantum values
==============
qs = 2
  # time ./pp 5
    0.26 real   0.01 user   0.18 sys
    0.23 real   0.00 user   0.21 sys
    0.25 real   0.00 user   0.21 sys
  # time ./pp 20
    1.18 real   0.03 user   1.06 sys
    1.31 real   0.05 user   1.18 sys
    1.21 real   0.05 user   1.00 sys
  # time ./pp 50
    3.31 real   0.18 user   2.81 sys
    3.18 real   0.11 user   2.91 sys
    3.15 real   0.10 user   2.78 sys

qs = 4
  # time ./pp 5
    0.30 real   0.01 user   0.28 sys
    0.28 real   0.00 user   0.23 sys
    0.31 real   0.03 user   0.23 sys
  # time ./pp 20
    1.03 real   0.06 user   0.96 sys
    1.03 real   0.06 user   0.88 sys
    1.05 real   0.01 user   0.98 sys
  # time ./pp 50
    2.55 real   0.05 user   2.21 sys
    2.55 real   0.11 user   2.31 sys
    2.56 real   0.10 user   2.31 sys

qs = 8
  # time ./pp 5
    0.31 real   0.00 user   0.23 sys
    0.30 real   0.03 user   0.16 sys
    0.26 real   0.00 user   0.16 sys
  # time ./pp 20
    1.03 real   0.01 user   0.96 sys
    1.05 real   0.08 user   0.93 sys
    1.05 real   0.01 user   0.93 sys
  # time ./pp 50
    2.56 real   0.06 user   2.26 sys
    3.01 real   0.15 user   2.66 sys
    2.65 real   0.13 user   2.28 sys

qs = 16
  # time ./pp 5
    0.28 real   0.00 user   0.16 sys
    0.28 real   0.01 user   0.16 sys
    0.28 real   0.00 user   0.18 sys
  # time ./pp 20
    1.03 real   0.05 user   0.98 sys
    1.05 real   0.05 user   0.93 sys
    1.03 real   0.08 user   0.85 sys
  # time ./pp 50
    2.58 real   0.10 user   2.13 sys
    2.58 real   0.08 user   2.23 sys
    2.58 real   0.15 user   2.45 sys

qs = 32
  # time ./pp 5
    0.31 real   0.01 user   0.15 sys
    0.28 real   0.00 user   0.18 sys
    0.26 real   0.00 user   0.16 sys
  # time ./pp 20
    1.01 real   0.08 user   0.88 sys
    1.01 real   0.03 user   0.75 sys
    1.05 real   0.05 user   0.90 sys
  # time ./pp 50
    2.51 real   0.16 user   2.23 sys
    2.53 real   0.15 user   2.30 sys
    2.50 real   0.10 user   2.16 sys

qs = 64
  # time ./pp 5
    0.30 real   0.01 user   0.21 sys
    0.26 real   0.00 user   0.20 sys
    0.28 real   0.00 user   0.25 sys
  # time ./pp 20
    1.01 real   0.13 user   0.83 sys
    1.08 real   0.03 user   0.86 sys
    1.06 real   0.01 user   0.98 sys
  # time ./pp 50
    2.50 real   0.15 user   2.10 sys
    2.50 real   0.16 user   2.23 sys
    2.48 real   0.13 user   2.18 sys