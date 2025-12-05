# Zadanie 1
print("Zadanie 1")
n1 <- 36
x1 <- 26
s1 <- 3.25
n2 <- 31
x2 <- 23
s2 <- 2.75

# (a) Oszacowanie punktowe
print(x1 - x2)

# (b) 99% przedział ufności
moe_99 <- qnorm(0.995) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe_99)
print((x1 - x2) + moe_99)
print((x1 - x2) - moe_99)

# (c) 95% przedział ufności
moe_95 <- qnorm(0.975) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe_95)
print((x1 - x2) + moe_95)
print((x1 - x2) - moe_95)

# Zadanie 2
print("Zadanie 2")
n1 <- 54
x1 <- -3
s1 <- 5.70
n2 <- 47
x2 <- -7
s2 <- 5.10

# (a) Oszacowanie punktowe
print(x1 - x2)

# (b) 99% przedział ufności
moe_99 <- qnorm(0.995) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe_99)
print((x1 - x2) + moe_99)
print((x1 - x2) - moe_99)

# (c) 95% przedział ufności
moe_95 <- qnorm(0.975) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe_95)
print((x1 - x2) + moe_95)
print((x1 - x2) - moe_95)

# Zadanie 3
print("Zadanie 3")
n1 <- 107
x1 <- 3
s1 <- 8.90
n2 <- 121
x2 <- -2
s2 <- 9.80

# (a) Oszacowanie punktowe
print(x1 - x2)

# (b) 99% przedział ufności
moe_99 <- qnorm(0.995) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe_99)
print((x1 - x2) + moe_99)
print((x1 - x2) - moe_99)

# (c) 95% przedział ufności
moe_95 <- qnorm(0.975) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe_95)
print((x1 - x2) + moe_95)
print((x1 - x2) - moe_95)

# Zadanie 4
print("Zadanie 4")
n1 <- 24
x1 <- 717
s1 <- 81
n2 <- 31
x2 <- 658
s2 <- 77

moe <- qt(0.95, n1 + n2 - 2) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe)
print((x1 - x2) + moe)
print((x1 - x2) - moe)

# Zadanie 5
print("Zadanie 5")
n1 <- 34
x1 <- -124
s1 <- 14
n2 <- 28
x2 <- -132 # Zgodnie z obliczeniami w treści zadania (-124 - (-132))
s2 <- 12

# 95% przedział ufności
moe <- qt(0.975, n1 + n2 - 2) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe)
print((x1 - x2) + moe)
print((x1 - x2) - moe)

# Zadanie 6
print("Zadanie 6")
n1 <- 27
x1 <- 2
s1 <- 3.70
n2 <- 22
x2 <- -3
s2 <- 2.45

# 99% przedział ufności
moe <- qt(0.995, n1 + n2 - 2) * sqrt(s1^2 / n1 + s2^2 / n2)
print(moe)
print((x1 - x2) + moe)
print((x1 - x2) - moe)

# Zadanie 7
print("Zadanie 7")
n1 <- 47
x1 <- 151800
s1 <- 17457
n2 <- 34
x2 <- 207100
s2 <- 26510

# (a) Niezależne
print("Dane są niezależne")

# (b) 95% przedział ufności (kierunek odejmowania x2 - x1 zgodnie z treścią)
moe <- qt(0.975, n1 + n2 - 2) * sqrt(s2^2 / n2 + s1^2 / n1)
print(moe)
print((x2 - x1) + moe)
print((x2 - x1) - moe)

# Zadanie 8
print("Zadanie 8")
n1 <- 63
x1 <- 73
s1 <- 11.1
n2 <- 68
x2 <- 76
s2 <- 4.4

# Test hipotezy
se <- sqrt(s1^2 / n1 + s2^2 / n2)
z_stat <- (x1 - x2) / se
print(paste("Z-statistic:", z_stat))

# Wartości krytyczne dla alpha = 0.05
print(qnorm(0.025))
print(qnorm(0.975))
print("Odrzucamy H0, ponieważ Z jest poza przedziałem (-1.96, 1.96)")

# Zadanie 9
print("Zadanie 9")
p_value <- 2 * pnorm(z_stat)
print(paste("P-value:", p_value))
print("P-value < 0.05, odrzucamy H0")

# Zadanie 10
print("Zadanie 10")
n1 <- 81
x1 <- 17.1
s1 <- 2.3
n2 <- 64
x2 <- 17.6
s2 <- 2.1

# Test H0: mu1 - mu2 >= 0 vs H1: mu1 - mu2 < 0
# alpha = 0.05
se <- sqrt(s1^2 / n1 + s2^2 / n2)
z_stat <- (x1 - x2) / se
print(paste("Z-statistic:", z_stat))

# Obszar odrzucenia (lewostronny)
crit_val <- qnorm(0.05)
print(paste("Critical value:", crit_val))
print("Ponieważ z > -1.645, nie odrzucamy H0")

# Zadanie 11
print("Zadanie 11")
p_value <- pnorm(z_stat)
print(paste("P-value:", p_value))
print("P-value > 0.05, nie odrzucamy H0")

# Zadanie 12
print("Zadanie 12")
n1 <- 100
x1 <- 120
s1 <- 20
n2 <- 100
x2 <- 112
s2 <- 20

# Test H0: mu1 - mu2 <= 0 vs H1: mu1 - mu2 > 0
# alpha = 0.01
se <- sqrt(s1^2 / n1 + s2^2 / n2)
z_stat <- (x1 - x2) / se
print(paste("Z-statistic:", z_stat))

# Obszar odrzucenia (prawostronny)
crit_val <- qnorm(0.01, lower.tail = FALSE)
print(paste("Critical value:", crit_val))
print("Ponieważ z > 2.33, odrzucamy H0")

# Zadanie 13
print("Zadanie 13")
p_value <- pnorm(z_stat, lower.tail = FALSE)
print(paste("P-value:", p_value))
print("P-value < 0.01, odrzucamy H0")

# Zadanie 14
print("Zadanie 14")
ex1 <- c(79, 92, 81, 80, 79, 80, 78, 88, 86, 88, 77, 93)
ex2 <- c(80, 75, 67, 82, 76, 71, 78, 78, 80, 77, 78, 75)
scores <- data.frame(Exam1 = ex1, Exam2 = ex2)
print(scores)

# (a) Sparowane
print("Dane są sparowane")

# (b) Estymacja punktowa
diff_est <- mean(scores$Exam1) - mean(scores$Exam2)
print(diff_est)

# (c) 99% przedział ufności
print(t.test(scores$Exam1, scores$Exam2, conf.level = 0.99, paired = TRUE))

# Zadanie 15
print("Zadanie 15")
# alpha = 0.10
test_result <- t.test(scores$Exam1, scores$Exam2, paired = TRUE)
print(test_result)
print("P-value < 0.10, odrzucamy H0")

# Zadanie 16
print("Zadanie 16")
# Check if file exists in current dir, otherwise try R/lab3/ subdir
file_path <- "holidays.csv"
if (!file.exists(file_path)) {
    file_path <- "R/lab3/holidays.csv"
}

if (file.exists(file_path)) {
    holidays <- read.csv(file_path)
    print(names(holidays))
    print("Dane są niezależne")
    print(t.test(holidays$algarve, holidays$cascais, conf.level = 0.90))
} else {
    print("Error: holidays.csv not found. Please download the file.")
}

# Zadanie 17
print("Zadanie 17")
library(MASS)
E11_1 <- Cars93
print(nrow(E11_1))
print(names(E11_1))
print(summary(E11_1$MPG.city))
print(summary(E11_1$MPG.highway))
print(sd(E11_1$MPG.city))
print(sd(E11_1$MPG.highway))
print(table(E11_1$Origin))

print("(b) Zmienne są sparowane (ten sam samochód, różne warunki)")

# (c)
E11_2 <- E11_1[which(E11_1$Origin == "USA"), ]
print(table(E11_2$Origin))

# (d) 90% CI
print(t.test(E11_2$MPG.highway, E11_2$MPG.city, conf.level = 0.90, paired = TRUE))

# Zadanie 18
print("Zadanie 18")
options(scipen = 999)
test_res <- t.test(E11_2$MPG.highway, E11_2$MPG.city, paired = TRUE)
print(test_res)
print("P-value < 0.05, odrzucamy H0")

# Zadanie 19
print("Zadanie 19")
# E11_1 is Cars93 from previous task
E11_3 <- E11_1[which(E11_1$Origin == "non-USA"), ]
print(table(E11_3$Origin))
print("Liczba pojazdów nie z USA: 45")

# (b) 90% CI
print(t.test(E11_3$MPG.highway, E11_3$MPG.city, conf.level = 0.90, paired = TRUE))

# Zadanie 20
print("Zadanie 20")
# alpha = 0.01
test_res <- t.test(E11_3$MPG.highway, E11_3$MPG.city, paired = TRUE)
print(test_res)
print("P-value < 0.01, odrzucamy H0")

# Zadanie 21
print("Zadanie 21")
file_path_temps <- "temps.csv"
if (!file.exists(file_path_temps)) {
    file_path_temps <- "R/lab3/temps.csv"
}

if (file.exists(file_path_temps)) {
    temps <- read.csv(file_path_temps)
    print(names(temps))
    print("(a) Dane są sparowane")
    print("(b) 90% CI")
    print(t.test(temps$Daytemp, temps$Nighttemp, conf.level = 0.90, paired = TRUE))
} else {
    print("Error: temps.csv not found. Please download the file.")
}

# Zadanie 22
print("Zadanie 22")
if (exists("temps")) {
    print(t.test(temps$Daytemp, temps$Nighttemp, paired = TRUE))
    print("P-value < 0.01, odrzucamy H0")
}
# Zadanie 23
print("Zadanie 23")
bad <- c(82, 28)
total <- c(900, 800)
print(prop.test(bad, total, conf.level = 0.95, correct = FALSE))

# Zadanie 24
print("Zadanie 24")
# alpha = 0.01
test_res <- prop.test(bad, total, correct = FALSE)
print(test_res)
print("P-value < 0.01, odrzucamy H0")

# Zadanie 25
print("Zadanie 25")
n1 <- 200
x1 <- 54
n2 <- 200
x2 <- 36
# (d) Rejon odrzucenia
print(qnorm(0.025))
print(qnorm(0.975))
z_val <- 2.1553
p_val <- pnorm(z_val, lower.tail = FALSE) + pnorm(-z_val)
print(p_val)
print("Odrzucamy H0")

# Zadanie 26
print("Zadanie 26")
illiquid <- c(54, 36)
total <- c(200, 200)
print(prop.test(illiquid, total, correct = FALSE))

# Zadanie 27
print("Zadanie 27")
E12_1 <- Cars93
print(nrow(E12_1))
print(names(E12_1))
print(summary(E12_1$MPG.city))
print(summary(E12_1$EngineSize))
print(sd(E12_1$MPG.city))
print(sd(E12_1$EngineSize))

# Zadanie 28
print("Zadanie 28")
plot(E12_1$EngineSize, E12_1$MPG.city,
    pch = 19,
    xlab = "Engine Size (liters)",
    ylab = "City Miles per Gallon",
    main = "Relationship Between City MPG and Engine Size (liters)"
)
print("Istnieje negatywna relacja.")

# Zadanie 29
print("Zadanie 29")
slr1 <- lm(MPG.city ~ EngineSize, data = E12_1)
plot(E12_1$EngineSize, resid(slr1),
    pch = 19,
    xlab = "Engine Size (liters)",
    ylab = "Residuals",
    main = "Residuals Against the Independent Variable"
)
abline(h = 0)
print("Liniowość nie jest zachowana dla skrajnych wartości.")

# Zadanie 30
print("Zadanie 30")
# Wybieramy kolumny MPG.city i EngineSize, gdzie EngineSize <= 2.40
E12_2 <- E12_1[E12_1$EngineSize <= 2.40, c("MPG.city", "EngineSize")]
print(max(E12_2$EngineSize))
print(min(E12_2$EngineSize))
print(head(E12_2, 3))
print(tail(E12_2, 3))
print(nrow(E12_2))

# Zadanie 31
print("Zadanie 31")
plot(E12_2$EngineSize, E12_2$MPG.city,
    pch = 19,
    xlab = "Engine Size (liters)",
    ylab = "City Miles per Gallon",
    main = "Relationship Between City MPG and Engine Size (liters)"
)
print("Teraz mamy liniową i negatywną zależność.")

# Zadanie 32
print("Zadanie 32")
slr2 <- lm(MPG.city ~ EngineSize, data = E12_2)
plot(E12_2$EngineSize, resid(slr2),
    pch = 19,
    xlab = "Engine Size (liters)",
    ylab = "Residuals",
    main = "Residuals Against the Independent Variable"
)
abline(h = 0)
print("Residua są rozłożone bardziej prawidłowo.")

# Zadanie 33
print("Zadanie 33")
print(slr2)

# Zadanie 34
print("Zadanie 34")
print(confint(slr2, level = 0.95))
print(confint(slr2, level = 0.99))

# Zadanie 35
print("Zadanie 35")
coeffs <- coef(slr2)
print(paste("MPG.city =", round(coeffs[1], 2), "+", round(coeffs[2], 2), "* EngineSize"))
print("Wzrost pojemności silnika o 1 litr powoduje spadek spalania (MPG) o ok. 6.65 mili na galon.")

# Zadanie 36
print("Zadanie 36")
ss_y <- sum((E12_2$MPG.city - mean(E12_2$MPG.city))^2)
ss_res <- sum((resid(slr2))^2)
r_squared <- (ss_y - ss_res) / ss_y
print(r_squared)

# Zadanie 37
print("Zadanie 37")
print("Współczynnik determinacji mówi, że około 50.5% zmienności MPG.city jest wyjaśniane przez EngineSize w tym modelu.")

# Zadanie 38
print("Zadanie 38")
s_xy <- sqrt(sum(resid(slr2)^2) / (nrow(E12_2) - 2))
ssx <- sqrt(sum((E12_2$EngineSize - mean(E12_2$EngineSize))^2))
sb1 <- s_xy / ssx

b1 <- sum((E12_2$EngineSize - mean(E12_2$EngineSize)) * (E12_2$MPG.city - mean(E12_2$MPG.city))) / sum((E12_2$EngineSize - mean(E12_2$EngineSize))^2)

t_val <- b1 / sb1
print(t_val)