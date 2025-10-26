# Zadanie 9 
options(scipen = 999)
var1 <- c("Bangladesh", "Brazil", "China", "India", "Indonesia", "Pakistan", "US")
var2 <- c(144000000, 204000000, 1439000000, 1380000000, 274000000, 221000000, 331000000)
var3 <- c(1700, 10800, 7600, 3500, 4200, 2500, 47200)
var4 <- c(28, 87, 47, 30, 44, 36, 82)
#Ramka
E1_3 <- data.frame(Nation = var1, 
                   Population = var2, 
                   GDP = var3, 
                   PercentUrban = var4)

print("Ramka danych E1_3 - Siedem najbardziej zaludnionych krajow:")
print(E1_3)

# Zadanie 10

print("a) Statystyki dla Population:")
print(summary(E1_3$Population))

print("b) Statystyki dla GDP:")
print(summary(E1_3$GDP))

print("c) Statystyki dla PercentUrban:")
print(summary(E1_3$PercentUrban))

