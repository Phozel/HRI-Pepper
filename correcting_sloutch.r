#This should be right but pls double check 
#slouches_group0 <- c(2, 2, 4, 5, 3, 6, 3, 10, 2, 9)
#corrections_group0 <- c(1, 1, 3, 3, 3, 5, 3, 8, 0, 7)

#slouches_group1 <- c(3, 2, 5, 5, 7, 3, 6, 4, 7, 6)
#corrections_group1 <- c(1, 2, 5, 4, 6, 3, 6, 3, 6, 5)

# Data
slouches_group0 <- c(2, 2, 6, 5, 5, 6, 4, 1, 8, 2, 9)
corrections_group0 <- c(1, 1, 5, 4, 4, 6, 3, 0, 6, 1, 7)

slouches_group1 <- c(2, 3, 3, 6, 6, 3, 3, 6, 6, 4, 6)
corrections_group1 <- c(1, 2, 2, 6, 6, 3, 3, 6, 6, 3, 5)

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
