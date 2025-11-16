E2_1 <- c(rep("A", 272), rep("B", 212), rep("C", 297), rep("D", 38), rep("E", 181), rep("F", 95))

fd <- table(E2_1)

print("Rozklad czestotliwosci preferencji marek:")
print(fd)

print("Calkowita liczba gospodarstw:")
print(sum(fd))

print("Procentowy rozklad preferencji:")
print(prop.table(fd) * 100)

print("Zadanie 12 - Wzgledny rozklad czestotliwosci preferencji marki:")
rf <- fd / sum(fd)
print(rf)

print("Zadanie 13 - Wykres slupkowy czestotliwosci preferencji marki:")
fd <- table(E2_1)
barplot(fd,
        col = c("green", "blue", "red", "yellow", "purple", "orange"),
        ylim = c(0, 300),
        main = "Number of Households Preferring Brand",
        xlab = "Brands",
        ylab = "Brand Preference Frequencies")

print("Zadanie 14 - Wykres slupkowy wzglednych czestotliwosci preferencji marki:")
fd <- table(E2_1)
rf <- fd / sum(fd)
barplot(rf,
        col = c("red", "blue", "red", "blue", "red", "blue"),
        ylim = c(0, 0.30),
        xlab = "Brands",
        ylab = "Relative Frequencies",
main = "Proportion of Households Preferring Brand")

print("Zadanie 15 - Wykres punktowy wzglednej czestotliwosci preferencji marki:")
fd <- table(E2_1)
rf <- fd / sum(fd)
dotchart(sort(rf),
         xlab = "Relative Frequencies Brand is Preferred",
         main = "Relative Frequencies by Brand",
         pch = 19,
         col = "blue")

