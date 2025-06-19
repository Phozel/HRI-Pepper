library(rethinking)

# Data
# 1 = test group, 0 = control
group <- c(
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
)

# n = nr of events
slouches <- c(
  2, 2, 5, 4, 6, 3, 1, 9, 1, 8, 2, 2, 5, 5, 7, 3, 7, 6, 4, 8
)

corrections <- c(
  1, 1, 3, 3, 6, 3, 0, 8, 0, 8, 1, 2, 5, 4, 6, 3, 7, 6, 3, 8
)

data_list <- list(
  group = group,
  slouches = slouches,
  corrections = corrections
)

m <- ulam(
  alist(
    corrections ~ dbinom(slouches, p),
    logit(p) <- a + b * group,
    a ~ normal(0, 1),
    b ~ normal(0, 1)
  ),
  data = data_list,
  chains = 4,
  cores = 4
)

print(precis(m))
post <- extract.samples(m)
print(mean(post$b > 0))
