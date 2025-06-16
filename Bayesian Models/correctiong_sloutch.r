library(rethinking)

# Data
# 1 = test group, 0 = control
group <- c(
  0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0,  # new data
  1, 1, 1, 1, 0, 0, 0, 0                    # previous data
)

# n = nr of events
slouches <- c(
  2, 2, 2, 3, 3, 6, 5, 5, 6, 6, 3, 3, 6, 4,  # new data
  6, 6, 4, 6, 1, 8, 2, 9                    # previous data
)

corrections <- c(
  1, 1, 1, 2, 2, 5, 4, 4, 6, 6, 3, 3, 6, 3,  # new data
  6, 6, 3, 5, 0, 6, 1, 7                    # previous data
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
