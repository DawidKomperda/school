print("Zadanie 19 - Analiza czekow klientow restauracji fast food")

setwd("/home/brolveth/Documents/school/R")

E2_3 <- read.csv("check.csv")

print("Statystyki opisowe dla E2_3:")
print(summary(E2_3))

print("Obliczanie szerokosci kategorii:")
print("Minimum: 6.72, Maksimum: 97.74")
print("Zakres: 97.74 - 6.72 = 91.02")
print("Szerokosc kategorii dla 5 klas: 91.02 / 5 = 18.20 (w przyblizeniu 20)")

print("Zadanie 20 - Rozklad czestotliwosci dla E2_3")

print("Nazwa zmiennej:")
print(names(E2_3))

brks <- c(0, 20, 40, 60, 80, 100)

categ <- cut(E2_3$amount, brks)

fd <- table(categ)

print("Rozklad czestotliwosci:")
print(fd)

print("Dane sa dystrybuowane bimodalnie, nie normalnie")

print("Zadanie 21 - Wzgledny rozklad czestotliwosci danych E2_3")

rf <- fd / sum(fd)

print("Wzgledne czestotliwosci:")
print(rf)

print("Interpretacja:")
print("0.09 nalezy do pierwszej kategorii")
print("0.34 do drugiej")
print("0.15 do trzeciej")
print("0.34 do czwartej")
print("0.08 do piatej")

print("Zadanie 22 - Histogram danych E2_3 z 5 kategoriami")

png("histogram_E2_3.png", width = 800, height = 600)
hist(E2_3$amount,
     breaks = c(0, 20, 40, 60, 80, 100),
     col = "purple",
     ylim = c(0, 80),
     xlab = "x values",
     ylab = "Frequencies",
     main = "Five Categories of the Amount that Customers Spend")
dev.off()

print("Histogram zapisany do pliku: histogram_E2_3.png")
print("Z histogramu jasno wynika, ze dane sa bimodalne, nie normalne")

print("Zadanie 23 - Histogram z dziesiecioma klasami")

png("histogram_E2_3_10classes.png", width = 800, height = 600)
hist(E2_3$amount,
     breaks = 10,
     col = "green",
     ylim = c(0, 40),
     xlab = "x values",
     ylab = "Frequencies",
     main = "Ten Categories of the Amount that Customers Spend")
dev.off()

print("Histogram z 10 klasami zapisany do pliku: histogram_E2_3_10classes.png")
print("Uzycie dziesieciu kategorii zamiast 5 nie daje dokladniejszego wgladu")
print("w charakter rozkladu wartosci danych w tym przypadku")

