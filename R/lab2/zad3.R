print("Zadanie 16: Defekty szkła, lambda = 0.002/m2, 10x10m okno")
lambda_16 <- 0.002
area_16 <- 100
mu_16 <- lambda_16 * area_16

print("")
print("a) P(X = 0), P(X = 1), P(X = 2)")
prob_16a_0 <- dpois(0, mu_16)
prob_16a_1 <- dpois(1, mu_16)
prob_16a_2 <- dpois(2, mu_16)
print(paste("P(X = 0) =", round(prob_16a_0, 5)))
print(paste("P(X = 1) =", round(prob_16a_1, 5)))
print(paste("P(X = 2) =", round(prob_16a_2, 5)))

print("")
print("b) P(X <= 2)")
prob_16b <- sum(dpois(0:2, mu_16))
print(paste("P(X <= 2) =", round(prob_16b, 4)))

print("")
prob_16b_alt <- ppois(2, mu_16)
print(paste("Alternatywnie: P(X <= 2) =", round(prob_16b_alt, 4)))

print("")
print("c) P(X > 2)")
prob_16c <- 1 - ppois(2, mu_16)
print(paste("P(X > 2) =", round(prob_16c, 6)))

print("")
print("Zadanie 17: Umowy budowlane, 300 na 200, 60000m2")
lambda_17 <- 60 / 60000
print(paste("lambda =", lambda_17, "pęcherzyków/m2"))

print("")
print("b) E(X) dla 60000 m2")
mu_17b <- lambda_17 * 60000
print(paste("E(X) =", mu_17b))

print("")
print("c) E(X) dla 3 milisekundy")
mu_17c <- lambda_17 * 3
print(paste("E(X) =", mu_17c))

print("")
print("d) P(18 <= X <= 21) dla 20 milisekund")
mu_17d <- lambda_17 * 20
prob_17d <- ppois(21, mu_17d) - ppois(17, mu_17d)
print(paste("P(18 <= X <= 21) =", round(prob_17d, 4)))

print("")
prob_17d_alt <- sum(dpois(18:21, mu_17d))
print(paste("Alternatywnie: P(18 <= X <= 21) =", round(prob_17d_alt, 4)))

print("")
print("Zadanie 19: Rozkład hipergeometryczny, N = 12, r = 4, n = 4")
N_19 <- 12
r_19 <- 4
n_19 <- 4

print("")
print("a) f(0), n = 4")
prob_19a <- dhyper(0, r_19, N_19 - r_19, n_19)
print(paste("f(0) =", round(prob_19a, 4)))

print("")
print("b) f(1), n = 4")
prob_19b <- dhyper(1, r_19, N_19 - r_19, n_19)
print(paste("f(1) =", round(prob_19b, 4)))

print("")
print("c) f(2), n = 4")
prob_19c <- dhyper(2, r_19, N_19 - r_19, n_19)
print(paste("f(2) =", round(prob_19c, 4)))

print("")
print("d) P(X <= 3), n = 6")
n_19d <- 6
prob_19d <- phyper(3, r_19, N_19 - r_19, n_19d)
print(paste("P(X <= 3) =", round(prob_19d, 4)))

print("")
prob_19d_alt <- sum(dhyper(0:3, r_19, N_19 - r_19, n_19d))
print(paste("Alternatywnie: P(X <= 3) =", round(prob_19d_alt, 4)))

print("")
print("e) P(X >= 4), n = 6")
prob_19e <- 1 - phyper(3, r_19, N_19 - r_19, n_19d)
print(paste("P(X >= 4) =", round(prob_19e, 4)))

print("")
print("f) E(X), Var(X), sigma dla n = 6")
E_19f <- n_19d * (r_19 / N_19)
Var_19f <- n_19d * (r_19 / N_19) * (1 - r_19 / N_19) * ((N_19 - n_19d) / (N_19 - 1))
sigma_19f <- sqrt(Var_19f)
print(paste("E(X) =", round(E_19f, 4)))
print(paste("Var(X) =", round(Var_19f, 4)))
print(paste("sigma =", round(sigma_19f, 4)))

print("")
print("Zadanie 25: Baterie AA, karton 100 sztuk, 15 uszkodzonych")
N_25 <- 100
r_25 <- 15
n_25 <- 5

print("")
print("a) P(karton zwrócony), rozmiar próbki n = 5")
prob_25a <- 1 - dhyper(0, r_25, N_25 - r_25, n_25)
print(paste("P(X >= 1) = 1 - P(X = 0) =", round(prob_25a, 4)))

print("")
print("Zadanie 26: Rozkład jednostajny, a = 120, b = 140")
a_26 <- 120
b_26 <- 140

print("")
print("a) f(x)")
f_26 <- 1 / (b_26 - a_26)
print(paste("f(x) = 1/(b-a) =", f_26))

print("")
print("b) E(x) i sigma")
E_26 <- (a_26 + b_26) / 2
sigma_26 <- sqrt((b_26 - a_26)^2 / 12)
print(paste("E(x) = (a+b)/2 =", E_26))
print(paste("sigma = sqrt((b-a)^2/12) =", round(sigma_26, 2)))

print("")
print("Zadanie 27: P(x = 130)")
prob_27 <- 0
print(paste("P(x = 130) =", prob_27))

print("")
print("Zadanie 28: a = 120, b = 140")

print("")
print("a) P(125 <= x <= 135)")
prob_28a <- punif(135, a_26, b_26) - punif(125, a_26, b_26)
print(paste("P(125 <= x <= 135) =", round(prob_28a, 4)))

print("")
print("b) P(125 <= x <= 131)")
prob_28b <- punif(131, a_26, b_26) - punif(125, a_26, b_26)
print(paste("P(125 <= x <= 131) =", round(prob_28b, 4)))

print("")
print("c) P(129 <= x <= 131)")
prob_28c <- punif(131, a_26, b_26) - punif(129, a_26, b_26)
print(paste("P(129 <= x <= 131) =", round(prob_28c, 4)))

print("")
print("Zadanie 29: a = 200000, b = 250000")
a_29 <- 200000
b_29 <- 250000

print("")
print("a) f(x)")
f_29 <- 1 / (b_29 - a_29)
print(paste("f(x) =", f_29))

print("")
print("b) E(x) i sigma")
E_29 <- (a_29 + b_29) / 2
sigma_29 <- sqrt((b_29 - a_29)^2 / 12)
print(paste("E(x) =", E_29))
print(paste("sigma =", round(sigma_29, 2)))

print("")
print("c) P(x >= 235000)")
prob_29c <- 1 - punif(235000, a_29, b_29)
print(paste("P(x >= 235000) =", round(prob_29c, 4)))

print("")
print("Zadanie 30: qunif")

print("")
print("a) qunif(0.75)")
q_30a <- qunif(0.75, a_29, b_29)
print(paste("qunif(0.75) =", q_30a))

print("")
print("b) qunif(0.25)")
q_30b <- qunif(0.25, a_29, b_29)
print(paste("qunif(0.25) =", q_30b))

print("")
print("Zadanie 36: Rozkład normalny")

print("")
print("a) P(z <= z) = 0.99")
z_36a <- qnorm(0.99)
print(paste("z =", round(z_36a, 3)))

print("")
print("b) P(z <= z) = 0.975")
z_36b <- qnorm(0.975)
print(paste("z =", round(z_36b, 3)))

print("")
print("c) P(z <= z) = 0.95")
z_36c <- qnorm(0.95)
print(paste("z =", round(z_36c, 3)))

print("")
print("Zadanie 37: Rozkład normalny")

print("")
print("a) P(z >= z) = 0.1")
z_37a <- qnorm(0.90)
print(paste("z =", round(z_37a, 3)))

print("")
print("b) P(z >= z) = 0.05")
z_37b <- qnorm(0.95)
print(paste("z =", round(z_37b, 3)))