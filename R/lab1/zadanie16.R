E2_2 <- c(24, 29, 34, 29, 37, 26, 30, 34, 30, 11, 12, 14, 18, 38, 17, 13, 16, 12, 33, 35, 35, 29, 28, 26, 25, 34, 11, 16, 19, 11, 13, 36, 12, 12, 12, 26, 36, 16, 26, 22, 15, 29, 38, 34, 30)

print("Zadanie 16 - Rozklad czestotliwosci z szerokoscia klasy 5:")

brks <- c(10, 14.99, 19.99, 24.99, 29.99, 34.99, 39.99)

categ <- cut(E2_2, brks)

fd <- table(categ)

print(fd)

print("Interpretacja:")
print("11 wartosci nalezy do pierwszej kategorii (10-15)")
print("7 do drugiej (15-20)")
print("2 do trzeciej (20-25)")
print("10 do czwartej (25-30)")
print("8 do piatej (30-35)")
print("7 do szostej (35-40)")

print("Zadanie 17 - Wzgledny rozklad czestotliwosci danych E2_2:")
rf <- fd / sum(fd)
print(rf)

print("Interpretacja wzglednych czestotliwosci:")
print("0.24 obserwacji przypada na pierwsza klase")
print("0.16 na druga klase")
print("0.04 na trzecia klase")
print("0.22 na czwarta klase")
print("0.18 na piata klase")
print("0.16 na szosta klase")

print("Zadanie 18 - Histogram czestotliwosci dla danych E2_2:")

png("histogram_E2_2.png", width = 800, height = 600)
hist(E2_2,
     breaks = c(9.99, 14.99, 19.99, 24.99, 29.99, 34.99, 39.99),
     xlim = c(0, 45),
     ylim = c(0, 12),
     xlab = "x-values",
     ylab = "Frequencies",
     main = "Six Categories",
     col = "blue")
dev.off()

print("Histogram zapisany do pliku: histogram_E2_2.png")