print("Zadanie 9a: P(X = 12)")
n_9a <- 20
x_9a <- 12
p_9a <- 0.50
prob_9a <- dbinom(x_9a, n_9a, p_9a)
print(paste("P(X = 12) =", round(prob_9a, 4)))

print("")
print("Zadanie 9b: P(X <= 5)")
x_9b <- 5
prob_9b <- pbinom(x_9b, n_9a, p_9a)
print(paste("P(X <= 5) =", round(prob_9b, 5)))

print("")
prob_9b_alt <- sum(dbinom(0:x_9b, n_9a, p_9a))
print(paste("Alternatywnie: P(X <= 5) =", round(prob_9b_alt, 5)))

print("")
print("Zadanie 10: Rozkład Poissona, mu = 3")
mu_10 <- 3

print("")
print("a) f(3)")
prob_10a <- dpois(3, mu_10)
print(paste("f(3) =", round(prob_10a, 4)))

print("")
print("b) P(X = 2)")
prob_10b <- dpois(2, mu_10)
print(paste("f(2) =", round(prob_10b, 4)))

print("")
print("c) P(X = 3)")
print(paste("f(3) =", round(prob_10a, 4)))

print("")
print("Zadanie 11: Proces Poissona, mu = 5")
mu_11 <- 5

print("")
print("a) f(5)")
prob_11a <- dpois(5, mu_11)
print(paste("f(5) =", round(prob_11a, 4)))

print("")
print("b) Oczekiwana liczba w 5 przedziałach")
print(paste("E(X) =", 5 * mu_11))

print("")
print("c) f(25) dla mu = 25")
prob_11c <- dpois(25, 25)
print(paste("f(25) =", round(prob_11c, 4)))

print("")
print("d) Oczekiwana liczba w odstępach 0.25")
print(paste("E(X) =", 5 * 0.25))

print("")
print("e) f(1.25) dla mu = 1.25")
prob_11e <- dpois(1, 1.25)
print(paste("f(1) =", round(prob_11e, 5)))

print("")
print("Zadanie 12: mu = 1.25, x = 0, 1, 2, 3")
mu_12 <- 1.25
x_12 <- c(0, 1, 2, 3)

for(i in x_12) {
  prob <- dpois(i, mu_12)
  print(paste("f(", i, ") =", round(prob, 5), sep = ""))
}

print("")
print("Zadanie 13: mu = 25, x = 23, 24, 25, 26")
mu_13 <- 25
x_13 <- c(23, 24, 25, 26)

for(i in x_13) {
  prob <- dpois(i, mu_13)
  print(paste("f(", i, ") =", round(prob, 5), sep = ""))
}

print("")
print("Zadanie 14a: P(X > 4), mu = 5")
mu_14a <- 5
prob_14a <- 1 - ppois(4, mu_14a)
print(paste("P(X > 4) =", round(prob_14a, 4)))

print("")
print("Zadanie 14b: P(7 <= X <= 12), mu = 10")
mu_14b <- 10
prob_14b <- ppois(12, mu_14b) - ppois(6, mu_14b)
print(paste("P(7 <= X <= 12) =", round(prob_14b, 4)))

print("")
prob_14b_alt <- sum(dpois(7:12, mu_14b))
print(paste("Alternatywnie: P(7 <= X <= 12) =", round(prob_14b_alt, 4)))

print("")
print("Zadanie 14c: P(X = 5), mu = 5")
mu_14c <- 5
prob_14c <- dpois(5, mu_14c)
print(paste("P(X = 5) =", round(prob_14c, 4)))

print("")
print("Zadanie 15a: P(X = 4), mu = 6")
mu_15a <- 6
prob_15a <- dpois(4, mu_15a)
print(paste("P(X = 4) =", round(prob_15a, 4)))

print("")
print("Zadanie 15b: P(X > 4), mu = 6")
prob_15b <- 1 - ppois(4, mu_15a)
print(paste("P(X > 4) =", round(prob_15b, 4)))

print("")
print("Zadanie 15c: P(X <= 74), lambda = 1, t = 72, mu = 72")
mu_15c <- 72
prob_15c <- ppois(74, mu_15c)
print(paste("P(X <= 74) =", round(prob_15c, 4)))

print("")
prob_15c_alt <- sum(dpois(0:74, mu_15c))
print(paste("Alternatywnie: P(X <= 74) =", round(prob_15c_alt, 4)))