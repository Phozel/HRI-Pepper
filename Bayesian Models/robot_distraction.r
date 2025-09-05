library(rethinking)

# Likert responses
rating <- c(5, 5, 3, 5, 3, 3, 2, 4, 3, 4, 3, 6, 5, 7, 6, 5, 3, 2, 3, 5)

# 1 = test group, 0 = control
group <- c(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0)

# Data list for ulam
dat <- list(
  N = length(rating),
  rating = rating,
  group = group
)

m <- ulam(
  alist(
    rating ~ ordered_logistic(phi, cutpoints),
    phi <- a + b * group,
    a ~ normal(0, 1),
    b ~ normal(0, 1),
    cutpoints ~ normal(0, 1)
  ),
  data = dat,
  chains = 4,
  cores = 4
)

print(precis(m, depth = 2))

post <- extract.samples(m)
print(mean(post$b > 0))
