print("Zadanie 1: Rzut monetą 3 razy")
S <- c("OOO", "OOR", "ORO", "ROO", "ORR", "ROR", "RRO", "RRR")
print(S)
print(paste("Liczba możliwych wyników:", length(S)))

print("")
print("Zadanie 2: Rozkład prawdopodobieństwa")
x <- c(0, 1, 2, 3)
f_x <- c(0.1250, 0.3750, 0.3750, 0.1250)
rozklad <- data.frame(
  "x" = x,
  "f(x)" = f_x
)
print(rozklad)

print("")
print("Zadanie 3: Weryfikacja prawidłowości rozkładu")
wszystkie_nieujemne <- all(f_x >= 0)
suma_prawdopodobienstw <- sum(f_x)
print(paste("Wszystkie f(x) >= 0:", wszystkie_nieujemne))
print(paste("Suma f(x) =", suma_prawdopodobienstw))
print(paste("Rozkład prawidłowy:", wszystkie_nieujemne && suma_prawdopodobienstw == 1))

print("")
print("Zadanie 4: P(X <= 2)")
P_x_le_2 <- sum(f_x[x <= 2])
print(paste("P(X <= 2) =", P_x_le_2))

print("")
print("Zadanie 5: Wartość oczekiwana E(X)")
E_x <- sum(x * f_x)
print(paste("E(X) =", E_x))

png("rozklad_prawdopodobienstwa_rzut_moneta.png", width = 800, height = 600)
barplot(f_x, 
        names.arg = x,
        col = "lightblue",
        main = "Rozkład prawdopodobieństwa liczby orłów w 3 rzutach monetą",
        xlab = "Liczba orłów (x)",
        ylab = "Prawdopodobieństwo f(x)",
        ylim = c(0, 0.4))
dev.off()
print("Wykres zapisany jako: rozklad_prawdopodobienstwa_rzut_moneta.png")

print("")
print("Zadanie 6: Rozkład dwumianowy - wartość oczekiwana, wariancja i odchylenie standardowe")
print("")

print("a) n = 75, p = 0.40")
n_a <- 75
p_a <- 0.40
E_a <- n_a * p_a
var_a <- n_a * p_a * (1 - p_a)
sd_a <- sqrt(var_a)
print(paste("E(x) = np =", E_a))
print(paste("σ² = np(1-p) =", var_a))
print(paste("σ = √(np(1-p)) =", sd_a))

print("")
print("b) n = 37, p = 0.65")
n_b <- 37
p_b <- 0.65
E_b <- n_b * p_b
var_b <- n_b * p_b * (1 - p_b)
sd_b <- sqrt(var_b)
print(paste("E(x) = np =", E_b))
print(paste("σ² = np(1-p) =", var_b))
print(paste("σ = √(np(1-p)) =", sd_b))

print("")
print("Zadanie 7: Rozkład dwumianowy - tunel Lincolna")
print("85% pojazdów ma tablice rejestracyjne NJ lub NY")
print("n = 20, p = 0.15 (prawdopodobieństwo innych stanów)")
print("P(X <= 2) = ?")
print("")

n <- 20
p <- 0.15

print("Metoda 1: Suma poszczególnych prawdopodobieństw")
prob_0 <- dbinom(0, 20, 0.15)
prob_1 <- dbinom(1, 20, 0.15)
prob_2 <- dbinom(2, 20, 0.15)
print(paste("P(X = 0) =", round(prob_0, 4)))
print(paste("P(X = 1) =", round(prob_1, 4)))
print(paste("P(X = 2) =", round(prob_2, 4)))
suma <- prob_0 + prob_1 + prob_2
print(paste("P(X <= 2) =", round(suma, 4)))

print("")
print("Metoda 2: Użycie pbinom()")
prob_pbinom <- pbinom(2, 20, 0.15)
print(paste("P(X <= 2) =", round(prob_pbinom, 4)))

print("")
print("Metoda 3: Użycie sum(dbinom())")
prob_sum <- sum(dbinom(0:2, 20, 0.15))
print(paste("P(X <= 2) =", round(prob_sum, 4)))

print("")
print("Zadanie 8: Prawdopodobieństwa dla rozkładu dwumianowego")
print("")

print("a) n = 50, x = 10, p = 0.20")
n_8a <- 50
x_8a <- 10
p_8a <- 0.20
prob_8a <- dbinom(x_8a, n_8a, p_8a)
print(paste("P(X = 10) =", round(prob_8a, 4)))

print("")
print("b) n = 40, x = 20, p = 0.40")
n_8b <- 40
x_8b <- 20
p_8b <- 0.40
prob_8b <- dbinom(x_8b, n_8b, p_8b)
print(paste("P(X = 20) =", round(prob_8b, 4)))