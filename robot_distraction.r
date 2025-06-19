library(MASS)

# Likert responses (as ordered factor)
rating <- ordered(c(5, 5, 3, 5, 3, 3, 2, 4, 3, 4, 3, 6, 5, 7, 6, 5, 3, 2, 3, 5)) # nolint

# 1 = test group, 0 = control
group <- factor(c(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0)) # nolint

# Fit ordinal logistic regression model
model <- polr(rating ~ group, method = "logistic")

# Summary output
print(summary(model))

# Get odds ratio
print(exp(coef(model)))
