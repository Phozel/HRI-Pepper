library(rethinking)

# Data
# 1 = test group, 0 = control
group <- c(1, 1, 1, 1, 0, 0, 0, 0)

# n = nr of events
slouches <- c(6, 6, 4, 6, 1, 8, 2, 9)
corrections <- c(6, 6, 3, 5, 0, 6, 1, 7)

# Data list for ulam
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
