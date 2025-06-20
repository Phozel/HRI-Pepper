

# Data
#Group 0 = Control Group
#Group 1 = Test Group

slouches_group0 <- c(2, 2, 5, 4, 6, 3, 1, 9, 1, 8)
corrections_group0 <- c(1, 1, 3, 3, 6, 3, 0, 8, 0, 8)

slouches_group1 <- c(2, 2, 5, 5, 7, 3, 7, 6, 4, 8)
corrections_group1 <- c(1, 2, 5, 4, 6, 3, 7, 6, 3, 8)

# Combine into a data frame
group <- c(rep(0, length(slouches_group0)), rep(1, length(slouches_group1)))
slouches <- c(slouches_group0, slouches_group1)
corrections <- c(corrections_group0, corrections_group1)

df <- data.frame(
  corrections = corrections,
  slouches = slouches,
  group = factor(group)
)

# Fit binomial logistic regression model
model <- glm(cbind(corrections, slouches - corrections) ~ group,
             family = binomial(link = "logit"),
             data = df)

# Output summary
print(summary(model))

# Odds ratio for group effect
print(exp(coef(model)["group1"]))
