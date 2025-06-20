library(MASS)

# Data
rating <- ordered(c(5, 7, 5, 7, 5, 6, 4, 6, 2, 6, 4, 4, 4, 4, 2, 4, 7, 5, 7, 5))
group <- factor(c(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0))

# Fit ordinal logistic regression
model <- polr(rating ~ group, method = "logistic")

# Summary
print(summary(model))
print(exp(coef(model)["group1"]))
